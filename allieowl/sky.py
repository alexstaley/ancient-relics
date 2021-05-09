######### ** THE ** SKY ** #########

from allieowl.base import *

def stars(sizeMax, number, body, moon, xShadow, yShadow, lyricsX, lyricsYtop, lyricsYbot, shade = "white", field = 700):
    color(shade)
    speed(25)
    for sky in range(number):
        while True:
            x = randint(0, int(field * 15/14) - (field / 2))
            y = randint(0, int(field * 8/9) - (field / 2))
            #if stars aren't in the way:
            if (((x - xShadow) ** 2 + (y - yShadow) ** 2) > (moon + sizeMax) ** 2) and ((x ** 2 + y ** 2) > (body - sizeMax) ** 2) and ((x > lyricsX) or (y > lyricsYtop) or (y < lyricsYbot)):
                break
        move(x, y)
        size = randint(1, (sizeMax + 1))
        left(size)
        begin_fill()
        star(size)
        end_fill()
    seth(0)

def corners(size, shade = "white"):
    color(shade)
    speed(0)
    #bottom left:
    move(-300, -200)
    left(size * 10)
    pendown()
    begin_fill()
    star(size)
    end_fill()
    move(-345, -240)
    left(size * 10)
    pendown()
    begin_fill()
    star(size - 8)
    end_fill()
    #top left:
    move(-340, 250)
    left(size * 10)
    pendown()
    begin_fill()
    star(size)
    end_fill()
    move(-400, 137)
    left(size * 7)
    pendown()
    begin_fill()
    star(size * 3/4)
    end_fill()
    seth(0)

def moon(x, y, size, craters, shadeMoon = '#FDF563', shadeCraters = '#A8A234', shadeStars = "white", shadeSky = '#012380'):
    color(shadeMoon)
    speed(2)
    #moon:
    move(x, y)
    moonCenter = position()
    penup()
    seth(90)
    forward(size)
    left(90)
    pendown()
    begin_fill()
    circle(size)
    end_fill()
    #craters:
    speed(1)
    for crater in range (craters):
        while True:
            #pick random locations for craters, weighted toward the bottom right part of the moon:
            xC = randint((-size), (size + 1))
            yC = randint((-size), (size + 1))
            craterSize = randint(1, int(size / 6))
            if (xC ** 2 + yC ** 2 <= (size * 5/6) ** 2) and (xC > -(size / 2)) and (yC < (size / 2)):
                break
        move((x + xC), (y + yC))
        dot(craterSize, shadeCraters)
    #crescent:
    color(shadeSky)
    move(x, y)
    penup()
    right(35)
    forward(size * 2 / 5)
    right(90)
    forward(size * 7 / 8)
    left(90)
    pendown()
    begin_fill()
    circle(size * 7 / 8)
    end_fill()
    #star eyes:
    color(shadeStars)
    speed(5)
    move(x, y)
    right(30)
    penup()
    forward((size * 7 / 8) - 4)
    pendown()
    begin_fill()
    star(8)
    end_fill()
    move(x, y)
    left(60)
    penup()
    forward((size * 7 / 8) - 4)
    pendown()
    begin_fill()
    star(8)
    end_fill()
    move(x, y)
    seth(325)
    return moonCenter

