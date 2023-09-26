// Voting system using the Tideman method.
// Has sorting functions, recursive functions, 2d arrays and much more.
#include <cs50.h>
#include <stdio.h>
#include <strings.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j.
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
//extra sub functions i will use
bool winner(int candidate);
void sort_bubble(int sov[], int num_elements);
bool is_circle(int winner, int current_
loser);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
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
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);
        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // Search if vote is valid in candidates array, else return false
    for (int i = 0; i < candidate_count; i++)
    {
        // return original index from candidates by comparing strings.
        if (strcasecmp(name, candidates[i]) == 0)
        {
            // Populate the ranks array using the vote rank, rank is index j from main function.
            // elements in ranks array have the same index as their original candidates array. also the same for preferences.
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // ranks array stores using original index
    // Loop through all ranks of choices.
    for (int i = 0; i < candidate_count; i++)
    {
        // Loop again to update values for prefereance, j = i to account for not make the other candidates top the one above them( number of loops decreses each time)
        // i + 1 to not compare a candidate against itself.
        // Could also set j = candidate_count and decrese it each time.
        for (int j = i + 1; j < candidate_count; j++)
        {
            // Add one to that preference. ranks[i] gives the original index in candidates.
            // update preferences array with original values for index ranks
            preferences[ranks[i]][ranks[j]]++;
        }
    }
    return;
}

// Record all pairs of candidates where one is preferred over the other, if tie, dont add.
// should update the global variable pair_count each time. initially its 0.
void add_pairs(void)
{
    // loop through preferences[i]
    // loop through preferences[i][j]
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            // check if pair value of pair [i][j] is bigger than pair [j][i] then store in pair array, pair_count++.
            // if pairs are equal or reveresed in greatness
            if (preferences[i][j] <= preferences[j][i])
            {
                continue;
            }
            else
            {
                // pair struct stores integers so we store original index from candidates (same for preferences scores)
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // sov array to sort based on strength of victory.
    int sov[pair_count];
    // loop through pairs array.
    for (int i = 0; i < pair_count; i++)
    {
        // Get strength of victory
        // strength of victory is differenece of votes between winner and loser.
        // we use pairs array to refer to the original index here.
        int strength_of_victory = preferences[pairs[i].winner][pairs[i].loser] - preferences[pairs[i].loser][pairs[i].winner];

        // sov[i] refers to strength of victory in pair[i]
        sov [i] = strength_of_victory;
    }
    // now to sort the pairs and sov arrays based on sov arrays values
    sort_bubble(sov, pair_count);
}

//bubble sort the sov and pairs array
void sort_bubble(int sov[], int num_elements)
{
    int swaps;
    pair cpair;
    int csov;
    do
    {
        swaps = 0;
        for (int i = 0; i < num_elements - 1; i++)
        {
            // variables for copying.
            if (sov[i] < sov[i + 1])
            {
                // copy big values to copying variables
                csov = sov[i];
                cpair = pairs[i];

                // SWAP1
                sov[i] = sov[i + 1];
                pairs[i] = pairs[i + 1];
                // SWAP2
                sov[i + 1] = csov;
                pairs[i + 1] = cpair;
                swaps++;
            }
        }
    }
    while (swaps != 0);
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // loop through all pairs.
    for (int i = 0; i < pair_count; i++)
    {
        // we lock the pairs for the moment, to check if there is a circle.
        locked[pairs[i].winner][pairs[i].loser] = true;

        // function checks whether adding will make a circle, then revert the locking we made, and continue
        if (is_circle(pairs[i].winner, pairs[i].loser))
        {
            locked[pairs[i].winner][pairs[i].loser] = false;
            continue;
        }
    }
}

//sub- functino in lock_pairs
// checks whether a circle is created.
bool is_circle(int winner, int current_loser)
{
    // first time this check is useless, when loser changes however it does make sense.
    if (locked[current_loser][winner])
    {
        return true;
    }
    // loop through all candidates
    for (int i = 0; i < candidate_count; i++)
    {
        //See if the current loser locks onto a candidate.
        if (locked[current_loser][i])
        {
            // call the function again using winner of the original pair, and the new loser (candidate).
            //((NOW THE FIRST IF MAKES SENSE))
            if (is_circle(winner, i))
            {
                return true;
            }
        }
        // the loop goes on until we find a loser that locks onto the original winner, therefore there is a circle, otherwise there isn't and we return false..
    }
    return false;
}

// Print the winner of the election
void print_winner(void)
{
    // read through locked array, when finding element == false print out the candidate with that index number from candidates array.
    // since we populated the locked array using pairs array indexes, they are the same original indexes from the candidates array.
    for (int i = 0; i < candidate_count; i++)
    {
        // checks if no edges point to it
        if (winner(i))
        {
            printf("%s\n", candidates[i]);
            continue;
        }
    }
}

// sub-functin in print_winner, tells if the candidate is a winner or not
bool winner(int candidate)
{
    for (int j = 0; j < candidate_count; j++)
    {
        // if another candidate[j] is locked onto the candidate, return false for this candidate.
        if (locked[j][candidate])
        {
            return false;
        }
    }
    // if no one is locked onto the candidate, they are a winner,
    return true;
}

