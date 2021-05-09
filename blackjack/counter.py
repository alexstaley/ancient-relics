#Assignment 5 -- Stepback Blackjack -- Alex Staley

#Introducing game, counting hands:

def count(hands):
  if hands == 0:
    print ("Let's play blackjack!\n*deals cards* ")
  elif hands <= 3:
    print ("\nWhoop whoop! Let's play some blackjack!\n*deals cards* ")
  elif hands <= 8:
    print ("\nLet's play blackjack... again!\n*deals cards* ")
  elif hands <= 10:
    print ("\nK just so you know this'll be hand number", (hands + 1), "and there's a whole world out there. Just saying.\n*deals cards* ")
  elif hands <= 11:
    print ("\nThis is hand", (hands + 1), "and I mean no judgment by that but I also know that there are resources out there for people who need help.\n*reluctantly deals cards*")
  elif hands <= 12:
    print ("\nHand", (hands + 1), "... You DO know there's no money involved here ...right?\n*shakes head, deals cards* ")
  elif hands == 13:
    problem = str(input("\nThis has gone far enough. If you want another hand please type the words 'I have a problem'. "))
    while not (problem == ("I have a problem") or problem == ("I have a problem.") or problem == ("i have a problem") or problem == ("i have a problem.")):
      problem = str(input("\nNot quite. Please type the words 'I have a problem'. "))
    if problem == ("I have a problem"):
      print ("\n*stares; deals cards*\nThis is hand", (hands + 1), "by the way. ")
    else:
      print ("\n*stares; deals cards*\nClose enough. This is hand", (hands + 1), "by the way. ")
  elif hands == 14:
    print ("\n\n\tOK, I give up. I'll just deal the cards.\nAnd count the hands, since I was dumb enough to open up that can of worms. Enjoy.\nHand", (hands + 1), "\n*deals cards*")
  else:
    print ("\nHand", (hands + 1), "\n*deals cards*")
  hands += 1
  return hands

#Determining if rematch:

def rematch (games):
  if (games >= 11) and (games <= 14):
    again = str(input("\n\nI'm almost afraid to ask, but... are we playing again? "))
  else:
    again = str(input("\n\nIn for another hand? "))
  if again == ("") or again == ("Yes") or again == ("yes") or again == ("YES") or again == ("y") or again == ("Y"):
    return True
    print ("\n\n")
  else:
    print ("\nYou'll be back. They all come back. ")
    return False

#Defining Player's record:

def record(win, tie, wins, losses, ties):
  if win:
    wins += 1
  else:
    losses += 1
  if tie:
    ties += 1
    losses -= 1
  return wins, losses, ties

#Displaying Player's record:

def exit(wins, losses, ties):
  if ties == 0:
    print ("\n\tYour record this time was", wins, "-", losses)
  elif ties == 1:
    print ("\n\tYour record this time was", wins, "-", losses, "with one tie. ")
  else:
    print ("\n\tYour record this time was", wins, "-", losses, "with", ties, "ties. ")