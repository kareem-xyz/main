
class Jar:
    def __init__(self, capacity):
        self.capacity = capacity
        self.size = 0


    def __str__(self):
        return '🍪' * self.size

    def deposit(self, n):
        if self.size + n > self.capacity:
            raise ValueError("Cookie Overflow")
        else :
            self.size += n

    def withdraw(self, n):
        if self.size - n < 0:
            raise ValueError("Cookie underflow")
        else :
            self.size -= n

   # @property
    def capacity(self):
        return self.capacity

    #@property
    def size(self):
        return self.size

def get_unsigned_int(prompt):
    while True:
        try:
            number = int(input(prompt))
            if number > 0:
                return number
        except ValueError:
            print("Not a positive integer")

def main():

    sizeofjar = get_unsigned_int("Size of Cookie Jar: ")

    cookiejar = Jar(sizeofjar)

    deposit = get_unsigned_int("Number of cookies to deposit: ")
    cookiejar.deposit(deposit)

    withdraw = get_unsigned_int("Number of cookies to withdraw: ")
    cookiejar.withdraw(withdraw)

    print("Here are your left cookies:")
    print(str(cookiejar))

main()


