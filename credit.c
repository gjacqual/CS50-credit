#include <cs50.h>
#include <stdio.h>

int nblen(long int number);
int check_lunn(long int number);
int find_first_digit(long int number);
int find_two_digits(long int number);

int main(void)
{
    long long number;
    int lenght;
    int check = 0;
    int first_digit;
    int two_digits;

    // Ask nomber of Credit Card
    do
    {
        number = get_long("Number: ");
        lenght = nblen(number);
    }
    while (lenght < 0);
    
    // check valid nomber with Luhn’s Algorithm
    check = check_lunn(number);
    // we find first and two firsts digits of card
    first_digit = find_first_digit(number);
    two_digits = find_two_digits(number);

    // Compare the card's type and output the result
    if (lenght == 16 && check && two_digits >= 51 && two_digits <= 55)
    {
        printf("MASTERCARD\n");
    }
    else if (lenght == 15 && check && (two_digits == 34 || two_digits == 37))
    {
        printf("AMEX\n");
    }
    else if ((lenght == 13 || lenght == 16) && check && first_digit == 4)
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }
    return (0);
}

int nblen(long int number)
{
    int len = 0;
    
    // find the length of the credit card number
    while (number > 0)
    {
        number /= 10;
        len++;
    }
    return (len);
}

int check_lunn(long int number)
{
    int prod2 = 0;
    int take_digit = 0;
    int digit_position = 1;
    int product2 = 0;
    int sum = 0;
    int sum_prod_even = 0;
    int sum_odd_even = 0;

    // We go through the cycle dividing the credit card number by the remainder
    while (number > 0)
    {
        take_digit = number % 10;
        
        // if position is even
        if (digit_position % 2 == 0)
        {
            product2 = take_digit * 2;
            sum_prod_even += (product2 / 10) + (product2 % 10);
        }
        
        // if position is odd
        else
        {
            sum = sum + take_digit;
        }

        number /= 10;
        digit_position++;
    }
    // add the sums of odd digits and multiplied by 2 even ones
    sum_odd_even = sum + sum_prod_even;

    if (sum_odd_even % 10 == 0)
    {
        return (1);
    }
    return (0);
}

int  find_first_digit(long int number)
{
    int take_digit = 0;
    // We go through the cycle until we reach the last (first) number of the card
    while (number > 0)
    {
        take_digit = number % 10;
        number /= 10;
    }
    // Return the first digit of the card
    return take_digit;
}

int  find_two_digits(long int number)
{
    int  take_digit = 0;
    int  two_digits;
    int  sec_digit = 0;
    
    // We go through the cycle until we reach the last (first) and seccond  numbers of the card
    while (number > 0)
    {
        sec_digit = take_digit;
        take_digit = number % 10;
        number /= 10;
    }
    // we translate the first digit into tens and add the second digit
    two_digits = (take_digit * 10) + sec_digit;
    return two_digits;
}