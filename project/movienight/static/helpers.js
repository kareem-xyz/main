// initialise variables for efficiency
var highlighted = [2]; // for css highlighting, stores button
const col_0 = document.getElementById("col_0");   // References html element of list 0
const col_1 = document.getElementById("col_1");   // References html element of list 1

// Initialise Arrays
for (let i = 0; i < 2; i++)
{
    highlighted[i] = "null"
}

// Run whenever a choose movie button is pressed to note the movie and makes sure to not conflict lists.
function choose(button)
{
    var movie = button;
    movie_list = movie.getAttribute("data-list");

    if (highlighted[movie_list])
    {
        if (highlighted[movie_list] == movie)
        {
            return
        };
    };

    movie_index = movie.getAttribute("data-index");
    
    // Highlight new chosen movie
    movie.innerHTML = "Chosen!";
    movie.classList.add("btn-primary");
    movie.classList.remove("btn-outline-primary");
    try 
    {
        // Remove highlight from the movie chosen before 
        highlighted[movie_list].classList.add("btn-outline-primary");
        highlighted[movie_list].classList.remove("btn-primary");
        highlighted[movie_list].innerHTML = "Choose";
    }
    catch(err) 
    {
        console.log(err)
    }


    // Add highlighting css
    highlighted[movie_list] = movie;

    // Set input field for the compare form ( notice how the variables are interpolated inside the back-ticked (``) strings using the JS symbol $)
    // Update input field for search form

    document.getElementById(`movie${movie_list}`).value = movie.getAttribute("data-title");
    // Save the new movie' data
    if (movie_list == '0'){
        sessionStorage.setItem('choice_0', JSON.stringify(datalist_0[Number(movie_index)]));
        // Input in compare form
        document.getElementById(`choice_${movie_list}`).value = JSON.stringify(datalist_0[Number(movie_index)]);
    }
    else {
        sessionStorage.setItem('choice_1', JSON.stringify(datalist_1[Number(movie_index)]));
        document.getElementById(`choice_${movie_list}`).value = JSON.stringify(datalist_1[Number(movie_index)]);
    }
}
