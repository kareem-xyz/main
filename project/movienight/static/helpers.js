// initialise variables for efficiency
var choices = [2];    // Stores choices by movie id
var highlighted = [2]; // for css highlighting, stores button
const list_0 = document.getElementById("list_0");   // References html element of list 0
const list_1 = document.getElementById("list_1");   // References html element of list 1

// Initialise Arrays
for (let i = 0; i < 2; i++)
{
    choices[i] = "null";
    highlighted[i] = "null"
}

// Run whenever a choose movie button is pressed to note the movie and makes sure to not conflict lists.
function choose(button)
{
    var movie = button;
    movie_list = movie.getAttribute("data-list")
    
    // Highlight new chosen movie
    movie.innerHTML = "Chosen!";
    movie.classList.add("btn-primary");
    movie.classList.remove("btn-outline-primary");
    try 
    {
        // Remove highlight from the movie chosen before 
        highlighted[movie_list].classList.add("btn-outline-primary");
        highlighted[movie_list].classList.remove("btn-primary");
        highlighted[movie_list].innerHTML = "Choose"
    }
    catch(err) 
    {
    }


    // Save new movie
    highlighted[movie_list] = movie;
    choices[movie_list] = movie.getAttribute("data-id");
    tmp = 'movie' + movie_list;
    document.getElementById(tmp).value = movie.getAttribute("data-title");

}
// Run after choosing movie and pressing compare, to render compare.html
function compare()
{
    // Convert array to json
    choices_json =  JSON.stringify(choices);

    // Post movies' ids chosen back to the python flask app to process them and display the new page of content.
    $.post( "/compare", {
        choices: choices_json
    });
}
