# Assignment 5 -- Stepback Blackjack -- Alex Staley

# Resolving final score, counting wins/losses:

def finalScore(total, totalDealer, blackjack, blackjackDealer, bust):
    win = False
    tie = False

    if bust:
        print("\n...BUSTED!\n:( ")
    if blackjack:
        if blackjackDealer:
            tie = True
            print(
                "\nbut hey,\tIT'S LIKE BLACKJACK CITY OVER HERE!\n\tTable's hot! Please provide credit card number\n\t\t$$$$$$$$$$ ")
        else:
            win = True
            print("\n\tYOU WIN!!! ")
    if (blackjack == False) and (bust == False):
        if totalDealer > 21:
            win = True
            print("\nDealer busts!\n\n\tYOU WIN!!!")
        elif totalDealer == 21:
            if not blackjackDealer:
                print("\nYou have", total)
                if (total == 21):
                    tie = True
                    print("\nA push... and on 21! What a shame ")
                elif total < 21:
                    print("\nYou lose. ")
            else:
                print("\nLet's try that again! ")
        elif totalDealer < 21:
            print("\nYou have", total)
            if total > totalDealer:
                win = True
                print("\n\tYOU WIN!!! ")
            elif total < totalDealer:
                print("\nYou lose. ")
            elif total == totalDealer:
                tie = True
                print("\nA push... meh ")
    return win, tie