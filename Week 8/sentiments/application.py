from flask import Flask, redirect, render_template, request, url_for

import sys
import os
import helpers
from analyzer import Analyzer

app = Flask(__name__)


@app.route("/")
def index():
    return render_template("index.html")


@app.route("/search")
def search():

    # validate screen_name
    screen_name = request.args.get("screen_name", "").lstrip("@")
    if not screen_name:
        return redirect(url_for("index"))

    # get screen_name's tweets
    tweets = helpers.get_user_timeline(screen_name, 100)

    # absolute paths to lists
    positives = os.path.join(sys.path[0], "positive-words.txt")
    negatives = os.path.join(sys.path[0], "negative-words.txt")

    # classify tweets
    positive, negative, neutral = 0.0, 0.0, 100.0
    positive_count, negative_count, neutral_count = 0, 0, 0

    if tweets is not None and len(tweets) != 0:

        # instantiate analyzer
        analyzer = Analyzer(positives, negatives)

        # analyze tweets
        for tweet in tweets:
            score = analyzer.analyze(tweet)
            if score > 0.0:
                positive_count += 1
            elif score < 0.0:
                negative_count += 1
            else:
                neutral_count += 1

        # get percentages
        positive, negative, neutral = positive_count / len(tweets), \
            negative_count / len(tweets), \
            neutral_count / len(tweets)

    # generate chart
    chart = helpers.chart(positive, negative, neutral)

    # render results
    if tweets is not None and len(tweets) != 0:
        return render_template("search.html", chart=chart, screen_name=screen_name, tweets=str(len(tweets)), tweet=tweets[0])
    elif len(tweets) == 0:
        return render_template("search.html", chart=chart, screen_name=screen_name, tweets=0, tweet="No tweets")
    else:
        return render_template("search.html", chart=chart, screen_name=screen_name, tweets="N/A", tweet="Not an account")
