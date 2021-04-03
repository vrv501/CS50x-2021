from sys import exit

def main():

    # Get positive change
    change = getChange()

    # printCoins
    coins(change)


def getChange():
    while True:
        change = input("Number: ")
        try:
            change = float(change)
            if (change > 0):
                break
        except:
            continue
    change = round(change * 100)
    return change


def coins(change):

    # Number of 25 cent coins required
    cents25 = change // 25
    change -= (cents25 * 25)

    # Number of 10 cent coins required
    cents10 = change // 10
    change -= (cents10 * 10)

    # Number of 5 cent coins required
    cents5 = change // 5
    change -= (cents5 * 5)

    # Number of 1 cent coins required
    cents1 = change

    totalCoins = cents25 + cents10 + cents5 + cents1
    print(f"{totalCoins}")


main()
