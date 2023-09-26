// Gives string with the most votes.
// Program uses some ideas from selection sort.
#include <cs50.h>
#include <stdio.h>
#include <strings.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: ./plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    // TODO
    // if input is the same as some candidate, add one vote to that candidate, else say input is invalid.
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcasecmp(name, candidates[i].name) == 0)
        {
            candidates[i].votes++;
            return true;
        }
    }
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    // TODO
    // Function uses initiliases a new array of candidates to house only winners, and a temporary variable called winner to compare the highest value only.
    // Similar to the function I used for selection sort.
    candidate winners[candidate_count];
    candidate winner;
    // we use the 0 as a starting value to avoid some trouble later.
    winner.votes = 0;
    int num_winners = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        // if a candidate has higher votes than the current highest, replace the winner with it and set the value of num_winners to one winner only.
        if (candidates[i].votes > winner.votes)
        {
            winner = candidates[i];
            winners[0] = candidates[i];
            // num_winners equals zero means one winner only.
            num_winners = 0;
        }
        else if (candidates[i].votes == winner.votes)
        {
            //if some candidate shares the votes with another, add it to the winner and increase their number by 1.
            num_winners++;
            winners[num_winners] = candidates[i];
        }
    }
    // loop to only output the winners (hence why <= num_winner) why the equals because num_winners can be 0
    for (int j = 0; j <= num_winners; j++)
    {
        printf("%s\n", winners[j].name);
    }
    //it's worth noting however that altough this function prints only the winners, some values in the winners array might still stay unprinted.
    return;
}