from flask import Flask, render_template, request, redirect 

# Configure Application
app = Flask(__name__)

# Load homepage
@app.route('/')
def homepage():
    return render_template('homepage.html')
