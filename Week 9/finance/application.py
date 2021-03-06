from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session, url_for
from flask_session import Session
from passlib.apps import custom_app_context as pwd_context
from tempfile import mkdtemp

import csv
import urllib

from helpers import *

# configure application
app = Flask(__name__)

# ensure responses aren't cached
if app.config["DEBUG"]:
    @app.after_request
    def after_request(response):
        response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
        response.headers["Expires"] = 0
        response.headers["Pragma"] = "no-cache"
        return response

# custom filter
app.jinja_env.filters["usd"] = usd

# configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

@app.route("/")
@login_required
def index():
    # get stock and cash data
    rows = db.execute("SELECT symbol, SUM(shares), SUM(price) FROM stocks WHERE user_id = '{}' GROUP BY symbol".format(session["user_id"]))
    cash = float(db.execute("SELECT cash FROM users WHERE id = '{}'".format(session["user_id"]))[0]['cash'])
    
    # add mo lookup data
    new_rows = []
    for row in rows:
        data = lookup(row['symbol'])
        row['value'] = int(row['SUM(shares)']) * data['price']
        row['price'] = float(row['SUM(price)'])
        row['shares'] = int(row['SUM(shares)'])
        row['name'] = data['name']
        new_rows.append(row)
    
    # totals
    total = {}
    total['price'] = sum(float(row['price']) for row in new_rows) + cash
    total['value'] = sum(float(row['value']) for row in new_rows) + cash
    total['change'] = "{0:.2f}%".format(100 * (total['value'] - total['price'])/total['price'])
    color = "red" if (100 * (total['value'] - total['price'])/total['price'])<0 else "green"
    total['price'], total['value'] = usd(total['price']), usd(total['value'])
    
    # format -_-
    newer_new_rows = []
    for row in new_rows:
        row['value'] = usd(row['value'])
        row['price'] = usd(row['price'])
        newer_new_rows.append(row)
    
    # return page
    return render_template("index.html", stocks=new_rows, cash=usd(cash), total=total, color=color)

@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock."""
    if request.method == "POST":
        
        # store symbol and shares
        symbol = request.form.get("symbol").upper()
        shares = float(int(request.form.get("shares")))
        
        # get data
        quote = lookup(symbol)
        if quote is None:
            return apology("invalid stock")
        
        # see if user has enough money
        rows = db.execute("SELECT * FROM users WHERE id = :id", id=session["user_id"])
        cash = rows[0]["cash"]
        if shares * quote["price"] > cash:
            return apology("not enough cash")
        
        # buy buy buy!
        db.execute("INSERT INTO stocks (user_id, action, symbol, shares, price) VALUES({}, '{}', '{}', {}, {})".format(session["user_id"], "buy", symbol, int(shares), shares * quote["price"]))
        db.execute("UPDATE users SET cash = {} WHERE id = {}".format(cash - (shares * quote["price"]), session["user_id"]))
        
        # back home
        return redirect(url_for("index"))
        
    else:
        return render_template("buy.html")

@app.route("/history")
@login_required
def history():
    """Show history of transactions."""
    
    # get transactions
    rows = db.execute("SELECT * FROM stocks WHERE user_id = ':id'", id=session["user_id"])
    
    # cleanup
    new_rows = []
    for row in rows:
        row["pricepershare"] = usd(abs(row["price"])/row["shares"])
        row["price"] = usd(abs(row["price"]))
        new_rows.append(row)
    rows = new_rows
    
    # render
    return render_template("history.html", stocks=rows)

@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in."""

    # forget any user_id
    session.clear()

    # if user reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username")

        # ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password")

        # query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username", username=request.form.get("username"))

        # ensure username exists and password is correct
        if len(rows) != 1:
            return apology("no such username")
        
        if pwd_context.verify(request.form.get("password"), rows[0]["hash"]) is False:
            return apology("wrong password/username")

        # remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # redirect user to home page
        return redirect(url_for("index"))

    # else if user reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")

@app.route("/logout")
def logout():
    """Log user out."""

    # forget any user_id
    session.clear()

    # redirect user to login form
    return redirect(url_for("login"))

@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    
    # if user reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        
        # store symbol
        symbol = request.form.get("symbol")
        
        # read data from Yahoo
        quote = lookup(symbol)
        
        # render
        if quote is not None:
            return render_template("quoted.html", symbol=quote["symbol"], name=quote["name"], price=usd(float(quote["price"])))
        else:
            return apology("invalid stock")
        
    # else if user reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("quote.html")

@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user."""

    # if user reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        
        # ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username")
        
        # ensure password was submitted
        elif not request.form.get("password") or not request.form.get("password-again"):
            return apology("must provide password twice")
        
        # check if username already exists
        rows = db.execute("SELECT * FROM users WHERE username = :username", username=request.form.get("username"))
        if len(rows) != 0:
            return apology("username already exists")
        
        # check if two passwords match
        if request.form.get("password") != request.form.get("password-again"):
            return apology("passwords don't match")
        
        # now actually add user to db
        db.execute("INSERT INTO users (username, hash) VALUES ('{}', '{}')".format(request.form.get("username"), pwd_context.encrypt(request.form.get("password"))))
        
        # redirect to login
        return redirect(url_for("login"))

    # else if user reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("register.html")

@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock."""
    
    if request.method == "POST":
        
        # store symbol and shares
        symbol = request.form.get("symbol").upper()
        shares = float(int(request.form.get("shares")))
        
        # get data
        quote = lookup(symbol)
        if quote is None:
            return apology("invalid stock")
        
        # see if user has enough shares
        rows = db.execute("SELECT SUM(shares) FROM stocks WHERE user_id = :id AND symbol = :symbol", id=session["user_id"], symbol=symbol)
        if rows[0]["SUM(shares)"] is None:
            return apology("you don't own that stock")
        if shares > int(rows[0]["SUM(shares)"]):
            return apology("not enough shares")
        cash = db.execute("SELECT cash FROM users WHERE id = :id", id=session["user_id"])[0]["cash"]
        
        # buy buy buy!
        db.execute("INSERT INTO stocks (user_id, action, symbol, shares, price) VALUES({}, '{}', '{}', {}, {})".format(session["user_id"], "sell", symbol, 0 - int(shares), 0 - (shares * quote["price"])))
        db.execute("UPDATE users SET cash = {} WHERE id = {}".format(cash + (shares * quote["price"]), session["user_id"]))
        
        # back home
        return redirect(url_for("index"))
        
    else:
        return render_template("sell.html")
        
    return apology("TODO")

""" my own additions """
@app.route("/cash", methods=["GET", "POST"])
@login_required
def cash():
    """ get cash """
    
    if request.method == "POST":
    
        # validate
        cash = request.form.get("cash")
        try:
            cash = float(cash)
            cash = round(cash, 2)
        except:
            return(apology("that's no numbah"))
        
        # add cash
        current_cash = db.execute("SELECT cash FROM users WHERE id = :id", id=session["user_id"])[0]["cash"]
        db.execute("UPDATE users SET cash = :cash WHERE id = :id", id=session["user_id"], cash=current_cash + cash)
        
        # back home
        return redirect(url_for("index"))
    
    else:
        return render_template("cash.html")