#include <iostream>
#include <vector>
using namespace std;

bool notInVector(vector<int> v, int num)
{
    for (auto& itr : v)
    {
        if (itr == num)
        {
            return false;
        }
    }
    return true;
}

int main()
{
    int n; //number of ships
    int t; //time of arrival
    int k; //number of passengers
    vector<vector<int>> x; //each passenger's nationality
    vector<int> nationalities; //all the nationalities arrived within 24 hours

    //input n
    cin >> n;
    x.reserve(n);

    for (int i = 0; i < n; i++)
    {
        //input time, number of passengers
        cin >> t >> k;
        x.push_back(vector<int>());
        x[i].reserve(k + 1);
        x[i].push_back(t);

        //input each passenger's nationality
        for (int j = 0; j < k; j++)
        {
            int nat; //nationality
            cin >> nat;
            x[i].push_back(nat);
        }

        //add unique nationalities to nats
        for (const auto& ship : x)
        {
            //check to only iterate through ships that came within 24 hours
            if (ship[0] > t - 86400 && ship[0] <= t)
            {
                for (auto passenger = ship.begin() + 1; passenger != ship.end(); passenger++)
                {
                    if (notInVector(nationalities, *passenger))
                    {
                        nationalities.push_back(*passenger);
                    }
                }
            }
        }

        //print, reset nationalities
        cout << nationalities.size() << endl;
        nationalities.clear();
        nationalities.shrink_to_fit();
    }
}
/* REFERENCES
https://doompa.tistory.com/286
https://boycoding.tistory.com/210
*/