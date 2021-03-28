from sys import exit


def main():

    # Get positive change
    penny = getChange()

    # printCoins
    coins(penny)


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


def coins(penny):

    # Number of 25 cent coins required
    cents25 = penny // 25
    penny = penny - (cents25 * 25)

    # Number of 10 cent coins required
    cents10 = penny // 10
    penny = penny - (cents10 * 10)

    # Number of 5 cent coins required
    cents5 = penny // 5
    penny = penny - (cents5 * 5)

    # Number of 1 cent coins required
    cents1 = penny

    totalCoins = cents25 + cents10 + cents5 + cents1
    print(f"{totalCoins}")


main()
