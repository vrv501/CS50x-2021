import re

text = input("Text: ")

# Replace anything other than letters, white space, ?, !, . with "". After that split text into a list using " " as delimiter
preProcessText = re.sub("[^\w\s?!.]", "", text).split(' ')

letters = 0
sentences = 0

# The number of words are obviously length of preProcessText
words = len(preProcessText)

for word in preProcessText:

    # Count punctuation which are indicaters of end of sentence
    punctuation = word.count('.') + word.count('!') + word.count('?')

    # Removing punctuation to find number of letters
    letters += (len(word) - punctuation)

    # Punctuation are indication of end of sentence
    sentences += punctuation

# Coleman-Liau index for grade calculation
letters = (letters * 100) / words
sentences = (sentences * 100) / words
index = round(((0.0588 * letters) - (0.296 * sentences) - 15.8))

if index < 1:
    print("Before Grade 1")
elif index > 15:
    print("Grade 16+")
else:
    print(f"Grade {index}")
