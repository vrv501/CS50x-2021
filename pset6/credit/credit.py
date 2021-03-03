from sys import exit


def main():
    number = get_positive_num()
    check(number)


def get_positive_num():
    while True:
        n = input("Number: ")
        if n.isdigit() and int(n) > 0:
            break
    return n


def check(number):
    length = len(number)
    if length in [13, 15, 16]:
        tot_sum = 0
        len1 = length - 1
        for i in range((length - 1), -1, -1):
            j = i - len1
            if j % 2 == 0:
                tot_sum += int(number[i])
            else:
                x = int(number[i])
                if x < 5:
                    x = x * 2
                else:
                    x = (x * 2) - 9
                tot_sum += x

        if tot_sum % 10 == 0:
            if length == 13 and number[0] == '4':
                print("VISA")
                exit(0)
            elif length == 15 and number[:2] in ["34", "37"]:
                print("AMEX")
                exit(0)
            else:
                if number[0] == '4':
                    print("VISA")
                    exit(0)
                elif 50 < int(number[:2]) < 56:
                    print("MASTERCARD")
                    exit(0)

    print("INVALID")
    exit(1)


main()