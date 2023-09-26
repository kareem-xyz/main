
while True:
    try:
        height = int(input("Height of Pyramid:"))
        if height > 0 and height <= 8:
            break
    except ValueError:
        ...

for i in range(height):
    row = i + 1

    # Print spaces before #

    print(" " * (height - row), end="")

    # Print rows of #, plus double space in middle
    print("#" * row + "  " + "#" * row)

