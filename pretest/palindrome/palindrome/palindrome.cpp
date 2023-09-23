#include <iostream>
using namespace std;

class Date {
public:
	//constructor
	Date(unsigned int Date);
	//destructor, not used
	~Date();

    //sets the date, calculates and sets m_Year, m_Month, and m_Day too
	void Set(unsigned int Date);

	//check if a year is leap year
	bool IsLeapYear() const;
	static bool IsLeapYear(unsigned int Year);

    //check if a date is palindrome, returns 1 if true, 0 if false
    bool IsPalindrome() const;
    static bool IsPalindrome(const Date& Date);

	//overload operators
	bool operator==(const Date& other) const;
    bool operator!=(const Date& other) const;
	Date& operator++();
	Date  operator++(int);

	//const references for data members, read only
    const unsigned int& DateRef;
	const unsigned int& Year;
	const unsigned int& Month;
	const unsigned int& Day;

	//number of days in each month
	static const unsigned int DaysInMonth[2][13];

private:
    unsigned int m_Date;
	unsigned int m_Year;
	unsigned int m_Month;
	unsigned int m_Day;
};

int main()
{
    unsigned int palindromeCount = 0;
    unsigned int date1;
    unsigned int date2;
    cin >> date1;
    cin >> date2;

    Date startDate(date1);
    Date endDate(date2);

    while (startDate != endDate)
    {
        if (startDate.IsPalindrome())
        {
            palindromeCount++;
        }
        startDate++;
    }

    cout << palindromeCount;
}
//constructor
Date::Date(unsigned int Date) : DateRef(m_Date), Year(m_Year), Month(m_Month), Day(m_Day)
{
    Set(Date);
}
//destructor, not used
Date::~Date()
{
}
//number of days in each month (leap year taken into account)
const unsigned int Date::DaysInMonth[2][13] = 
{
                0u, 31u, 28u, 31u, 30u, 31u, 30u, 31u, 31u, 30u, 31u, 30u, 31u,
                0u, 31u, 29u, 31u, 30u, 31u, 30u, 31u, 31u, 30u, 31u, 30u, 31u,
};
//sets the date, calculates and sets m_Year, m_Month, and m_Day too
void Date::Set(unsigned int Date) 
{
    m_Date = Date;
    m_Year = static_cast<unsigned int>(Date / 10000);
    m_Month = static_cast<unsigned int>((Date % 10000) / 100);
    m_Day = Date % 100;
}
//check if a year is leap year
bool Date::IsLeapYear() const 
{
    return IsLeapYear(m_Year);
}
bool Date::IsLeapYear(unsigned int Year) 
{
     return (Year % 4 == 0 && Year % 100 != 0) || (Year % 400 == 0);
}
//check if a date is palindrome, returns 1 if true, 0 if false
bool Date::IsPalindrome() const
{
    return IsPalindrome(*this);
}
bool Date::IsPalindrome(const Date& Date)
{
    unsigned int frontHalf = Date.Year;
    unsigned int backHalf = Date.DateRef % 10000;
    unsigned int frontHalfReversed = frontHalf % 10 * 1000
        + static_cast<unsigned int>((frontHalf % 100) / 10) * 100
        + static_cast<unsigned int>((frontHalf % 1000) / 100) * 10
        + static_cast<unsigned int>(frontHalf / 1000);
    return frontHalfReversed == backHalf;
}
//overload operators
bool Date::operator==(const Date& other) const 
{
    return (m_Date == other.DateRef);
}
bool Date::operator!=(const Date& other) const
{
    return (m_Date != other.DateRef);
}
Date& Date::operator++() 
{
    unsigned int NewDate;
    unsigned int NewDay = m_Day + 1;
    unsigned int NewMonth = m_Month;
    unsigned int NewYear = m_Year;
    if (NewDay > DaysInMonth[IsLeapYear()][NewMonth]) 
    {
        NewDay = 1;
        NewMonth++;
    }
    if (NewMonth > 12) 
    {
        NewMonth = 1;
        NewYear++;
    }
    NewDate = NewYear * 10000 + NewMonth * 100 + NewDay;
    Set(NewDate);
    return *this;
}
Date Date::operator++(int) 
{
    Date Res(*this);
    ++(*this);
    return Res;
}
