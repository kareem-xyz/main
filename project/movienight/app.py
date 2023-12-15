from flask import Flask, render_template, request, redirect 
import requests # Used in the query Api
# Configure Application
app = Flask(__name__)

####FOR TESTING
@app.route('/test')
def test():
    return render_template('test.html')

@app.route('/testnew')
def testnew():
    return render_template('testnew.html')
#####
# Load homepage
@app.route('/')
def homepage():
    return render_template('homepage.html')
    
@app.route('/search', methods=['GET', 'POST'])
def search():
    m1_input = request.form.get("movie1")
    m2_input = request.form.get("movie2")
    
    # Check for invalid input
    if not (m1_input and m2_input):
        return redirect('/')
    
    # Movie Databases Api to get Movie's Data.
    # https://rapidapi.com/SAdrian/api/moviesdatabase/
    #----

    # Format Api Urls for each movie inputed
    m1_url = "https://moviesdatabase.p.rapidapi.com/titles/search/title/" + m1_input
    m2_url = "https://moviesdatabase.p.rapidapi.com/titles/search/title/" + m2_input

    # Api Specifics (login key and query parameters)
    querystring = {"exact":"false","titleType":"movie"}
    headers = {
        "X-RapidAPI-Key": "dcabfff8b1msh47092185488eb22p1b47e2jsn45e1e47ab1f7",
        "X-RapidAPI-Host": "moviesdatabase.p.rapidapi.com"
    }

    # Run Api
    m1_response = requests.get(m1_url, headers=headers, params=querystring)
    m2_response = requests.get(m2_url, headers=headers, params=querystring)

    m1_json = m1_response.json()
    m2_json = m2_response.json()
    # Next stage is developing the search result page, adding thumbnails images from bootstrap, and making them resposive to pressing so users can choose which movie they want.
    # should experiment and read about how to manipulate jinja into showing images with urls from json files
    # Pass Api response to render search results
    return render_template('search.html', list1=m1_json["results"], list2=m2_json["results"])




