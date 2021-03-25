import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True


# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    # Get cash for current-user
    cash = db.execute("SELECT * FROM users WHERE id=(?)", session["user_id"])[0]["cash"]

    # Get shares_purchases of current user
    portfolio = db.execute("SELECT * FROM purchases WHERE id=(?)", session["user_id"])

    # Update per-share-value, total-value from lookup
    total = cash
    if len(portfolio) == 0:
        portfolio = None
    else:
        total_shares_value = 0
        for row in portfolio:
            quote = lookup(row["symbol"])
            row["per_symbol_share_value"] = quote["price"]
            row["symbol_totalShares_value"] = (row["per_symbol_share_value"] * row["shares"])
            total_shares_value += row["symbol_totalShares_value"]
        total = total + total_shares_value
    return render_template("portfolio.html", portfolio=portfolio, cash=cash, total=total)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        # Get the symbol from user
        symbol = request.form.get("symbol")

        # Get the shares from user
        shares = request.form.get("shares")

        # Validate symbol
        quote = lookup(symbol)
        if not quote:
            return apology("Symbol not found", 400)

        # Validate shares
        if not shares.isdigit() or int(shares) <= 0:
            return apology("Shares must be positive integers", 400)
        shares = int(shares)

        # Validate for sufficient funds
        curr_user = db.execute("SELECT * FROM users WHERE id=(?)", session["user_id"])
        cash = curr_user[0]["cash"] - (shares * quote["price"])
        if cash < 0:
            return apology("Not sufficient funds", 400)

        # Update cash
        db.execute("UPDATE users SET cash=(?) WHERE id=(?)", cash, session["user_id"])

        # Update shares. Also update history
        past_symbol_purchase = db.execute("SELECT * FROM purchases WHERE id=(?) AND symbol=(?)", session["user_id"], symbol)
        db.execute("INSERT INTO history(id, symbol, shares, price) VALUES(?,?,?,?)",
                   session["user_id"], symbol, shares, quote["price"])
        if len(past_symbol_purchase) == 1:
            shares = shares + past_symbol_purchase[0]["shares"]
            db.execute("UPDATE purchases SET shares = (?) WHERE id = (?) AND symbol = (?)", shares, session["user_id"], symbol)
        else:
            db.execute("INSERT INTO purchases(id, symbol, name, shares) VALUES(?,?,?,?)",
                       session["user_id"], symbol, quote["name"], shares)

        flash("Bought!")
        return redirect("/")

    return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    history_db = db.execute("SELECT * FROM history WHERE id=(?)", session["user_id"])
    if history_db == []:
        history_db = None
    return render_template("history.html", history_db=history_db)


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
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
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

        # Validate symbol
        quote = lookup(request.form.get("symbol"))
        if not quote:
            return apology("Symbol not found", 400)

        # Return symbol quote
        return render_template("quote.html", quote=quote)

    return render_template("quote.html", quote=None)


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":

        # Get username and password
        usrname = request.form.get("username")
        psw = request.form.get("password")

        # Validate username
        if not usrname:
            return apology("must provide username", 400)
        check = db.execute("SELECT * FROM users WHERE username=(?) LIMIT 1", usrname)
        if len(check) == 1:
            return apology("Username taken", 400)

        # Validate password
        if not psw or not request.form.get("confirmation"):
            return apology("must provide password", 400)
        if psw != request.form.get("confirmation"):
            return apology("Passwords must match", 400)

        # Generate psw_hash and update db
        psw_hash = generate_password_hash(psw)
        db.execute("INSERT INTO users (username, hash) VALUES(?, ?)", usrname, psw_hash)

        # Set-cookie for session
        rows = db.execute("SELECT id FROM users WHERE username = ?", usrname)
        session["user_id"] = rows[0]["id"]

        flash("Registered!")
        return redirect("/")

    return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    # Get symbols owned by the current user
    symbols = db.execute("SELECT symbol FROM purchases WHERE id=(?)", session["user_id"])
    if symbols == []:
        symbols = None

    if request.method == "POST":
        # Get symbol, shares from POST request
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        # Validate symbol
        if not symbol:
            return apology("Select symbol", 400)
        if not symbols:
            return apology("You don't own that symbol shares", 400)
        flag = 0
        for row in symbols:
            if symbol == row["symbol"]:
                flag = 1
                break
        if flag == 0:
            return apology("You don't own that symbol shares", 400)

        # Validate shares
        if not shares.isdigit() or int(shares) <= 0:
            return apology("Shares must be positive integers", 400)
        shares = int(shares)

        # Check if current user owns more shares than selling shares
        curr_shares = db.execute("SELECT shares FROM purchases WHERE id=(?) AND symbol=(?)",
                                 session["user_id"], symbol)[0]["shares"]
        curr_shares = curr_shares - shares
        if curr_shares < 0:
            return apology("Not sufficient shares", 400)

        # Update current owned shares by subtracting from sold shares. Also update history
        quote = lookup(symbol)
        db.execute("INSERT INTO history(id, symbol, shares, price) VALUES(?,?,?,?)",
                   session["user_id"], symbol, (-1 * shares), quote["price"])
        if curr_shares == 0:
            db.execute("DELETE FROM purchases WHERE id=(?) AND symbol=(?)", session["user_id"], symbol)
        else:
            db.execute("UPDATE purchases SET shares=(?) WHERE id=(?) AND symbol=(?)", curr_shares, session["user_id"], symbol)

        # Update cash after selling
        value = quote["price"] * shares
        db.execute("UPDATE users SET cash=cash+(?) WHERE id=(?)", value, session["user_id"])

        flash("Sold!")
        return redirect("/")

    return render_template("sell.html", symbols=symbols)


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
