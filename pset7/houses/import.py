from cs50 import SQL
import sys
import csv
import re


def main():
    if len(sys.argv) != 2 or re.match(".+\.csv$", sys.argv[1]) == None:
        print("Usage: python import.py filename.csv")
        exit()
        
    with open(sys.argv[1], "r") as csvfile:
        reader = csv.DictReader(csvfile)
        db = SQL("sqlite:///students.db")

        for row in reader:
            splited = re.split("\s", row['name'])
            if len(splited) < 3:
                db.execute("INSERT INTO students (first, last, house, birth) VALUES (?, ?, ?, ?)",
                           splited[0], splited[1], row['house'], row['birth'])
            else:
                db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES (?, ?, ?, ?, ?)",
                           splited[0], splited[1], splited[2], row['house'], row['birth'])


main()