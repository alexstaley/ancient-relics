#Assignment 5 -- Stepback Blackjack -- Alex Staley

from blackjack.counter import *
from blackjack.deal import *
from blackjack.turns import *
from blackjack.record import *

games = 0
wins = 0
losses = 0
ties = 0

while True:
  games = count(games)

  triggerA = random.randint(0,12)
  triggerB = random.randint(0,12)
  triggerC = random.randint(0,12)
  triggerD = random.randint(0,12)

  ace = False
  aceDealer = False
  blackjack = False
  blackjackDealer = False
  bust = False

#Dealing Player's cards:
  card1, card2, ace = dealPlayer (triggerA, triggerC)
#Processing Player's hand:
  total, totalAce, ace, blackjack = hand(card1, card2, ace)
#Revealing Dealer's up card:
  card1Dealer, aceDealer = dealer1(triggerB, blackjack)
#Player's turn:
  total, ace, bust = turnPlayer(total, totalAce, ace, blackjack, bust)
#Revealing Dealer's second card:
  totalDealer, totalDealAce, aceDealer, blackjackDealer = dealer2(triggerB, triggerD, card1Dealer, aceDealer, blackjack, bust)
#Dealer's turn:
  totalDealer = turnDealer(totalDealer, totalDealAce, aceDealer, blackjack, blackjackDealer, bust)
#Processing final score:
  win, tie = finalScore(total, totalDealer, blackjack, blackjackDealer, bust)
#Processing Player's record:
  wins, losses, ties = record(win, tie, wins, losses, ties)
#Determining if rematch, displaying Player's record:
  if not rematch(games):
    exit(wins, losses, ties)
    break