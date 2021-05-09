#Assignment 5 -- Stepback Blackjack -- Alex Staley

#Dealing Player's cards (triggerA,C = first and third cards dealt):

def dealPlayer (triggerA, triggerC):

  ace = False
  blackjack = False

#first card:
  if triggerA <= 8:
    card1 = triggerA + 2
    print ("\nYour first card:", card1)
  elif triggerA <= 11:
    card1 = 10
    if triggerA == 9:
      print ("\nYour first card: Jack ")
    elif triggerA == 10:
      print ("\nYour first card: Queen ")
    elif triggerA == 11:
      print ("\nYour first card: King ")
  elif triggerA == 12:
    card1 = 1
    ace = True
    print ("\nYour first card: Ace ")
#second card:
  if triggerC <= 7:
    card2 = triggerC + 2
    if triggerA == triggerC:
      print ("Your second card: another", card2)
    else:
      print ("Your second card:", card2)
  elif triggerC <= 11:
    card2 = 10
    if triggerC == 8:
      if card1 == 1:
        print ("Your second card: a 10! ")
      elif triggerA == 8:
        print ("Your second card: another 10 ")
      else:
        print ("Your second card: 10 ")
    elif triggerC == 9:
      if card1 == 1:
        print ("Your second card: a Jack! ")
      elif triggerA == 9:
        print ("Your second card: another Jack ")
      else:
        print ("Your second card: Jack ")
    elif triggerC == 10:
      if card1 == 1:
        print ("Your second card: a Queen! ")
      elif triggerA == 10:
        print ("Your second card: another Queen ")
      else:
        print ("Your second card: Queen ")
    elif triggerC == 11:
      if card1 == 1:
        print ("Your second card: a King! ")
      elif triggerA == 11:
        print ("Your second card: another King ")
      else:
        print ("Your second card: King ")
  elif triggerC == 12:
    card2 = 1
    ace = True
    if card1 == 10:
      print ("Your second card: an Ace! ")
    elif card1 == 1:
        print ("Your second card: another Ace ")
    else:
      print ("Your second card: Ace ")
  return card1, card2, ace

#Processing initial player total, resolving 21 & blackjack scores:

def hand(card1, card2, ace):
  total = card1 + card2
  totalAce = 0
  if ace:
    if total == 11:
      blackjack = True
      total += 10
      print ("\n\tBLACKJAAAAAAAAAACK!!!!!\n")
    else:
      totalAce = total + 10
      blackjack = False
      print ("\nYou have", total, "or", (totalAce))
  else:
    blackjack = False
    print ("\nYou have", total)
  return total, totalAce, ace, blackjack

#Revealing Dealer's up card:

def dealer1(triggerB, blackjack):

  aceDealer = False

  if triggerB == 6:
    card1Dealer = 8
    if not blackjack:
      print ("Dealer shows an 8 ")
    else:
      print ("Dealer shows an 8\nNot gonna touch your blackjack! ")
  elif triggerB <= 7:
    card1Dealer = triggerB + 2
    if not blackjack:
      print ("Dealer shows a", card1Dealer)
    else:
      print ("Dealer shows a", card1Dealer, "\nNot gonna touch your blackjack! ")
  elif triggerB <= 11:
    card1Dealer = 10
    if triggerB == 8:
      print ("Dealer shows a 10 ")
    if triggerB == 9:
      print ("Dealer shows a Jack ")
    elif triggerB == 10:
      print ("Dealer shows a Queen ")
    elif triggerB == 11:
      print ("Dealer shows a King ")
  elif triggerB == 12:
    card1Dealer = 1
    aceDealer = True
    print ("Dealer shows an ace ")
  return card1Dealer, aceDealer

#Revealing Dealer's second card, processing initial Dealer total:

def dealer2(triggerB, triggerD, card1Dealer, aceDealer, blackjack, bust):

  card2Dealer = 0
  totalDealer = 0
  totalDealAce = 0
  blackjackDealer = False

  if (bust == False) and ((blackjack == False) or (triggerB >= 8)):
  #dealer's second card is a 2-6:
    if triggerD <= 4:
      card2Dealer = triggerD + 2
      totalDealer = card1Dealer + card2Dealer
      if blackjack:
        print ("\nDealer shows a", card2Dealer, "and cowers before your Blackjack ")
      elif aceDealer:
        totalDealAce = totalDealer + 10
        print ("\nDealer shows a", card2Dealer, "\nDealer has", totalDealer, "or", totalDealAce)
      else:
        print ("\nDealer shows a", card2Dealer, "\nDealer has", totalDealer)
  #dealer's second card is an 8:
    elif triggerD == 6:
      card2Dealer = 8
      totalDealer = card1Dealer + 8
      if blackjack:
        print ("\nDealer shows an 8 and cowers before your Blackjack ")
      elif aceDealer:
        totalDealer += 10
        totalDealAce = 0
        print ("\nDealer shows an 8\nDealer stands on 19 ")
      else:
        print ("\nDealer shows an 8\nDealer has", totalDealer)
  #dealer's second card is a 7 or 9:
    elif triggerD <= 7:
      card2Dealer = triggerD + 2
      totalDealer = card1Dealer + card2Dealer
      if blackjack:
        print ("\nDealer shows a", card2Dealer, "and cowers before your Blackjack ")
      elif aceDealer:
        totalDealer += 10
        totalDealAce = 0
        print ("\nDealer shows a", card2Dealer, "\nDealer stands on", totalDealer)
      else:
        print ("\nDealer shows a", card2Dealer, "\nDealer has", totalDealer)
  #dealer's second card is a 10 or face card:
    elif triggerD <= 11:
      card2Dealer = 10
      totalDealer = card1Dealer + card2Dealer
      if aceDealer:
        totalDealer +=10
        totalDealAce = 0
        blackjackDealer = True
    #...is a 10:
      if triggerD == 8:
        if aceDealer:
          print ("\nDealer shows a 10 ...and has blackjack. Sorry about that :/ ")
        else:
          if blackjack:
            if triggerB == 8:
              print ("\nDealer shows another 10 and cowers before your Blackjack ")
            else:
              print ("\nDealer shows a 10 and cowers before your Blackjack ")
          else:
            print ("\nDealer shows a 10\nDealer has", totalDealer)
    #...is a Jack:
      elif triggerD == 9:
        if aceDealer:
          print ("\nDealer has ...a Jack. A BLACKjack. Sorry about that :/ ")
        else:
          if blackjack:
            if triggerB == 9:
              print ("\nDealer shows another Jack and cowers before your Blackjack ")
            else:
              print ("\nDealer shows a Jack and cowers before your Blackjack ")
          else:
            print ("\nDealer shows a Jack\nDealer has", totalDealer)
    #...is a Queen:
      elif triggerD == 10:
        if aceDealer:
          print ("\nDealer shows a Queen ...and has blackjack. Sorry about that :/ ")
        else:
          if blackjack:
            if triggerB == 10:
              print ("\nDealer shows another Queen and cowers before your Blackjack ")
            else:
              print ("\nDealer shows a Queen and cowers before your Blackjack ")
          else:
            print ("\nDealer shows a Queen\nDealer has", totalDealer)
    #...is a King:
      elif triggerD == 11:
        if aceDealer:
          print ("\nDealer shows a King ...and has blackjack. Sorry about that :/ ")
        else:
          if blackjack:
            if triggerB == 11:
              print ("\nDealer shows another King and cowers before your Blackjack ")
            else:
              print ("\nDealer shows a King and cowers before your Blackjack ")
          else:
            print ("\nDealer shows a King\nDealer has", totalDealer)
  #dealer's second card is an ace:
    elif triggerD == 12:
      card2Dealer = 1
      aceDealer = True
      totalDealer = card1Dealer + card2Dealer
      if blackjack:
        if triggerB == 12:
          print ("\nDealer shows another Ace and cowers before your Blackjack ")
        elif card1Dealer == 10:
          totalDealer = 21
          totalDealAce = 0
          blackjackDealer = True
          print ("Dealer shows an Ace ...and has blackjack TOO! Sorry about that :/ ")
      else:
        print ("\nDealer shows an ace ")
        if card1Dealer <= 6:
          totalDealAce = totalDealer + 10
          print ("Dealer has", totalDealer, "or", totalDealAce)
        elif card1Dealer <= 9:
          totalDealer += 10
          totalDealAce = 0
          print ("Dealer has", totalDealer)
        elif card1Dealer == 10:
          totalDealer = 21
          totalDealAce = 0
          blackjackDealer = True
          print ("Dealer has blackjack! Sorry about that :/ ")
  return totalDealer, totalDealAce, aceDealer, blackjackDealer