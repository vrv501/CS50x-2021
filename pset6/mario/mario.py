def main():
    steps = get_positive_num()
    for i in range(1, (steps + 1)):
        print(f"{' ' * (steps - i)}{'#' * i}  {'#' * i}")


def get_positive_num():
    while True:
        n = input("Height: ")
        if n.isdigit():
            n = int(n)
            if 0 < n < 9:
                break
    return n


main()