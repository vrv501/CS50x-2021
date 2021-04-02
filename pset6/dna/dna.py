from sys import argv, exit
import csv


if len(argv) != 3:
    print(f"Usage: python {argv[0]} data.csv sequence.txt")
    exit(1)

peopleDNAinfo = []
STRS = None
with open(argv[1], "r") as db:
    reader = csv.DictReader(db)
    STRS = reader.fieldnames[1:]

    # Convert counts of STRS of every person into integers
    for person in reader:
        for STR in STRS:
            person[STR] = int(person[STR])
        peopleDNAinfo.append(person)

# Input seq from CL arguments
inputSeq = None
with open(argv[2], "r") as seq:
    inputSeq = seq.read().rstrip("\n")

inputSeqLen = len(inputSeq)
# Empty dictionary
inputSeqSTRCount = {}

# Loop over seq to calculate STR count
for STR in STRS:
    # For every STR, initialise helper variables
    STRlen = len(STR)
    currCount = 0
    maxCount = 0
    index = 0

    # Loop over inputSeq for finding maxcount of consecutive STR
    while index < inputSeqLen:
        if inputSeq[index: (index + STRlen)] == STR:
            currCount += 1
            index += STRlen
        else:
            if currCount > maxCount:
                maxCount = currCount
            currCount = 0
            index += 1

    inputSeqSTRCount[STR] = maxCount

for person in peopleDNAinfo:
    found = True

    # Equate counts of STR of a person in database to inputSeq
    for STR in STRS:

        # If any STR count doesn't match, we stop and move onto next person
        if person[STR] != inputSeqSTRCount[STR]:
            found = False
            break
    if (found):
        print(f"{person['name']}")
        exit(0)

print("No match")

