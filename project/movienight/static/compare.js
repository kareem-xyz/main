// initialise array for later usage
const choices = [2]
for (let i = 0; i < 2; i++)
{
    choices[i] = "empty";
}

// Run whenever a choose movie is pressed to choose the movie and makes sure to not conflict lists.
function choose(button)
{
    const movie = button;
    choices[movie.getAttribute('data-list')] = movie.getAttribute("data-id");
    console.log(choices)
}
function compare(button)
{
    // Submit movies chosen back to the python flask app to process them and display the new page of content.
}