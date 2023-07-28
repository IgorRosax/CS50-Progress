#include <stdio.h>
#include <cs50.h>

int main(void)
{
    
    int size = 0;
    
    while (size < 1 || size > 8)
    {
        size = get_int("Please, type the pyramid's height (must be beetween 1 and 8): ");
    }
    
    
    for (int i = size; i > 0; i--)
    {
        for (int j = size - i; j < size - 1; j++)
        {
            printf(" ");
        }
        
        for (int j = i; j <= size; j++)
        {
            printf("#");
        }
        
        printf("  ");
        
        for (int j = i; j <= size; j++)
        {
            printf("#");
        }
        
        
        printf("\n");
    }
}