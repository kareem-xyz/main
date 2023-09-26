
greeting = (input("Greet me \n").lower()).split()
if "hello" in greeting[0]:
    money = "$0"
elif "h" == greeting[0][0]:
    money = "$20"
else :
    money = "$100$"
print(money)