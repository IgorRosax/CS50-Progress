from cs50 import SQL
import sys


def main():
    if len(sys.argv) != 2:
        print("Usage: python import.py House")
        exit()

    db = SQL("sqlite:///students.db")
    reader = db.execute("SELECT first, middle, last, birth FROM students WHERE house = ? ORDER BY last, first", sys.argv[1])

    for row in reader:
        if row['middle'] == None:
            print(row['first'], " ", row['last'], ", born ", row['birth'], sep='')
        else:
            print(row['first'], " ", row['middle'], " ", row['last'], ", born ", row['birth'], sep='')


main()