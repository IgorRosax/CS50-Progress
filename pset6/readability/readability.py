from cs50 import get_string
from math import floor, ceil


def main():
    text = get_string("Text: ")

    Grade = 0.0588 * ((count_letters(text) / count_words(text)) * 100) - 0.296 * ((count_sentences(text) / count_words(text)) * 100) - 15.8

    if Grade >= 16:
        print("Grade 16+")
    elif Grade < 1:
        print("Before Grade 1")
    elif Grade - floor(Grade) < 0.5:
        print(f"Grade {floor(Grade)}")
    else:
        print(f"Grade {ceil(Grade)}")


def count_letters(txt):
    lcounter = 0
    for i in range(len(txt)):
        if txt[i].isalpha() == True:
            lcounter += 1

    return lcounter


def count_words(txt):
    wcounter = 0
    for i in range(len(txt)):
        if txt[i].isalpha() == True:
            if txt[i + 1].isalpha() == False and txt[i + 1] != "'" and txt[i + 1] != "-":
                wcounter += 1

    return wcounter


def count_sentences(txt):
    scounter = 0
    for i in range(len(txt)):
        if txt[i] == "." or txt[i] == "!" or txt[i] == "?":
            scounter += 1

    return scounter


main()
