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
void print_winner(void);

void partition(pair list[], int low, int high);
void mergeSort(pair list[], int low, int mid, int high);

bool check_edge(int x);
bool check_cycle(int x, int y);

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
    for (int k = 0; k < candidate_count; k++)
    {
        if (strcmp(name, candidates[k]) == 0)
        {
            ranks[rank] = k;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int k = 0; k < candidate_count; k++)
    {
        for (int m = k + 1; m < candidate_count; m++)
        {
            preferences[ranks[k]][ranks[m]]++;
        }
    }

    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int k = 0; k < candidate_count; k++)
    {
        for (int m = 0; m < candidate_count; m++)
        {
            if (preferences[k][m] > preferences[m][k])
            {
                pairs[pair_count].winner = k;
                pairs[pair_count].loser = m;
                pair_count++;
            }
        }
    }
    
    for (int i = 0; i < pair_count; i++)
    {
        printf("%i: %i %i\n", i, pairs[i].winner, pairs[i].loser);
    }
    
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    partition(pairs, 0, pair_count);
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        if (check_cycle(pairs[i].winner, pairs[i].loser) == false)
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    for (int i = 0; i < MAX; i++)
    {
        for (int j = 0; j < MAX; j++)
        {
            if (locked[i][j] == true && check_edge(i) == false)
            {
                printf("%s\n", candidates[i]);
                return;
            }
        }
    }
    
    return;
}

void partition(pair list[], int low, int high)
{
    int mid;
 
    if (low < high)
    {
        mid = (low + high) / 2;
        partition(list, low, mid);
        partition(list, mid + 1, high);
        mergeSort(list, low, mid, high);
    }
}
 
void mergeSort(pair list[], int low, int mid, int high)
{
    int i, mi, k, lo; 
    pair temp[high - low];
 
    lo = low;
    i = low;
    mi = mid + 1;
    while ((lo <= mid) && (mi <= high))
    {
        if (preferences[list[lo].winner][list[lo].loser] > preferences[list[mi].winner][list[mi].loser])
        {
            temp[i] = list[lo];
            lo++;
        }
        else
        {
            temp[i] = list[mi];
            mi++;
        }
        i++;
    }
    if (lo > mid)
    {
        for (k = mi; k <= high; k++)
        {
            temp[i] = list[k];
            i++;
        }
    }
    else
    {
        for (k = lo; k <= mid; k++)
        {
            temp[i] = list[k];
            i++;
        }
    }
 
    for (k = low; k <= high; k++)
    {
        list[k] = temp[k];
    }
}

bool check_cycle(int x, int y)
{
    for (int i = 0; i < MAX; i++)
    {
        if (locked[y][i] == true)
        {
            if (i == x || check_cycle(x, i) == true)
            {
                return true;
            }
        }
    }
    return false;
}

bool check_edge(int x)
{
    for (int i = 0; i < MAX; i++)
    {
        if (locked[i][x] == true)
        {
            return true;
        }
        
    }
    return false;
}