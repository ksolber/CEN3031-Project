import sqlite3

DB_PATH = "food_finder.db"


def get_connection():
    """Returns a connection to the SQLite database."""
    conn = sqlite3.connect(DB_PATH)
    conn.row_factory = sqlite3.Row  # lets us access columns by name
    return conn


def init_db():
    """Creates the locations table if it doesn't exist yet."""
    conn = get_connection()
    cursor = conn.cursor()

    cursor.execute("""
        CREATE TABLE IF NOT EXISTS locations (
            id                   INTEGER PRIMARY KEY AUTOINCREMENT,
            name                 TEXT NOT NULL,
            address              TEXT NOT NULL,
            latitude             REAL,
            longitude            REAL,
            halal                INTEGER DEFAULT 0,
            kosher               INTEGER DEFAULT 0,
            vegan                INTEGER DEFAULT 0,
            vegetarian           INTEGER DEFAULT 0,
            carnivore            INTEGER DEFAULT 0,
            handicap_accessible  INTEGER DEFAULT 0,
            appointment_required INTEGER DEFAULT 0,
            student_only         INTEGER DEFAULT 0,
            hours                TEXT,
            description          TEXT,
            eligibility          TEXT,
            phone                TEXT,
            email                TEXT,
            website              TEXT,
            notes                TEXT,
            is_open              INTEGER DEFAULT 0
        )
    """)

    conn.commit()
    conn.close()
    print("Database initialized.")


if __name__ == "__main__":
    init_db()
