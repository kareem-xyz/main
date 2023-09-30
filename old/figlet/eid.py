#TERMINAL ART
#WEEK 6

import sys
import random
import time
from pyfiglet import Figlet


figlet = Figlet()
fonts = figlet.getFonts()
argc = len(sys.argv)

#if argument count isnt 1 or three
if argc not in [1, 3]:
    print("Usage: python figlet.py emptystring OR -f fontName")
    sys.exit(1)

if argc == 3:
    if sys.argv[1] not in ["-f", "--font"] or sys.argv[2] not in fonts:
        print("Usage: python figlet.py emptystring OR -f fontName")
        sys.exit(2)
    else:
        fontChoice = sys.argv[2]
else :
    fontChoice = fonts[random.randrange(0, len(fonts))]

# text = input("Input text:\n")
figlet.setFont(font=fontChoice)

text = ["EID MUBARAK!", "I WISH YOU", "ALL", "A VERY HAPPY", "AND  PEACEFUL ", "EID"]
for word in text:
    print(figlet.renderText(word))
    time.sleep(2)