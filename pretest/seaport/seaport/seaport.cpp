#include <iostream>
#include <vector>
#include <set>
using namespace std;

int main()
{
    int n; //number of ships
    int t; //time of arrival
    int k; //number of passengers
    vector<vector<int>> passengersInShips; //each passenger's nationality    

    //input number of ships, reserve vector capacity
    cin >> n;
    passengersInShips.reserve(n);

    for (int i = 0; i < n; i++)
    {
        cin >> t >> k;
        
        passengersInShips.push_back(vector<int>());
        passengersInShips[i].reserve(k + 1);
        passengersInShips[i].push_back(t);

        int temp;
        //input each passenger's nationality
        for (int j = 1; j < k + 1; j++)
        {          
            cin >> temp;
            passengersInShips[i].push_back(temp);
        }

        int startTime = t - 86400; //starting point of time
        set<int> uniqueNationalities; //unique nationalities

        //add unique nationalities to nationalities
        for (auto& ship : passengersInShips)
        {
            //check to only iterate through ships that came within 24 hours
            if (ship[0] > startTime)
            {
                for (auto p = ship.begin() + 1; p != ship.end(); p++)
                {
                    uniqueNationalities.insert(*p);
                }
            }
        }

        //print result
        cout << uniqueNationalities.size() << endl;
    }
}
/* REFERENCES
https://doompa.tistory.com/286
https://boycoding.tistory.com/210
*/