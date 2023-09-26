

//Pre Settings.
document.querySelector("button").addEventListener("click", function()
    {
        q1.querySelector('#b1').style.backgroundColor = '#00cc00';
    }
);

//To Check answers
const answers = [3];
// Array holds "empty" or button.id
for (let i = 0; i < 3; i++)
{
    answers[i] = "empty";
}



/////////////////////////
//Function Definitions
//When pressing SUBMIT
function checkAnswers()
{

    // Check if all questions were answered
    for (let i = 0; i < 3; i++)
    {
        error = document.getElementById("tmpDiv");
        if (answers[i] === "empty")
        {
            error.innerHTML = "<p style='color:red;'>Please answer all the questions first.<p>";
            return;
        }

    }
    if (answers[0] === "a11" && answers[1] === "a20" && answers[2] === "a32")
    {
        window.location.replace("h3.html");
    }
    else
    {
        window.location.replace("h4.html");
    }
    // Won't check if personal data was filled
}

function changeColor3(button)
{
    const btns3 = document.querySelectorAll('.btns3');
    btns3.forEach(btns3 =>
        {
        btns3.style.backgroundColor = "black";
        btns3.style.color = "#06b406";
        });
    button.style.backgroundColor = "#06b406";
    button.style.color = "black";
    answers[2] = button.id;
}

function changeColor2(button)
{
    const btns2 = document.querySelectorAll('.btns2');
    btns2.forEach(btns2 =>
        {
        btns2.style.backgroundColor = "black";
        btns2.style.color = "#06b406";
        });
    button.style.backgroundColor = "#06b406";
    button.style.color = "black";
    answers[1] = button.id;
}

function changeColor1(button)
{
    const btns1 = document.querySelectorAll('.btns1');
    btns1.forEach(btns1 =>
        {
        btns1.style.backgroundColor = "black";
        btns1.style.color = "#06b406";
        });
    button.style.backgroundColor = "#06b406";
    button.style.color = "black";
    answers[0] = button.id;
}
