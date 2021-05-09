#  TWINKLE, TWINKLE, TURTLE STAR*  #
## Kallo / Staley / Taylor / Tong ##

from allieowl.sky import *
from allieowl.tree import *
from allieowl.owl import *

#########  THE BACKGROUND  #########
night_sky = '#012380'
getscreen().bgcolor(night_sky)
stars(sizeMax = 25, number = 50, body = 150, moon = 50, xShadow = -291, yShadow = 191, lyricsX = -195, lyricsYtop = 125, lyricsYbot = -146)
corners(size = 20)
moonCenter = moon(x = -275, y = 180, size = 50, craters = 15)
tree(x = 225, y = -210, size = 275)

#########  THE FOREGROUND  #########
legs(size = 80, body = 150, width = 30, origin = (0, 0), tweakL = 10, tweakR = 0)
body(size = 150, shade = '#B89B76', origin = (0, 0))
ears(size = 60, shade = '#B89B76', body = 150, origin = (0, 0))
eyes(x = 0, y = 120, size = 40, shade = '#E6A550', goofR = 4, goofL = 2)
beak(xEyes = 0, yEyes = 120, size = 50)
wingLean = 10 * wings(shade = '#7C684E', body = 150, lean = 2, origin = (0, 0))
feathers(size = 25, shade = '#894D1F', number = 3, body = 150, face = 25, wings = wingLean, shift = 0)
shape("turtle")
song(x = -374, y = 90)
crawl(x = -275, y = 180)
