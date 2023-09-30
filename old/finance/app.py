import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd, check_password

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    """
    All below code is for GET method, could do shortcuts for selling and buying from portfolio.html using POST. Will see to it later)))
    """

    # Get User data from server (Cash, stocks owned, shares)
    user_id = session["user_id"]
    cash_balance = db.execute("SELECT cash FROM users WHERE id = ? LIMIT 1", user_id)
    cash_balance = int(cash_balance[0]["cash"])
    stocks = db.execute(
        "SELECT stock, shares FROM portfolios WHERE user_id = ?", user_id
    )  # List of dicts

    # Calculate values for each stock, and total value for portfolio
    grand_total = cash_balance
    for stock in stocks:
        price = lookup(stock["stock"])["price"]
        total_stock_value = price * stock["shares"]
        stock["price"] = price
        stock["total_stock_value"] = total_stock_value
        grand_total += total_stock_value

    # Pass values to render portfolio
    return render_template(
        "portfolio.html",
        stocks=stocks,
        cash_balance=cash_balance,
        grand_total=grand_total,
    )


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    if request.method == "POST":
        # Get User input, and Validate.
        symbol = request.form.get("symbol")
        shares_buy = request.form.get("shares")

        if (not symbol) or (not shares_buy):
            return apology("Invalid Stock symbol or share amount")

        if not shares_buy.isdecimal():
            return apology("Invalid amount of shares")
        shares_buy = int(shares_buy)

        # Get Stock details from api, and validate
        stock = lookup(symbol)
        if not stock:
            return apology("Stock not available")
        symbol = stock["symbol"]
        price = stock["price"]

        # Check for enough cash
        user_id = session["user_id"]
        user_balance = db.execute(
            "SELECT cash FROM users WHERE id = ? LIMIT 1", user_id
        )
        user_balance = user_balance[0]["cash"]
        price_total = price * shares_buy
        remaining_balance = user_balance - price_total
        if remaining_balance < 0:
            return apology(
                f"Not enough Cash.\n Current: {usd(user_balance)} \n Required: {usd(price_total)}"
            )

        # Begin transaction
        db.execute("begin transaction")
        try:
            # Payment
            db.execute(
                "UPDATE users SET cash = ? WHERE id = ?;", remaining_balance, user_id
            )
            # Update portfolio
            db.execute(
                "INSERT INTO portfolios(user_id, stock, shares) VALUES(?, ?, ?) ON CONFLICT(user_id, stock) DO UPDATE SET shares = shares + ?",
                user_id,
                symbol,
                shares_buy,
                shares_buy,
            )
            # Log transaction
            db.execute(
                "INSERT INTO transactions(user_id, type, stock, shares, price) VALUES(?, 'buy', ?, ?, ?)",
                user_id,
                symbol,
                shares_buy,
                price,
            )

        except (ValueError, RuntimeError):
            # On Failure, revert changes to server.
            db.execute("rollback")
            # Forget any user_id
            session.clear()
            return apology("SERVER ERROR")

        db.execute("commit")

        # Redirect to home page
        return redirect("/")

    return render_template("buy.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    # Render page with owned stocks to choose from
    if request.method == "GET":
        user_id = session["user_id"]
        stocks = db.execute("SELECT stock FROM portfolios WHERE user_id = ?", user_id)
        return render_template("sell.html", stocks=stocks)

    if request.method == "POST":
        # Get User input, and Validate.
        symbol = request.form.get("symbol")
        shares_sell = request.form.get("shares")

        if (not symbol) or (not shares_sell):
            return apology("Invalid Stock symbol or share amount")

        if not shares_sell.isdecimal():
            return apology("Invalid amount of shares")
        if int(shares_sell) == 0:
            return apology("Invalid amount of shares")

        shares_sell = int(shares_sell)

        # Get Stock details from api, and validate
        stock = lookup(symbol)
        if not stock:
            return apology("Stock not available")
        symbol = stock["symbol"]
        price = stock["price"]

        # Check for enough owned shares
        user_id = session["user_id"]
        user_shares = db.execute(
            "SELECT shares FROM portfolios WHERE user_id = ? and stock = ? LIMIT 1",
            user_id,
            symbol,
        )
        user_shares = user_shares[0]["shares"]
        added_balance = price * shares_sell
        remaining_shares = user_shares - shares_sell
        if remaining_shares < 0:
            return apology(
                f"Not enough shares.\n Current: {user_shares}.\n Required: {shares_sell}.",
            )

        # Begin transaction
        db.execute("begin transaction")
        try:
            # Payment
            db.execute(
                "UPDATE users SET cash = cash + ? WHERE id = ?;", added_balance, user_id
            )
            # Update portfolio
            db.execute(
                "UPDATE portfolios SET shares = ? WHERE user_id = ? AND stock = ?",
                remaining_shares,
                user_id,
                symbol,
            )
            # Log transaction
            db.execute(
                "INSERT INTO transactions(user_id, type, stock, shares, price) VALUES(?, 'sell', ?, ?, ?)",
                user_id,
                symbol,
                shares_sell,
                price,
            )

        except (ValueError, RuntimeError):
            # On Failure, revert changes to server.
            db.execute("rollback")
            # Forget any user_id
            session.clear()
            return apology("SERVER ERROR")

        db.execute("commit")

        # Redirect to home page
        return redirect("/")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    user_id = session["user_id"]
    transactions = db.execute(
        "SELECT id, type, stock, shares, price, date_time FROM transactions WHERE user_id = ? ORDER BY (date_time) DESC",
        user_id,
    )
    return render_template("history.html", transactions=transactions)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        quote = lookup(symbol)
        if quote == None:
            return apology("Stock not found")
        return render_template("quoted.html", quote=quote)
    return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    if request.method == "GET":
        return render_template("register.html")

    if request.method == "POST":
        # Get user's input
        userdata = request.form.to_dict()
        username = userdata["username"]
        password = userdata["password"]
        confirmation = userdata["confirmation"]

        # Check Username Validity
        username = userdata["username"]
        if not username:
            return apology("Username required")

        user_check = db.execute(
            "SELECT username FROM users WHERE username = ? LIMIT 1", username
        )
        if user_check:
            return apology("Username is already in use")

        # Check Password Validity
        """
        Function from Geeksforgeeks.com, adjusted for my own use, with some changes by me.
        Check helper.py
        """
        result = check_password(password)

        if not result["validity"]:
            return apology(result["msg"])

        if password != confirmation:
            return apology("Passwords do not match")

        # Insert User into Database
        db.execute(
            "INSERT INTO users (username, hash) VALUES (?, ?)",
            username,
            generate_password_hash(password),
        )
        return render_template("registered.html")


@app.route("/account", methods=["GET"])
@login_required
def account():
    return render_template("account.html", phrase="")


@app.route("/change_password", methods=["POST"])
@login_required
def change_password():
    # Get input
    if request.method == "POST":
        user_id = session["user_id"]
        old = request.form.get("oldpassword")
        new = request.form.get("newpassword")
        con = request.form.get("confirmation")

        # Validate new passwords.
        if new == old:
            return apology("New Password must be different from old")
        if new != con:
            return apology("Passwords do not match")
        result = check_password(new)
        if not result["validity"]:
            return apology(result["msg"])

        # Compare to server
        server_hash = db.execute("SELECT hash FROM users WHERE id = ?", user_id)
        server_hash = server_hash[0]["hash"]
        if not check_password_hash(server_hash, old):
            return apology("Incorrect Old Password")

        # Store Hash Values
        old = generate_password_hash(old)
        new = generate_password_hash(new)
        con = generate_password_hash(con)

        # Update values on server
        db.execute("UPDATE users SET hash = ? WHERE id = ?", new, user_id)

    redirect("/")


@app.route("/add_cash", methods=["POST"])
@login_required
def add_cash():
    # Input data
    user_id = session["user_id"]
    add_cash = request.form.get("add_cash")

    # Validate cash
    if not add_cash:
        return apology("Invalid amount of cash. Must be positive number1.")
    if not add_cash.isdecimal():
        return apology("Invalid amount of cash. Must be positive number.2")
    if int(add_cash) == 0:
        return apology("Invalid amount of cash. Must be positive number.3")
    add_cash = int(add_cash)

    # Update Server
    db.execute("begin transaction")
    if (
        db.execute("UPDATE users SET cash = cash + ? WHERE id = ?", add_cash, user_id)
        != 1
    ):
        db.execute("rollback")
        return apology("Adding Cash failed")
    db.execute("commit")
    return redirect("/")
