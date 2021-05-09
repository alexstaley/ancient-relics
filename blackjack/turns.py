#Assignment 5 -- Stepback Blackjack -- Alex Staley

import random

#Player's turn:

def turnPlayer(total, totalAce, ace, blackjack, bust):
  while (total <= 21) and (blackjack == False):
    hit = str(input("\nHit? "))
    if hit == ("") or hit == ("Yes") or hit == ("yes") or hit == ("YES") or hit == ("y") or hit == ("Y") or hit == ("hit") or hit == ("Hit") or hit == ("HIT"):
      triggerPlayer = random.randint(0,12)
    #player is dealt an 8:
      if triggerPlayer == 6:
        cardPlayer = 8
        total += 8
        if ace:
          totalAce += 8
        if (total == 21) or (totalAce == 21):
          print ("An 8 ... 21!!! ")
          total = 21
          totalAce = 0
          break
        elif (total == 10) and (totalAce == 20):
          print ("It's an 8\nYou now have 10 or 20 ")
        else:
          print ("It's an 8\nYou now have", total )
    #player is dealt a 2-10:
      elif triggerPlayer <= 8:
        cardPlayer = triggerPlayer + 2
        total += cardPlayer
        if ace:
          totalAce = total + 10
        if (total == 21) or (totalAce == 21):
          print ("A", cardPlayer, "... 21!!! ")
          total = 21
          totalAce = 0
          break
        else:
          if (ace == True) and (total <= 10):
            print ("It's a", cardPlayer, "\nYou now have", total, "or", totalAce)
          else:
            print ("It's a", cardPlayer, "\nYou now have", total )
    #player is dealt a face card:
      elif triggerPlayer <= 11:
        cardPlayer = 10
        total += 10
        if triggerPlayer == 9:
          if total == 21:
            print ("A Jack ...21!!! ")
            totalAce = 0
            break
          else:
            print ("It's a Jack\nYou now have", total )
        elif triggerPlayer == 10:
          if total == 21:
            print ("A Queen ...21!!! ")
            totalAce = 0
            break
          else:
            print ("It's a Queen\nYou now have", total )
        else:
          if total == 21:
            print ("A King ...21!!! ")
            totalAce = 0
            break
          else:
            print ("It's a King\nYou now have", total)
    #player is dealt an ace:
      elif triggerPlayer == 12:
        cardPlayer = 1
        ace = True
        total += 1
        if (total == 11) or (total == 21):
          print ("An ace ...21!!! ")
          total = 21
          totalAce = 0
          break
        elif total <=10:
          totalAce = total + 10
          print ("An ace\nYou now have", total, "or", totalAce)
        else:
          print ("It's an ace\nYou now have", total )
  #player does not hit:
    else:
      if total <= 11:
        if ace:
          total += 10
          totalAce = 0
          print ("\nYou're standing on", total)
          break
        else:
          print ("\nWho are you, Austin Powers? You're standing on", total)
          break
      else:
        print ("You're standing on", total)
        break
  if total > 21:
    bust = True
  else:
    bust = False
  return total, ace, bust

#Dealer's turn:

def turnDealer(totalDealer, totalDealAce, aceDealer, blackjack, blackjackDealer, bust):
  if (blackjack == False) and (bust == False) and (blackjackDealer == False):
    while True:
      if totalDealer >= 17:
        break
      triggerDealer = random.randint(0,12)
    #dealer draws an 8:
      if triggerDealer == 6:
        draw = 8
        totalDealer += 8
        if aceDealer:
          if totalDealer == 11:
            print ("\nDealer draws an 8 ...makes 21 ")
            totalDealer += 10
            totalDealAce = 0
            break
          elif totalDealer == 10:
            print ("\nDealer draws an 8 ...stands on 20 ")
            totalDealer += 10
            totalDealAce = 0
            break
          elif totalDealer <= 16:
            print ("\nDealer draws an 8 ...total", totalDealer)
          elif totalDealer <= 21:
            print ("\nDealer draws an 8 ...stands on", totalDealer)
            break
          else:
            print ("\nDealer draws an 8 ...total", totalDealer)
        else:
          print ("\nDealer draws an 8 ...total", totalDealer)
    #dealer draws a 2-10:
      elif triggerDealer <= 8:
        draw = triggerDealer + 2
        totalDealer += draw
        if aceDealer:
          totalDealAce = totalDealer + 10
          if totalDealer == 11:
            print ("\nDealer draws a", draw, "...makes 21 ")
            totalDealer = 21
            totalDealAce = 0
            break
          elif totalDealer <= 7:
            totalDealAce = totalDealer + 10
            print ("\nDealer draws a", draw, "...total", totalDealer, "or", totalDealAce)
          elif totalDealer <= 10:
            totalDealer += 10
            totalDealAce = 0
            print ("\nDealer draws a", draw, "...stands on", totalDealer)
            break
          elif totalDealer <= 16:
            totalDealAce = 0
            print ("\nDealer draws a", draw, "...total", totalDealer)
          elif totalDealer <= 20:
            totalDealAce = 0
            print ("\nDealer draws a", draw, "...stands on", totalDealer)
            break
          elif totalDealer == 21:
            totalDealAce = 0
            print ("\nDealer draws a", draw, "...makes 21 ")
            break
          else:
            print ("\nDealer draws a", draw, "...total", totalDealer)
            break
        else:
          print ("\nDealer draws a", draw, "...total", totalDealer)
    #dealer draws a face card:
      elif triggerDealer <= 11:
        draw = 10
        totalDealer += 10
        totalDealAce = 0
        if triggerDealer == 9:
          print ("\nDealer draws a Jack ...total", totalDealer)
        elif triggerDealer == 10:
          print ("\nDealer draws a Queen ...total", totalDealer)
        else:
          print ("\nDealer draws a King ...total", totalDealer)
    #dealer draws an ace:
      else:
        draw = 1
        aceDealer = True
        totalDealer += 1
        if totalDealer <= 7:
          totalDealAce = totalDealer + 10
          print ("\nDealer draws an ace ...total", totalDealer, "or", totalDealAce)
        elif totalDealer <= 10:
          totalDealer += 10
          totalDealAce = 0
          print ("\nDealer draws an ace ...stands on", totalDealer)
          break
        elif totalDealer == 11:
          totalDealer = 21
          totalDealAce = 0
          print ("\nDealer draws an ace ...and makes 21. ")
          break
        else:
          print ("\nDealer draws an ace ...total", totalDealer)
  return totalDealer