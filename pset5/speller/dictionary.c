// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <ctype.h>
#include <string.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

void unload_hash(node *hash);

// Number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

//pnteiro do dicionario
FILE *inptr;

// conta quantas palavras tem no dicionario
int diccounter = 0;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    node *cursor;
    
    char *temp = malloc(sizeof(char) * (LENGTH + 1));
    
    strcpy(temp, word);
    
    for (int i = 0; word[i] != '\0'; i++)
    {
        temp[i] = tolower(word[i]);
    }
    
    cursor = table[hash(word)];
    
    while (cursor != NULL)
    {
        if (strcmp(cursor->word, temp) == 0)
        {
            free(temp);
            return true;
        }
        
        cursor = cursor->next;
    }
    free(temp);
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    char alpha = tolower(word[0]);

    return (alpha - 97);
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // To Do
    inptr = fopen(dictionary, "r");
    if (inptr == NULL)
    {
        return false;
    }

    int index = 0;

    char *dicword = malloc(sizeof(char) * (LENGTH + 1));



    // Separa palavras do dicionario
    for (int c = fgetc(inptr); c != EOF; c = fgetc(inptr))
    {
        // Allow only alphabetical characters and apostrophes
        if (isalpha(c) || (c == '\'' && index > 0))
        {
            // Append character to word
            dicword[index] = c;
            index++;


        }
        else if (index > 0)
        {
            // Terminate current word
            dicword[index] = '\0';

            //Puts word o Hash table
            int hashindex = hash(dicword);
            if (table[hashindex] == NULL)
            {
                table[hashindex] = malloc(sizeof(node));
                strcpy(table[hashindex]->word, dicword);
                table[hashindex]->next = NULL;

            }
            else
            {
                node *cursor;
                cursor = table[hashindex];


                while (cursor->next != NULL)
                {
                    cursor = cursor->next;
                }

                cursor->next = malloc(sizeof(node));
                strcpy(cursor->next->word, dicword);
                cursor->next->next = NULL;


            }

            // Update counter
            diccounter++;

            // Prepare for next word
            for (int i = 0; i < index; i++)
            {

                dicword[i] = '\0';
            }
            index = 0;
        }
    }
    free(dicword);

    fclose(inptr);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{

    return diccounter;

}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    //TO DO
    for (int i = 0; i < N; i++)
    {
        unload_hash(table[i]);
    }
    
    
    if (diccounter == 0)
    {
        return true;
    }
    
    return false;
}

void unload_hash(node *hash)
{
    if (hash == NULL)
    {
        return;
    }
    
    if (hash->next != NULL)
    {
        unload_hash(hash->next);
    }
    free(hash);
    diccounter--;
    
    
    
    
    return;
}