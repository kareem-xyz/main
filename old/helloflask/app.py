from flask import Flask, render_template, request

app = Flask(__name__)
colors = ["Red", "Blue"]


@app.route("/", methods=["POST", "GET"])
def index():
    if request.method == "GET":
        return render_template("index.html", colors=colors)

    print("Form Submitted!")
    color = request.form.get("color")
    if color not in colors:
        return "<div style='text-align:center;'><h1>Error<br></h1><h2>Invalid Input</h2></div>"
    return render_template("color.html", color=color)
