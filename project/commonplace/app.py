from flask import Flask, render_template, request, redirect
app = Flask(__name__)
if __name__ == "__main__":
    app.run(debug=True)
@app.route('/',  methods=["POST", "GET"])
def homepage():
    return render_template("homepage.html")