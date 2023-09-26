import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///birthdays.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalibirthday"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/", methods=["GET", "POST"])
def index():
    if request.method == "POST":
        # TODO: Add the user's entry into the database
        name = request.form.get("name")
        # Get birthday from Form in the (yyyy-mm-dd) format
        birthday = request.form.get("birthday")
        # Separate values for birthday
        birthday = birthday.split("-")
        month = birthday[1]
        day = birthday[2]

        db.execute(
            "INSERT INTO birthdays (name, month, day) VALUES (?, ?, ?)",
            name,
            month,
            day,
        )

        # redirect using GET
        return redirect("/")

    else:
        # TODO: Display the entries in the database on index.html
        # db.execute here returns a list of dictionaries, where each dictionary is a row.

        birthdays = db.execute("SELECT name, month, day FROM birthdays")
        for person in birthdays:
            person["month"] = str(person["month"])
            person["day"] = str(person["day"])
        return render_template("index.html", birthdays=birthdays)
