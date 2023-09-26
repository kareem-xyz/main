#include <cs50.h>
#include <stdio.h>
// included for comparing names
#include <strings.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    // loop through candidates
    for (int i = 0; i < candidate_count; i++)
    {
        // check if input (name) is a candidate, else return false
        if (strcasecmp(name, candidates[i].name) == 0)
        {
            // set the (ranks) preference equal to the candidate's index.
            preferences[voter][rank] = i;
            return true;
        }
    }
    // if no candidate matches name.
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    // loop through all voters
    for (int i = 0; i < voter_count; i++)
    {
        //read through preferences
        for (int j = 0; j < candidate_count; j++)
        {
            int current_cand = preferences[i][j];
            // if current rank is not eliminated
            if (!candidates[current_cand].eliminated)
            {
                // add vote.
                candidates[current_cand].votes++;
                // break here goes to the next voter.
                break;
            }
            // else the loop will go on until it finds an un eliminated candidate.
        }
    }
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    // calculate half of votes
    int half_votes = voter_count / 2;
    for (int i = 0; i < candidate_count; i++)
    {
        // check if a candidate has more than half
        if (candidates[i].votes > half_votes)
        {
            printf("%s\n", candidates[i].name);
            return true;
        }
    }
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    // TODO
    // set to the first candidate for comparisons sake
    int lowest_vote = candidates[0].votes;
    // read candidates
    for (int i = 0; i < candidate_count; i++)
    {
        // if a candidate isn't eliminated, and has lower votes than the current one, update lowest_vote
        if ((!candidates[i].eliminated) && (candidates[i].votes < lowest_vote))
        {
            lowest_vote = candidates[i].votes;
        }
    }
    return lowest_vote;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    // if all candidates are tied, they must be all equal to (min)
    for (int i = 0; i < candidate_count; i++)
    {
        // if not eliminated and votes not equal to min.
        if (!candidates[i].eliminated && candidates[i].votes != min)
        {
            return false;
        }
    }
    // when all remaining (uneliminated candidates) have votes equal to min
    return true;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    // loop through candidates
    for (int i = 0; i < candidate_count; i++)
    {
        // not eliminated and is lowest on votes.
        if (!candidates[i].eliminated && candidates[i].votes == min)
        {
            // eliminate.
            candidates[i].eliminated = true;
        }
    }
    return;
}