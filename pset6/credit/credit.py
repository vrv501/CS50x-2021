from sys import exit


def main():

    # Get positive card number
    cardNumber = get_positive_num()

    # Check validity of card and print brand
    check(cardNumber)


def get_positive_num():
    while True:
        number = input("Number: ")
        if number.isdigit() and int(number) > 0:
            break
    return number


def check(cardNumber):
    length = len(cardNumber)

    # If valid length
    if length in [13, 15, 16]:
        checkSum = 0

        # Loop over every character to find checkSum
        for digitPosition in range(0, length):
            digit = int(cardNumber[(length - digitPosition - 1)])
            if digitPosition % 2 != 0:
                digit *= 2
                if digit > 8:
                    digit -= 9
            checkSum += digit

        # Identify whether checkSum satisfies Luhn's algorithm
        if checkSum % 10 == 0:

            # Conditions for VISA
            if length == 13 and cardNumber[0] == '4':
                print("VISA")
                exit(0)

            # Conditions for AMEX
            elif length == 15 and cardNumber[:2] in ["34", "37"]:
                print("AMEX")
                exit(0)

            else:

                # Conditions for VISA
                if cardNumber[0] == '4':
                    print("VISA")
                    exit(0)

                # Conditions for MASTER-CARD
                elif 50 < int(cardNumber[:2]) < 56:
                    print("MASTERCARD")
                    exit(0)

    print("INVALID")
    exit(1)


main()
