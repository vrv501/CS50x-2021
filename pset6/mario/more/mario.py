def main():

    # Get steps from user
    steps = get_positive_num()

    # Print the pyramid
    for row in range(1, (steps + 1)):
        print(f"{' ' * (steps - row)}{'#' * row}  {'#' * row}")


def get_positive_num():
    while True:
        steps = input("Height: ")
        if steps.isdigit():
            steps = int(steps)
            if 0 < steps < 9:   # Accept steps in range(0 to 9) exclusive
                break
    return steps


main()
