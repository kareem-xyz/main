# Week 6 Practise P
# On Dicts, a program that takes users order from a menu and prints the total cost.

menu = {
    "Baja Taco": 4.00,
    "Burrito": 7.50,
    "Bowl": 8.50,
    "Nachos": 11.00,
    "Quesadilla": 8.50,
    "Super Burrito": 8.50,
    "Super Quesadilla": 9.50,
    "Taco": 3.00,
    "Tortilla Salad": 8.00
        }
total = 0

while True:
    try:

        item = input("Item: ").lower().title()
        if item in menu:
            total += menu[item]
            print("Total: $%0.2f" % (total))

    # when user types ctrl-d break the loop and exit program
    except EOFError:
        print("\n")
        break

