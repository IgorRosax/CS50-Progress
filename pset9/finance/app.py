import os
import re

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd


# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


OPERATION_BUY="buy"
OPERATION_SELL="sell"
CURRENCY_SYMBOL="$"

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


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
    stocks = getStocks(session["user_id"])

    wallet = getWallet(session["user_id"])

    ballance = calculateBalance(stocks,wallet)

    return render_template("index.html",index={"stocks":stocks, "wallet":wallet,"ballance":ballance})




@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():

    """Buy shares of stock"""
    if request.method == "POST":
        if not request.form.get("symbol"):
            return apology("must provide symbol", 403)
        elif not request.form.get("shares"):
            return apology("must provide shares", 403)
        elif int(request.form.get("shares")) <= 0:
            return apology("Share number must be positive", 403)

        quoteResult = lookup(request.form.get("symbol"))
        if quoteResult != None:

            rows = db.execute("select cash from users where id = ?", session["user_id"])


            if len(rows) != 1:
                return apology("Invalid user!", 403)
            elif rows[0]["cash"]< int(request.form.get("shares")) * quoteResult["price"]:
                return apology("Insuficient cash!", 403)

            if not buyStock(request.form.get("symbol"),int(request.form.get("shares")),quoteResult["price"],session["user_id"]):
                return apology("Sorry, the stock could not be bought!", 403)
            else:
                return redirect("/")
        else:
            return apology("Symbol not found", 403)

    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    return apology("TODO")


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

        if not request.form.get("symbol"):
            return apology("must provide symbol", 403)

        quoteResult = lookup(request.form.get("symbol"))

        return render_template("quoted.html",quoteResult=quoteResult)
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

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

        # Ensure password confirmation was submitted
        elif not request.form.get("confirmation"):
            return apology("must provide password confirmation", 403)

        # Ensure password confirmation was the same as password


        elif re.compile(str(request.form.get("password"))).fullmatch(str(request.form.get("confirmation"))) == None:
        #elif not check_password_hash(request.form.get("confirmation"), request.form.get("password")):
            return apology("must provide the same password twice for confirmation", 403)

        # Query database for username
        rows = db.execute("SELECT 1 FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) >= 1:
            return apology("invalid username", 403)

        #Insert user on table users to register
        rows = db.execute("Insert into users (username, hash) values (?,?)", request.form.get("username"), generate_password_hash(request.form.get("password")))

        # Query database for user id
        rows = db.execute("SELECT id FROM users WHERE username = ?", request.form.get("username"))

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("register.html")



@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":
        if not request.form.get("symbol"):
            return apology("must provide symbol", 403)
        elif not request.form.get("shares"):
            return apology("must provide shares", 403)
        elif int(request.form.get("shares")) <= 0:
            return apology("Share number must be positive", 403)

        quoteResult = lookup(request.form.get("symbol"))
        if quoteResult != None:

            rows = db.execute(" select sum(case when operation = ? then shares else shares * (-1) end) as shares from brokerage_registers where userid = ? and symbol = ?",
                              OPERATION_BUY,session["user_id"], request.form.get("symbol"))


            if len(rows) != 1:
                return apology("Invalid user!", 403)
            elif rows[0]["shares"] < int(request.form.get("shares")):
                return apology("Insuficient shares!", 403)

            if not sellStock(request.form.get("symbol"),int(request.form.get("shares")),quoteResult["price"],session["user_id"]):
                return apology("Sorry, the stock could not be bought!", 403)
            else:
                return redirect("/")
        else:
            return apology("Symbol not found", 403)

    else:
        return render_template("sell.html")


def buyStock(symbol, shares, price, userId):
    """Buy Stock"""

    db.execute("Insert into brokerage_registers (userid, symbol, shares,price, operation, timestamp) values (?,?,?,?,?,datetime())",
                      userId , symbol, shares, price,OPERATION_BUY)

    db.execute("update users set cash = cash - ? where id = ?", shares * price, userId )

    return True

def sellStock(symbol, shares, price,userId):
    """Sell Stock"""

    db.execute("Insert into brokerage_registers (userid, symbol, shares,price, operation, timestamp) values (?,?,?,?,?,datetime())",
                      userId , symbol, shares, price,OPERATION_SELL)

    db.execute("update users set cash = cash + ? where id = ?", shares * price, userId )

    return True

def getStocks(user_id):
    rows = db.execute(" select symbol, sum(case when operation = ? then shares else shares * (-1) end) as shares " +
                      "from brokerage_registers where userid = ? group by symbol " +
                      "having sum(case when operation = ? then shares else shares * (-1) end) > 0;",
                              OPERATION_BUY,user_id,OPERATION_BUY)

    for row in rows:
        quoteResult = lookup(row["symbol"])
        row["name"]=quoteResult["name"]
        row["price"]=quoteResult["price"]
        row["total"]=row["shares"]*quoteResult["price"]

    return rows

def getWallet(user_id):
    rows = db.execute(" select ? as symbol, ? as name, cash from users where id = ?",
                              CURRENCY_SYMBOL,"cash",user_id)

    return rows

def calculateBalance(stocks,wallet):
    ballance={"symbol": CURRENCY_SYMBOL ,"name":"ballance", "ballance" : 0}

    for row in stocks:
        ballance["ballance"] = ballance["ballance"] + row["total"]

    for row in wallet:
        ballance["ballance"] = ballance["ballance"] + row["cash"]

    return ballance