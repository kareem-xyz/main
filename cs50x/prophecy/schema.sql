
CREATE TABLE IF NOT EXISTS students
    (
        student_id     INTEGER,
        student_name   TEXT,
        PRIMARY KEY    (student_id)
    );

CREATE TABLE IF NOT EXISTS houses
    (
        house_id       INTEGER,
        house_name     TEXT UNIQUE,
        head           TEXT,
        PRIMARY KEY    (house_id)
    );

CREATE TABLE IF NOT EXISTS house_assignments
    (
        student_id     INTEGER FORIEGN KEY REFERENCES students(student_name),
        house_id       TEXT  FORIEGN KEY REFERENCES houses(huose_id)
    );