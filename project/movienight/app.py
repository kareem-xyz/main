from flask import Flask, render_template, request, redirect 
import requests # Used in the query Api

# Configure Application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

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
    m0_input = request.form.get("movie0")
    m1_input = request.form.get("movie1")
    
    # Check for invalid input
    if not (m0_input and m1_input):
        return redirect('/')
    
    # Movie Databases Api to get Movie's Data.
    # https://rapidapi.com/SAdrian/api/moviesdatabase/
    #----

    # Format Api Urls for each movie inputed
    m0_url = "https://moviesdatabase.p.rapidapi.com/titles/search/title/" + m0_input
    m1_url = "https://moviesdatabase.p.rapidapi.com/titles/search/title/" + m1_input

    # Api Specifics (login key and query parameters)
    querystring = {"exact":"false","titleType":"movie"}
    headers = {
        "X-RapidAPI-Key": "dcabfff8b1msh47092185488eb22p1b47e2jsn45e1e47ab1f7",
        "X-RapidAPI-Host": "moviesdatabase.p.rapidapi.com"
    }

    # Run Api
    m0_response = requests.get(m0_url, headers=headers, params=querystring)
    m1_response = requests.get(m1_url, headers=headers, params=querystring)

    m0_json = m0_response.json()
    m1_json = m1_response.json()

    return render_template('search.html', list0=m0_json["results"], list1=m1_json["results"], q0=m0_input, q1=m1_input)




