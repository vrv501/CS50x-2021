import re

text = input("Text: ")
l = re.sub("[^\w\s?!.]", "", text).split(' ') #replace anything other than (letters, white space, ?, !, .) with ""
print(l)
letters = 0
sentences = 0
words = len(l)

for word in l:
    sen = word.count('.') + word.count('!') + word.count('?')
    letters += (len(word) - sen)
    sentences += sen

letters = (letters * 100) / words
sentences = (sentences * 100) / words
index = round(((0.0588 * letters) - (0.296 * sentences) - 15.8))

if index < 1:
    print("Before Grade 1")
elif index > 15:
    print("Grade 16+")
else:
    print(f"Grade {index}")

