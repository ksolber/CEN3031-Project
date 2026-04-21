CREATE TABLE IF NOT EXISTS pantries (
    id                   INT AUTO_INCREMENT PRIMARY KEY,
    name                 VARCHAR(255) NOT NULL,
    address              VARCHAR(255),

    -- Coordinates
    latitude             DOUBLE,
    longitude            DOUBLE,

    -- Dietary flags
    halal                BOOLEAN DEFAULT FALSE,
    kosher               BOOLEAN DEFAULT FALSE,
    vegan                BOOLEAN DEFAULT FALSE,
    vegetarian           BOOLEAN DEFAULT FALSE,
    carnivore            BOOLEAN DEFAULT FALSE,

    -- Accessibility & conditions
    handicap_accessible  BOOLEAN DEFAULT FALSE,
    appointment_required BOOLEAN DEFAULT FALSE,
    student_only         BOOLEAN DEFAULT FALSE,

    -- Contact & details
    hours                VARCHAR(255),
    description          TEXT,
    eligibility          VARCHAR(255),
    phone                VARCHAR(50),
    email                VARCHAR(255),
    website              VARCHAR(255),
    notes                TEXT,

    -- Realtime status
    is_open              BOOLEAN DEFAULT FALSE
);
