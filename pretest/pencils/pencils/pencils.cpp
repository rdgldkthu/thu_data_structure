#include <iostream>
using namespace std;

int findMinimumPrice(int n, int pencilsPerPackage, int price)
{
    int totalPencils = 0;
    int i = 0;
    while (totalPencils < n)
    {
        totalPencils = pencilsPerPackage * ++i;
    }
    return price * i;
}

int main()
{
    int n; //number of pencils needed
    int pencilsPerPackage;
    int price;
    int minimumPrice = 10000000; //result

    //input number of pencils needed
    cin >> n;

    //iterate through each product, calculate minimum price
    int tempPrice;
    for (int i = 0; i < 3; i++)
    {
        cin >> pencilsPerPackage >> price;
        tempPrice = findMinimumPrice(n, pencilsPerPackage, price);
        if (tempPrice < minimumPrice)
        {
            minimumPrice = tempPrice;
        }
    }

    //print minimum price
    cout << minimumPrice;
}