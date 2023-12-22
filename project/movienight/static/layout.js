// List of forms
const list_form = Array.from(document.getElementsByTagName('form'));
for (let i = 0; i < list_form.length; i++)
{
    // List of loading elements inside a form
    const list_load_status = Array.from(list_form[i].getElementsByClassName('load-status'));

    // Remove loading mode at startup
    for (let j = 0; j < list_load_status.length; j++)
    {
        (list_load_status[j]).classList.remove('display-show');
        (list_load_status[j]).classList.add('display-hide');
    }

    // THESE TWO FUNCTIONS MUST NOT BE MERGED, OTHERWISE CODE WILL BREAK
    
    // On form submit, add loading to elements
    list_form[i].addEventListener('submit', function (event) 
    {
        // Run over elements and add listener
        for (let k = 0; k < list_load_status.length; k++)
        {
            list_load_status[k].classList.add('display-show');
            list_load_status[k].classList.remove('display-hide');
        }
    })
};
