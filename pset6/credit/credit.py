from cs50 import get_int


def main():
    number = get_int("Number: ")
    validation = 0
    i = 1
    while number % pow(10, i - 1) != number:
        if i % 2 == 0:
            if (get_digit(number, i) * 2) < 10:
                validation += get_digit(number, i) * 2
            else:
                validation += get_digit(get_digit(number, i) * 2, 1) + get_digit(get_digit(number, i) * 2, 2)
        else:
            validation += get_digit(number, i)
            
        i += 1
    
    i -= 1
    
    if (validation % 10 != 0):
        print("INVALID")
    elif i == 15 and (((10 * get_digit(number, i)) + get_digit(number, i - 1)) == 34 or ((10 * get_digit(number, i)) + get_digit(number, i - 1)) == 37):
        print("AMEX")
    elif i == 16 and (((10 * get_digit(number, i)) + get_digit(number, i - 1)) > 50 and ((10 * get_digit(number, i)) + get_digit(number, i - 1)) < 56):
        print("MASTERCARD")
    elif (i == 13 or i == 16) and get_digit(number, i) == 4:
        print("VISA")
    else:
        print("INVALID")


def get_digit(number, position):
    return((number % pow(10, position) - number % pow(10, position - 1)) / pow(10, position - 1))

    
main()
