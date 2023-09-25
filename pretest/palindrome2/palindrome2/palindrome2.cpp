#include <iostream>
using namespace std;

//number of days in each month (leap year taken into account)
const unsigned int daysInMonth[2][13] =
{
                0u, 31u, 28u, 31u, 30u, 31u, 30u, 31u, 31u, 30u, 31u, 30u, 31u,
                0u, 31u, 29u, 31u, 30u, 31u, 30u, 31u, 31u, 30u, 31u, 30u, 31u,
};

//check if an year is a leap year
bool isLeapYear(unsigned int year)
{
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

//check if a date is valid
bool isValidDate(unsigned int date)
{
    unsigned int year = date / 10000;
    unsigned int month = (date % 10000) / 100;
    unsigned int day = date % 100;

    //check month
    if (month > 12 || month <= 0)
    {
        return false;
    }

    //check day
    if (day > daysInMonth[isLeapYear(year)][month] || day <= 0)
    {
        return false;
    }

    return true;
}

//generate a palindrome date with given year
unsigned int generatePalindrome(unsigned int year)
{
    unsigned int result = year * 10000
        + (year % 10) * 1000
        + ((year % 100) / 10) * 100
        + ((year % 1000) / 100) * 10
        + (year / 1000);
    return result;
}

int main()
{
    unsigned int date1; //start date
    unsigned int date2; //end date
    unsigned int res = 0; //result
    
    //input dates
    cin >> date1;
    cin >> date2;

    //set start, end years to generate test cases
    unsigned int startYear = date1 / 10000;
    unsigned int endYear = date2 / 10000 + 1;

    //iterate through test cases
    unsigned int testCase;
    for (unsigned int year = startYear; year < endYear + 1; year++)
    {
        testCase = generatePalindrome(year);
        if (isValidDate(testCase) && testCase >= date1 && testCase <= date2)
        {
            res++;
        }
    }

    //print out the result
    cout << res;
}