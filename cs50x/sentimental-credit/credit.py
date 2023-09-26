import sys


def main():
    num = input("Credit card number:")
    length = len(num)
    num = int(num)

    # Variables used for Lohn Checksum rules
    n = num
    oddlast = 0
    evenlast = 0
    doubleeven = 0
    oddsum = 0
    evensum = 0
    total = 0

    while (n > 0):

        # Sums up odd powers from right to left
        oddlast = n % 10
        n //= 10
        oddsum += oddlast

        # Sums up 2 * even ranks from right to left
        evenlast = n % 10
        doubleeven = 2 * evenlast
        n //= 10

        # Because doubleeven might be > 9. for example in (doubleeven = 18, we want to do:
        # evensum += 8, and evensum += 1
        while (doubleeven > 0):
            evensum += doubleeven % 10
            doubleeven //= 10

    total = oddsum + evensum

    # Lohn Checksum condition
    if ((total % 10) != 0):
        print("INVALID")
        sys.exit(0)

    # Specifications for Visa
    elif (length == 13 and oddlast == 4) or (length == 16 and evenlast == 4):
        print("VISA")
        sys.exit(0)

    # Specifications for American Express Card
    elif (length == 15 and isAMEX(num)):
        print("AMEX")
        sys.exit(0)

    elif (length == 16 and isMASTERCARD(num)):
        print("MASTERCARD")
        sys.exit(0)

    else:
        print("INVALID")


# Checks whether a given number is an American express, returns bool
def isAMEX(number):
    # Get first two digits in number (from left side)
    # The number 13 because AMEX numbers come in 15 digits only, and we want to left
    number //= (10 ** 13)

    if number in [34, 37]:
        return True

    else:
        return False


# Checks whether a given number is a Mastercard, returns bool
def isMASTERCARD(number):
    # Get first two digits in number (from left side)
    # The number 14 because MASTERCARD numbers come in 16 digits only, and we want to left
    number //= (10 ** 14)

    if number in [51, 52, 53, 54, 55]:
        return True

    else:
        return False


main()