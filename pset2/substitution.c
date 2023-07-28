#include<stdio.h>
#include<cs50.h>
#include<string.h>



int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    else if (strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    else
    {
        for (int i = 0; i < 26; i++)
        {
            if (argv[1][i] < 65 || (argv[1][i] > 90 && argv[1][i] < 97) || argv[1][i] > 122)
            {
                return 1;
            }
        }
        for (int i = 0; i < 26; i++)
        {
            for (int j = i + 1; j < 26 - i; j++)
            {
                if (argv[1][i] == argv[1][j])
                {
                    return 1;
                }
            }
        }

        string plaintext = get_string("plaintext: ");

        printf("ciphertext: ");
        int length = strlen(plaintext);

        for (int i = 0; i < length; i++)
        {
            if ((plaintext[i] >= 65 && plaintext[i] <= 90) || (plaintext[i] >= 97 && plaintext[i] <= 122))
            {
                for (int j = 0; j < 26; j++)
                {
                    if (plaintext[i] == 97 + j)
                    {
                        if (argv[1][j] >= 97)
                        {
                            printf("%c", argv[1][j]);
                        }
                        else
                        {
                            printf("%c", argv[1][j] + 32);
                        }
                    }
                    if (plaintext[i] == 65 + j)
                    {
                        if (argv[1][j] <= 90)
                        {
                            printf("%c", argv[1][j]);
                        }
                        else
                        {
                            printf("%c", argv[1][j] - 32);
                        }
                    }
                }
            }
            else
            {
                printf("%c", plaintext[i]);
            }

        }
        printf("\n");
    }
}

