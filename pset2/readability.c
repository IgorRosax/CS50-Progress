#include<stdio.h>
#include<cs50.h>
#include<string.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);
int round_to_nearest(float number);

int main(void)
{
    string text = get_string("Text: ");
    int index;
    index = round_to_nearest(0.0588 * ((float) count_letters(text) / (float)count_words(text)) * 100 - 0.296 * ((float) count_sentences(
                                 text) / (float)count_words(text)) * 100 - 15.8);

    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }

}

int count_letters(string text)
{
    int counter = 0, length = strlen(text);

    for (int i = 0; i < length; i++)
    {
        if ((text[i] >= 65 && text[i] <= 90) || (text[i] >= 97 && text[i] <= 122))
        {
            counter++;
        }
    }

    return counter;
}

int count_words(string text)
{
    int counter = 0, length = strlen(text);

    for (int i = 0; i < length; i++)
    {
        if (((text[i] >= 65 && text[i] <= 90) || (text[i] >= 97 && text[i] <= 122)) && (text[i + 1] == 32 || text[i + 1] == 33
                || text[i + 1] == 44 || text[i + 1] == 46 || text[i + 1] == 58 || text[i + 1] == 59 || text[i + 1] == 63))
        {
            counter++;
        }
    }

    return counter;
}

int count_sentences(string text)
{
    int counter = 0, length = strlen(text);

    for (int i = 0; i < length; i++)
    {
        if (((text[i] >= 65 && text[i] <= 90) || (text[i] >= 97 && text[i] <= 122)) && (text[i + 1] == 33 || text[i + 1] == 46
                || text[i + 1] == 63))
        {
            counter++;
        }
    }

    return counter;
}

int round_to_nearest(float number)
{
    if ((number - (int)number) > 0.5)
    {
        number = (int) number + 1;
    }
    else
    {
        number = (int)number;
    }
    return number;
}