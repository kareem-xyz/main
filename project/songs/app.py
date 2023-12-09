from flask import Flask, render_template, request, redirect, url_for
app = Flask(__name__)

@app.route('/', methods=["POST", "GET"])
def mainpage():
    return render_template('homepage.html')

@app.route('/test', methods=["POST", "GET"])
def test():
     return redirect('/static/index.html')