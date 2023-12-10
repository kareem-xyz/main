from flask import Flask, render_template, request, redirect 
import requests # Used in the query Api
# Configure Application
app = Flask(__name__)

# Load homepage
@app.route('/')
def homepage():
    return render_template('homepage.html')
    
@app.route('/compare', methods=['GET', 'POST'])
def compare():
    m1_input = request.form.get("movie1")
    m2_input = request.form.get("movie2")
     
    # Movie Databases Api to get Movie's Data.
    # https://rapidapi.com/SAdrian/api/moviesdatabase/
    #----

    # Format Api Urls for each movie inputed
    m1_url = "https://moviesdatabase.p.rapidapi.com/titles/search/title/" + m1_input
    m2_url = "https://moviesdatabase.p.rapidapi.com/titles/search/title/" + m2_input

    # Api Specifics (login key and query parameters)
    querystring = {"exact":"true","titleType":"movie"}
    headers = {
        "X-RapidAPI-Key": "dcabfff8b1msh47092185488eb22p1b47e2jsn45e1e47ab1f7",
        "X-RapidAPI-Host": "moviesdatabase.p.rapidapi.com"
    }

    # Run Api
    m1_response = requests.get(m1_url, headers=headers, params=querystring)
    m2_response = requests.get(m2_url, headers=headers, params=querystring)

    return m1_response.json

