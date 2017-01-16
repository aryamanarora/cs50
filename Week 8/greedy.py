def main():
    # change owed
    try:
        money = float(input("O hai! How much change is owed?\n"))
    except:
        print("That isn't a float...")
        exit(1)
    while money < 0:
        money = float(input("You can only have positive money!\n"))

    # convert to cents
    money = int(money * 100)

    # count
    count = counter(money)
    print(count)


def counter(money):
    count = 0
    while money > 0:
        for val in [25, 10, 5, 1]:
            max_coins = money // val
            count += max_coins
            money -= max_coins * val
    return count


if __name__ == "__main__":
    main()
