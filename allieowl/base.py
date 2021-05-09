from turtle import *
from random import *

def move(x, y):
    penup()
    goto(x, y)
    pendown()

def star(size):
    for arm in range(5):
        forward(size)
        left(216)

def triangle(size):
    for leg in range(3):
        forward(size)
        left(120)

def song(x, y, font=("Verdana", 12, "italic")):
    #REQUIRES BOSTON ACCENT
    pensize(2)
    color("white")
    speed(10)
    seth(160)
    penup()
    forward(150)
    shape("turtle")
    speed(1)
    move (x, y)
    write("Twinkle, twinkle, ", font = font)
    move (x+20,y-20)
    write("Little star~ ", font = font)
    move (x,y-40)
    write ("How I wonder ",font = font)
    move (x+20,y-60)
    write ("What you are? ", font = font)
    move (x,y-80)
    write ("Up above ", font = font)
    move (x+20,y-100)
    write ("Eyebrowls so high~ ", font = font)
    move (x,y-120)
    write ("Like a triangle ", font = font)
    move (x+20,y-140)
    write ("On your face... ", font = font)
    move (x,y-160)
    write ("Twinkle, twinkle, ", font = font)
    move (x+20,y-180)
    write("Turtle star~ ", font = font)
    move (x,y-200)
    write ("How I wonder ",font = font)
    move (x+20,y-220)
    write ("What you draw~ ", font = font)

def crawl(x, y):
    color("white")
    speed(2)
    penup()
    goto(x, y)
    seth(145)
    forward(5)
    left(70)
    right(140)
    forward(2)
    left(70)
    forward(15)
    seth(90)
    seth(180)
    seth(325)
    forward(4)

