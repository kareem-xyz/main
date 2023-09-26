import sys


# Dict to store values
main_dict = {"letter_count": 0, "sent_count": 0, "word_count": 0}


def main():

    # Get text and length
    text = input("Input Text:\n")
    length = len(text)

    # Calculate letters, words, and sentences in text. (Stored in main_dict)
    num_variables(text, length)
    sent_count = main_dict["sent_count"]
    word_count = main_dict["word_count"]
    letter_count = main_dict["letter_count"]

    # Catching errors
    if (letter_count == 0 or sent_count == 0):
        print("ERORR: Please make sure your write at least one word, and use punctuation marks")
        sys.exit(1)

    # Average of letters per 100 words
    letter_avg = (letter_count / word_count) * 100

    # Average of sentences per 100 words
    sent_avg = (sent_count / word_count) * 100

    # Apply and print the index number rounded
    index = round(0.0588 * letter_avg - 0.296 * sent_avg - 15.8)
    if (index < 16 and index >= 1):
        print(f"Grade {index}")

    elif (index >= 16):
        print("Grade 16+")

    elif (index < 1):
        print("Before Grade 1")

    else:
        print("Something went wrong!")
        sys.exit(2)


def num_variables(text, length):
    # Temp variables for counting. words starts at 1 because the last word, the one that doesn't have a space after the end of the sentence, wont be recorded otherwise.
    l = 0
    w = 1
    s = 0
    for i in range(length):
        if (text[i].isalpha()):
            l += 1

        elif (text[i].isspace()):
            w += 1

        elif (text[i] == '.' or text[i] == '?' or text[i] == '!'):
            s += 1

    main_dict["letter_count"] = l
    main_dict["word_count"] = w
    main_dict["sent_count"] = s


main()