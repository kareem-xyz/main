import csv
import datetime
import pytz
import requests
import subprocess
import urllib
import uuid

from flask import redirect, render_template, session
from functools import wraps


def apology(message, code=400):
    """Render message as an apology to user."""

    def escape(s):
        """
        Escape special characters.

        https://github.com/jacebrowning/memegen#special-characters
        """
        for old, new in [
            ("-", "--"),
            (" ", "-"),
            ("_", "__"),
            ("?", "~q"),
            ("%", "~p"),
            ("#", "~h"),
            ("/", "~s"),
            ('"', "''"),
        ]:
            s = s.replace(old, new)
        return s

    return render_template("apology.html", top=code, bottom=escape(message)), code


def login_required(f):
    """
    Decorate routes to require login.

    http://flask.pocoo.org/docs/0.12/patterns/viewdecorators/
    """

    @wraps(f)
    def decorated_function(*args, **kwargs):
        if session.get("user_id") is None:
            return redirect("/login")
        return f(*args, **kwargs)

    return decorated_function


def lookup(symbol):
    """Look up quote for symbol."""

    # Prepare API request
    symbol = symbol.upper()
    end = datetime.datetime.now(pytz.timezone("US/Eastern"))
    start = end - datetime.timedelta(days=7)

    # Yahoo Finance API
    url = (
        f"https://query1.finance.yahoo.com/v7/finance/download/{urllib.parse.quote_plus(symbol)}"
        f"?period1={int(start.timestamp())}"
        f"&period2={int(end.timestamp())}"
        f"&interval=1d&events=history&includeAdjustedClose=true"
    )

    # Query API
    try:
        response = requests.get(
            url,
            cookies={"session": str(uuid.uuid4())},
            headers={"User-Agent": "python-requests", "Accept": "*/*"},
        )
        response.raise_for_status()

        # CSV header: Date,Open,High,Low,Close,Adj Close,Volume
        quotes = list(csv.DictReader(response.content.decode("utf-8").splitlines()))
        quotes.reverse()
        price = round(float(quotes[0]["Adj Close"]), 2)
        return {"name": symbol, "price": price, "symbol": symbol}
    except (requests.RequestException, ValueError, KeyError, IndexError):
        return None


def usd(value):
    """Format value as USD."""
    return f"${value:,.2f}"


def check_password(password):
    """
    Function from Geeksforgeeks.com, adjusted for my own use
    Return value is a dict = {"validity" : validityean, "msg": "string"
    """
    SpecialSym = [
        "$",
        "@",
        "#",
        "%",
        "~",
        "!",
        "@",
        "#",
        "$",
        "%",
        "^",
        "&",
        "*",
        "(",
        ")",
        "_",
        "-",
        "+",
        "=",
        "{",
        "[",
        "}",
        "]",
        "|",
        ":",
        ";",
        "<",
        ">",
        ".",
        "?",
        "/",
    ]
    result = {"validity": True, "msg": "Valid Password"}

    if len(password) < 8:
        result["validity"] = False
        result["msg"] = "Password must be at least 8 characters long"

    elif len(password) > 20:
        result["validity"] = False
        result["msg"] = "Password can not be above 20 characters long"

    elif not any(char.isdigit() for char in password):
        result["validity"] = False
        result[
            "msg"
        ] = "Password must contain atleast a lowercase letter, an uppercase letter, a number, and a symbol"

    elif not any(char.isupper() for char in password):
        result["validity"] = False
        result[
            "msg"
        ] = "Password must contain atleast a lowercase letter, an uppercase letter, a number, and a symbol"

    elif not any(char.islower() for char in password):
        result["validity"] = False
        result[
            "msg"
        ] = "Password must contain atleast a lowercase letter, an uppercase letter, a number, and a symbol"

    elif not any(char in SpecialSym for char in password):
        result["validity"] = False
        result[
            "msg"
        ] = "Password must contain atleast a lowercase letter, an uppercase letter, a number, and a symbol"
        
    return result
