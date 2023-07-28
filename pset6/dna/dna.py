import sys
import csv
import re


def main():
    if len(sys.argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")

    else:
        with open(sys.argv[1], newline='\n') as csvfile:
            reader = csv.DictReader(csvfile)
            STRseq = reader.fieldnames[1: len(reader.fieldnames)]
            STRseq_counter = []
            for i in range(len(STRseq)):
                STRseq_counter.append(0)

            with open(sys.argv[2]) as sqcfile:
                sqc = sqcfile.read()

                for i in range(len(STRseq)):
                    matches = re.finditer(STRseq[i], sqc)
                    j = 0
                    previous_end = None
                    for match in matches:
                        if j == 0:
                            j += 1
                            if j > STRseq_counter[i]:
                                STRseq_counter[i] = j

                        if previous_end == match.span()[0]:
                            j += 1
                            if j > STRseq_counter[i]:
                                STRseq_counter[i] = j
                        else:
                            j = 1

                        previous_end = match.span()[1]
                for row in reader:
                    for x in range(len(STRseq_counter)):
                        if int(row[STRseq[x]]) != STRseq_counter[x]:
                            break
                        elif x == len(STRseq_counter) - 1:
                            print(row['name'])
                            exit(0)
        print("No match")
        exit(0)


main()
