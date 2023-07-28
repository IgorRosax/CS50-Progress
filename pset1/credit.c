#include <stdio.h>
#include <cs50.h>

long int doubledigit(long int cardnum, long int i);

int main(void)
{
    long int cardnum, validation = 0, i = 10;
    int count = 0 ;
    
    cardnum = get_long("Insert the card number: ");
    
    
    
    for (i = 10; cardnum % i != cardnum ; i = i * 10)
    {
        
        count++;
        if (count % 2 == 0)
        {
            if (doubledigit(cardnum, i) < 10)
            {
                validation = validation + doubledigit(cardnum, i);
            }
            else
            {
                validation = validation + doubledigit(cardnum, i) % 10 + (doubledigit(cardnum, i) - doubledigit(cardnum, i) % 10) / 10;
            }
        }
        else
        {
            validation = validation + (((cardnum % i) - (cardnum % (i / 10))) / (i / 10));
        }
    }
    count++;
    
    if (count % 2 == 0)
    {
        if (doubledigit(cardnum, i) < 10)
        {
            validation = validation + doubledigit(cardnum, i);
        }
        else
        {
            validation = validation + doubledigit(cardnum, i) % 10 + (doubledigit(cardnum, i) - doubledigit(cardnum, i) % 10) / 10;
        }
    }
    else
    {
        validation = validation + (((cardnum % i) - (cardnum % (i / 10))) / (i / 10));
    }
    
    printf("\nNumero do cartao: %ld \n\n", cardnum % i);
    printf("Dois primeiros digitos: %ld \n\n", ((cardnum % i) - (cardnum % (i / 100))) / (i / 100));
    printf("O cartao tem %d digitos. \n\n", count);
    
    if (validation % 10 == 0 && (count == 13 || count == 16) && (((cardnum % i) - (cardnum % (i / 10))) / (i / 10)) == 4)
    {
        printf("VISA\n");
    }
    else 
    {
        int aux = ((cardnum % i) - (cardnum % (i / 100))) / (i / 100);
        switch (aux)
        {
            case 34:
                if (validation % 10 == 0 && count == 15)
                {
                    printf("AMEX\n");
                    
                }
                else
                {
                    printf("INVALID\n");
                }
                break;
            
            case 37:
                if (validation % 10 == 0 && count == 15)
                {
                    printf("AMEX\n");
                    
                }
                else
                {
                    printf("INVALID\n");
                }
                break;
            
            case 51:
                if (validation % 10 == 0 && count == 16)
                {
                    printf("MASTERCARD\n");
                    
                }
                else
                {
                    printf("INVALID\n");
                }
                break;
            
            case 52:
                if (validation % 10 == 0 && count == 16)
                {
                    printf("MASTERCARD\n");
                    
                }
                else
                {
                    printf("INVALID\n");
                }
                break;
            
            case 53:
                if (validation % 10 == 0 && count == 16)
                {
                    printf("MASTERCARD\n");
                    
                }
                else
                {
                    printf("INVALID\n");
                }
                break;
            
            case 54:
                if (validation % 10 == 0 && count == 16)
                {
                    printf("MASTERCARD\n");
                    
                }
                else
                {
                    printf("INVALID\n");
                }
                break;
            
            case 55:
                if (validation % 10 == 0 && count == 16)
                {
                    printf("MASTERCARD\n");
                    
                }
                else
                {
                    printf("INVALID\n");
                }
                break;
            
            default:
                printf("INVALID\n");
        }
    }
    
    
    
    
    
    
}

long int doubledigit(long int cardnum, long int i)
{
    long int doubledig;
    
    doubledig = (((cardnum % i) - (cardnum % (i / 10))) / (i / 10)) * 2;
    return doubledig;
}