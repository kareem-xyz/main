// initialise variables for efficiency
const choices = [2];    // Array for Choices
const list_0 = document.getElementById("list_0");   // References parent element of list 0
const list_1 = document.getElementById("list_1");   // References parent element of list 1
const highlighted = [2];

for (let i = 0; i < 2; i++)
{
    choices[i] = "empty";
    highlighted[i] = "empty"
}

// Run whenever a choose movie button is pressed to choose the movie and makes sure to not conflict lists.
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
        // ###############need to adjust highlight as a list not a var
        // Remove highlight from the movie chosen before 
        highlighted[movie_list].classList.add("btn-outline-primary");
        highlighted[movie_list].classList.remove("btn-primary");
    }
    catch(err) 
    {
    }


    // Save new movie
    highlighted[movie_list] = movie;
    choices[movie_list] = movie.getAttribute("data-id");

}
function compare(button)
{
    // Submit movies chosen back to the python flask app to process them and display the new page of content.
}
