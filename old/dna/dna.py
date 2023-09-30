import csv
import sys


def main():

    # Check for correct usage
    if len(sys.argv) != 3:
        print("ERORR: Usage: python dna.py (database.txt) (sequence.txt)")
        sys.exit(1)

    """________READ DATABASE TO MEMORY________"""
    # Initialise the main dictionary, and (short tandem repeats phrases) used in the checking
    dict_datab = {}
    str_s = []
    name_datab = sys.argv[1]
    name_sequn = sys.argv[2]
    with open(name_datab, 'r', newline='') as csv_datab:
        # load STRS to be used. (Also fieldnames for dictreader later)
        str_s = (csv_datab.readline()).replace('\n', '').split(",")

        # Read data for each row, and store it in a nested dict inside the main dict_datab.
        # key is name, value is a dict containing the DNA data.
        reader = csv.DictReader(csv_datab, fieldnames=str_s)
        for row in reader:
            name = row["name"]
            dict_datab[name] = row

            # Remove the name field from the nested dict (already present as key in main dict), this is important for converting values. So No need to handle exceptions.
            del (dict_datab[name])["name"]

            # Convert values to integers using dictionary comprehension
            dict_datab[name] = dict([str_tmp, int(rpt_tmp)] for str_tmp, rpt_tmp in dict_datab[name].items())

    """________Read DNA sequence file to memory________"""
    # Read DNA sequence
    file_sequence = open(name_sequn, 'r')
    txt_sequn = file_sequence.readline()

    # Dict to hold data of str_s for the read sequence
    profile = {}

    # Find longest match (repeated sequence) of each STR in DNA sequence
    str_s.remove("name")
    for str_ in str_s:
        rpt_str = longest_match(txt_sequn, str_)
        profile[str_] = rpt_str

    # Check database for matching profiles
    for p in dict_datab:
        if profile == dict_datab[p]:
            # Print name of person matching
            print(p)
            sys.exit(0)
    # Else
    print("No match")


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
