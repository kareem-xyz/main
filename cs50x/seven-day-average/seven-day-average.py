import csv
import requests


def main():
    # Read NYTimes Covid Database
    download = requests.get(
        "https://raw.githubusercontent.com/nytimes/covid-19-data/master/us-states.csv"
    )
    decoded_content = download.content.decode("utf-8")
    file = decoded_content.splitlines()
    reader = csv.DictReader(file)

    # Construct 14 day lists of new cases for each states
    new_cases = calculate(reader)

    # Create a list to store selected states
    states = []
    print("Choose one or more states to view average COVID cases.")
    print("Press enter when done.\n")

    while True:
        state = (input("State: ").lower()).capitalize()
        if state in new_cases:
            states.append(state)
        if len(state) == 0:
            break

    print(f"\nSeven-Day Averages")

    # Print out 7-day averages for this week vs last week
    comparative_averages(new_cases, states)


# TODO: Create a dictionary to store 14 most recent days of new cases by state
def calculate(reader):
    # load data to memory.
    reader_row = list(reader)
    # dicts for daily cases
    daily_cases = {}
    prev_cases = {}

    # initialising lists and dicts
    for states in reader_row:
        cur_state = states["state"]
        prev_cases[cur_state] = 0
        daily_cases[cur_state] = []

    for states in reader_row:
        cur_state = states["state"]
        cur_cases = int(states["cases"])

        # if there are new cases (to avoid death causing a problem with previous cases)
        if cur_cases > prev_cases[cur_state]:
            new_cases = cur_cases - prev_cases[cur_state]
            prev_cases[cur_state] = cur_cases

        else:
            prev_cases[cur_state] = cur_cases

        (daily_cases[cur_state]).append(new_cases)

        # if past 2 weeks delete the first number
        if len(daily_cases[cur_state]) > 14:
            # prev_cases[cur_state] -= daily_cases[cur_state][0]
            del (daily_cases[cur_state])[0]

    return daily_cases


# TODO: Calculate and print out seven day average for given state
def comparative_averages(new_cases, states):

    avg1 = avg2 = 0
    # for every state chosen
    for state in states:
        sum1 = 0
        sum2 = 0
        avg1 = 0
        avg2 = 0

        # for every day in the first week
        for i in range(7):
            sum1 += (new_cases[state])[i]
        avg1 += sum1 // 7


        #USING LIST SLICING
        #for case in (new_cases[state])[0:7]:
            #sum1 += case
        #avg1 = sum1 // 7

        # for every day in the second week (start from 7 till end at 1 step)
        for i in range(7, 14,):
            sum2 += (new_cases[state])[i]
        avg2 += sum2 // 7

        try:
            diff = (avg1 - avg2) / avg2
            diff *= 100
        except ZeroDivisionError:
            diff = avg1

        if diff > 0:
            print(f"{state} had a 7-day average of {avg1} and an increase of {abs(diff):.2f}%.")
        else:
            print(f"{state} had a 7-day average of {avg1} and a decrease of {abs(diff):.2f}%.")
        #print(f"avg1 = {avg1}, avg2 = {avg2}")

main()
