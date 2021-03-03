from sys import argv, exit
import csv


if len(argv) != 3:
    print(f"Usage: python {argv[0]} data.csv sequence.txt")
    exit(1)

with open(argv[1], "r") as db:
    dna_list = []
    db_dict = {}
    for line in db:
        current_dna_list = line.rstrip("\n").split(',')
        if len(dna_list) == 0:
            for word in current_dna_list[1:]:
                dna_list.append(word)
            continue
        db_dict["".join(current_dna_list[1:])] = current_dna_list[0]

with open(argv[2], "r") as seq:
    input_seq = seq.read().rstrip("\n")

length = len(input_seq)
str_key = ""
for str_seq in dna_list:       #dna_list is a list having str's whose count has to be determined from input seq
    i = 0
    str_len = len(str_seq)
    max_num = 0
    curr_count = 0
    while i < length:
        if input_seq[i:i + str_len] == str_seq:  #input_seq is self explanatory
            curr_count += 1
            i += str_len
        else:
            if curr_count > max_num:
                max_num = curr_count
            curr_count = 0
            i += 1
    str_key += str(max_num)

if str_key not in db_dict:      # db_dict is a dictionary having key as counts of str's(combined as string) and name as value ex: d[415] = "bob" 4-AATG 1-TATAG 4-AGTC
    print("No match")
else:
    print(db_dict[str_key])