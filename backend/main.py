import math
from pathlib import Path
from typing import Optional

from database import get_connection, init_db
from fastapi import FastAPI, HTTPException
from fastapi.responses import FileResponse
from fastapi.staticfiles import StaticFiles
from pydantic import BaseModel


def haversine(lat1: float, lon1: float, lat2: float, lon2: float) -> float:
    """Returns the distance in miles between two coordinates."""
    earth_radius_miles = 3958.8
    to_rad = math.pi / 180.0
    dlat = (lat2 - lat1) * to_rad
    dlon = (lon2 - lon1) * to_rad
    a = (
        math.sin(dlat / 2) ** 2
        + math.cos(lat1 * to_rad) * math.cos(lat2 * to_rad) * math.sin(dlon / 2) ** 2
    )
    return earth_radius_miles * 2 * math.atan2(math.sqrt(a), math.sqrt(1 - a))


app = FastAPI(title="GatorsKitchen API")


# Run DB setup on startup
@app.on_event("startup")
def startup():
    init_db()


# defines what a location looks like as JSON
class Location(BaseModel):
    name: str
    address: str
    latitude: Optional[float] = None
    longitude: Optional[float] = None
    description: Optional[str] = None
    hours: Optional[str] = None
    eligibility: Optional[str] = None
    phone: Optional[str] = None
    email: Optional[str] = None
    website: Optional[str] = None
    halal: bool = False
    kosher: bool = False
    vegan: bool = False
    vegetarian: bool = False
    carnivore: bool = False
    handicap_accessible: bool = False
    notes: Optional[str] = None
    is_open: bool = False


# Routes
@app.get("/api/locations")
def get_all_locations(
    halal: Optional[bool] = None,
    kosher: Optional[bool] = None,
    vegan: Optional[bool] = None,
    vegetarian: Optional[bool] = None,
    carnivore: Optional[bool] = None,
    handicap_accessible: Optional[bool] = None,
    is_open: Optional[bool] = None,
    max_distance: Optional[float] = None,
    user_lat: Optional[float] = None,
    user_lon: Optional[float] = None,
):
    """Returns locations, optionally filtered by dietary flags and distance."""
    conditions = []
    for field, value in [
        ("halal", halal),
        ("kosher", kosher),
        ("vegan", vegan),
        ("vegetarian", vegetarian),
        ("carnivore", carnivore),
        ("handicap_accessible", handicap_accessible),
        ("is_open", is_open),
    ]:
        if value is True:
            conditions.append(f"{field} = 1")

    query = "SELECT * FROM locations"
    if conditions:
        query += " WHERE " + " AND ".join(conditions)

    conn = get_connection()
    rows = conn.execute(query).fetchall()
    conn.close()

    results = [dict(row) for row in rows]

    if max_distance is not None and user_lat is not None and user_lon is not None:
        results = [
            r
            for r in results
            if r["latitude"] is not None
            and r["longitude"] is not None
            and haversine(user_lat, user_lon, r["latitude"], r["longitude"])
            <= max_distance
        ]

    return results


@app.get("/api/locations/{location_id}")
def get_location(location_id: int):
    """Returns a single location by ID."""
    conn = get_connection()
    row = conn.execute(
        "SELECT * FROM locations WHERE id = ?", (location_id,)
    ).fetchone()
    conn.close()

    if row is None:
        raise HTTPException(status_code=404, detail="Location not found")
    return dict(row)


@app.post("/api/locations", status_code=201)
def create_location(location: Location):
    """Adds a new location to the database."""
    conn = get_connection()
    cursor = conn.cursor()

    cursor.execute(
        """
        INSERT INTO locations
            (name, address, latitude, longitude, description,
             hours, eligibility, phone, email, website,
             halal, kosher, vegan, vegetarian, carnivore,
             handicap_accessible, notes, is_open)
        VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)
    """,
        (
            location.name,
            location.address,
            location.latitude,
            location.longitude,
            location.description,
            location.hours,
            location.eligibility,
            location.phone,
            location.email,
            location.website,
            location.halal,
            location.kosher,
            location.vegan,
            location.vegetarian,
            location.carnivore,
            location.handicap_accessible,
            location.notes,
            location.is_open,
        ),
    )

    conn.commit()
    new_id = cursor.lastrowid
    conn.close()
    return {"id": new_id, "message": "Location created successfully"}


@app.put("/api/locations/{location_id}")
def update_location(location_id: int, location: Location):
    """Updates an existing location."""
    conn = get_connection()

    existing = conn.execute(
        "SELECT id FROM locations WHERE id = ?", (location_id,)
    ).fetchone()

    if existing is None:
        conn.close()
        raise HTTPException(status_code=404, detail="Location not found")

    conn.execute(
        """
        UPDATE locations SET
            name=?, address=?, latitude=?, longitude=?, description=?,
            hours=?, eligibility=?, phone=?, email=?, website=?,
            halal=?, kosher=?, vegan=?, vegetarian=?, carnivore=?,
            handicap_accessible=?, notes=?, is_open=?
        WHERE id=?
    """,
        (
            location.name,
            location.address,
            location.latitude,
            location.longitude,
            location.description,
            location.hours,
            location.eligibility,
            location.phone,
            location.email,
            location.website,
            location.halal,
            location.kosher,
            location.vegan,
            location.vegetarian,
            location.carnivore,
            location.handicap_accessible,
            location.notes,
            location.is_open,
            location_id,
        ),
    )
    conn.commit()
    conn.close()
    return {"message": "Location updated successfully"}


@app.delete("/api/locations/{location_id}")
def delete_location(location_id: int):
    """Deletes a location."""
    conn = get_connection()

    existing = conn.execute(
        "SELECT id FROM locations WHERE id = ?", (location_id,)
    ).fetchone()

    if existing is None:
        conn.close()
        raise HTTPException(status_code=404, detail="Location not found")

    conn.execute("DELETE FROM locations WHERE id = ?", (location_id,))
    conn.commit()
    conn.close()
    return {"message": "Location deleted successfully"}


# Serve the frontend
FRONTEND_DIR = Path(__file__).parent.parent / "frontend"
app.mount("/static", StaticFiles(directory=str(FRONTEND_DIR / "static")), name="static")


@app.get("/")
def serve_frontend():
    return FileResponse(str(FRONTEND_DIR / "index.html"))
