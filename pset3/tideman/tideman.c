#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
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
bool cycle(int, int);
void print_winner(void);

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
// ranks is an array where each element is candidateNum
// Each element's position signify voter preference of a candidate over the other candidates
bool vote(int rank, string name, int ranks[])
{
    for (int candidateNumber = 0; candidateNumber < candidate_count; candidateNumber++)
    {
        if (strcmp(candidates[candidateNumber], name) == 0)
        {
            ranks[rank] = candidateNumber;
            return true;
        }
    }
    return false;
}

// Update preferences given a voter's ranks array
// Keep-in-mind, prefrences is a global int array, which means all it's elements are already initialised to zeros
void record_preferences(int ranks[])
{
    for (int superiorCandidateNum = 0; superiorCandidateNum < (candidate_count - 1); superiorCandidateNum++)
    {
        for (int inferiorCandidateNum = (superiorCandidateNum + 1); inferiorCandidateNum < candidate_count; inferiorCandidateNum++)
        {
            ++preferences[ranks[superiorCandidateNum]][ranks[inferiorCandidateNum]];
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int candidateNum = 0; candidateNum < (candidate_count - 1); candidateNum++)
    {
        for (int opponentNum = (candidateNum + 1); opponentNum < candidate_count; opponentNum++)
        {
            // Skip pairs which are tied
            if (preferences[candidateNum][opponentNum] == preferences[opponentNum][candidateNum])
            {
                continue;
            }
            pairs[pair_count].winner = preferences[candidateNum][opponentNum] > preferences[opponentNum][candidateNum] ? candidateNum : opponentNum;
            pairs[pair_count].loser = preferences[candidateNum][opponentNum] < preferences[opponentNum][candidateNum] ? candidateNum : opponentNum;
            ++pair_count;
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    int highStrengthPair;
    pair tempPair;
    for (int currPair = 0; currPair < (pair_count - 1); currPair++)
    {
        // selectionSort
        highStrengthPair = currPair;
        for (int opponentPair = (currPair + 1); opponentPair < pair_count; opponentPair++)
        {
            if (preferences[pairs[highStrengthPair].winner][pairs[highStrengthPair].loser] < preferences[pairs[opponentPair].winner][pairs[opponentPair].loser])
            {
                highStrengthPair = opponentPair;
            }
        }

        // If no pair whose strength is greater than current pair, then no need swap
        if (highStrengthPair == currPair)
        {
            continue;
        }

        tempPair = pairs[currPair];
        pairs[currPair] =  pairs[highStrengthPair];
        pairs[highStrengthPair] = tempPair;
    }
    return;
}
// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int currPair = 0; currPair < pair_count; currPair++)
    {
        // Check whether currPair forms a cycle
        if (!cycle(pairs[currPair].winner, pairs[currPair].loser))
        {
            locked[pairs[currPair].winner][pairs[currPair].loser] = true;
        }
    }
    return;
}

bool cycle(int currWinner, int startPairLoser)
{
    // Base case. If startPairLoser is currWinner, cycle found
    if (startPairLoser == currWinner)
    {
        return true;
    }

    // Check if currPair winner has been a loser before
    for (int newWinner = 0; newWinner < candidate_count; newWinner++)
    {
        // If yes, then recursively call cycle function with new winner
        if (locked[newWinner][currWinner])
        {
            // If function returns true, then cycle is found.
            if (cycle(newWinner, startPairLoser))
            {
                return true;
            }

            // Otherwise continue checking connections b/w rest of the candidates & currWinner
        }
    }

    // No cycle found
    return false;
}

// Print the winner of the election
void print_winner(void)
{
    int flag;
    for (int currNode = 0; currNode < candidate_count; currNode++)
    {
        flag = 0;
        for (int otherNode = 0; otherNode < candidate_count; otherNode++)
        {
            if (locked[otherNode][currNode])
            {
                flag = 1;
                break;
            }
        }

        // We have found currNode doesn't have any connections from otherNodes
        if (flag == 0)
        {
            printf("%s\n", candidates[currNode]);
            break;
        }
    }
    return;
}
