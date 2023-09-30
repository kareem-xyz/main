void sort_bubble(int arraytosort[], int num_elements)
{
    int swaps;
    do
    {
         swaps = 0;
        for (int i = 0; i < num_elements - 1; i++)
        {
            // variables for copying.
            // Can vary from program to program based on what to sort
            int copy;
            if (arraytosort[i] < arraytosort[i+1])
            {
                // copy big values to copying variables
                copy = arraytosort[i];

                // SWAP1
                arraytosort[i] = arraytosort[i+1];

                // SWAP2
                arraytosort[i+1] = copy;
                swaps++;
            }
        }
    }
    //--------------TESTING-------------
    // for (int i = 0; i < num_elements; i++;
    //{
        //printf("%i ", arraytosort[i]);
    //}
    while (swaps != 0);
}