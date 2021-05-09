######## ~^~ A ~^~ TREE ~^~ ########

from allieowl.base import *

def leaf(size, shadeBranch = '#584225', shadeLeaf = '#2A7426'):
    pensize(1)
    color(shadeBranch)
    speed(25)
    #stem:
    (x1, y1) = position()
    forward(size / 2)
    #leaf:
    color(shadeLeaf)
    left(45)
    begin_fill()
    circle((-1 * size), 90)
    right(90)
    circle((-1 * size), 90)
    end_fill()
    #veins:
    color(shadeBranch)
    right(135)
    counter = 0
    forward(size / 5)
    for vein in range(5):
        counter += 1
        (x2, y2) = position()
        face = heading()
        if counter % 2 != 0:
            right(45)
        else:
            left(45)
        forward(size / 5)
        move(x2, y2)
        seth(face)
        forward(size / 5)
    move(x1, y1)

def branch(size, limbs, thickness, shadeBranch = '#584225', shadeLeaf = '#2A7426'):
    color(shadeBranch)
    speed(5)
    #main branch:
    counter = 0
    for branch in range((size + 1), 50, int(-1 * limbs)):
        pensize((branch * thickness) / 36)
        left(15)
        forward(limbs)
        right(30)
        forward(limbs)
        left(17)
        #side branch:
        (x1, y1) = position()
        face = heading()
        counter += 1
        if counter % 2 != 0:
            right(50)
        else:
            left(50)
        pensize((branch * thickness) / 60)
        forward(limbs)
        right(50)
        leaf(limbs)
        left(100)
        leaf(limbs)
        speed(5)
        right(50)
        move(x1 , y1)
        seth(face)

def trunk(size, shade = '#584225'):
    color(shade)
    branch(size, (size * 7/40), 6)

def tree(x, y, size, shadeBranch = '#584225', shadeLeaf = '#2A7426'):
    color(shadeBranch)
    move((x + (size / 10)), (y - (size / 3)))
    seth(85)
    trunk(size)
    move((x + 15), (y - 15))
    seth(173)
    branch(size, (size / 10), 3)

