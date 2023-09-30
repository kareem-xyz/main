name = input("Whats your name?  ")
last = input("Your Last name? ")
age = input("Your Age? ")

# C style
print("Hello, I am %s %s. I am %i years old" % (name, last, age))

# The Pythonic way (as of python 3.0)
print(f"Hello, I am {name} {last}. I am {age}.")

# Using the .format() method
print("The name is, {}, {} {}".format(last, name, last))
