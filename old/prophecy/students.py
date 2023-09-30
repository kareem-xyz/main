import csv
import sys
import sqlite3
# From cs50 import SQL
# using both sql packages to demonstrate different methods

buffer = []

# ---------Read csv data to memory.
with open("students.csv", "r") as file:
    reader = csv.DictReader(file)
    for row in reader:
        buffer.append(row)

# ---------Open new database, create a new one if first time.
# CS50 Way (documentation says I can't create database on the fly, So I will use a different method): new_db = SQL("sqlite:///hogwarts.db")

# The method I found online to create database:
new_db = sqlite3.connect('hogwarts.db')

# Think of cursor like the command door I am using to issue queries.
c = new_db.cursor()

# ----------CREATE TABLES
c.execute("""
          CREATE TABLE IF NOT EXISTS students
               (
                    student_id     INTEGER,
                    student_name   TEXT,
                    PRIMARY KEY    (student_id)
                );
          """)

c.execute("""
          CREATE TABLE IF NOT EXISTS houses
               (
                    house_id       INTEGER,
                    house_name     TEXT UNIQUE,
                    head           TEXT,
                    PRIMARY KEY(house_id)
                );
          """)

c.execute("""
          CREATE TABLE IF NOT EXISTS house_assignments
               (
                    student_id     INTEGER FORIEGN KEY REFERENCES students(student_name),
                    house_id TEXT  FORIEGN KEY REFERENCES houses(huose_id)
               );
          """)

# ----------INSERT STUDENTS DATA
for student in buffer:
    c.execute('INSERT INTO           students (student_name) VALUES(?);', (student["student_name"],) )
    c.execute('INSERT OR IGNORE INTO houses(house_name, head) VALUES(?, ?);', (student["house"], student["head"]) )
    c.execute('INSERT INTO           house_assignments (student_id, house_id) VALUES(?, (SELECT house_id FROM houses WHERE houses.house_name = ?));', (student["id"], student["house"]) )
new_db.commit()
sys.exit(0)