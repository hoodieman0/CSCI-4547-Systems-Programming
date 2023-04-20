# Written by AI
# Checks for duplicate job IDs in Threads output
# Redirect output to output.txt like: ./Threads > output.txt
# ChatGPT was doing a very poor job of this so I figured I'd see if it could write a script that could do it better 

import re

# open the file and read its contents
with open('output.txt', 'r') as file:
    data = file.read()

# find all instances of Job [0-9][0-9]
matches = re.findall(r'Job \d{2}', data)

# count the frequency of each match
freq = {}
for match in matches:
    if match in freq:
        freq[match] += 1
    else:
        freq[match] = 1

# print out the repeated matches, if any
repeated = False
for match, count in freq.items():
    if count > 1:
        print(match, "is repeated", count, "times")
        repeated = True

# if no matches are repeated, print "No matches"
if not repeated:
    print("No matches")
