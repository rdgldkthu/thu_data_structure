#include <iostream>
#include <unordered_map>
#include <queue>
using namespace std;

struct passenger 
{
    int nat; //nationality
    int t; //time of arrival
};

int main() 
{
    int n; //number of ships
    int t; //time of arrival of a ship
    int k; //number of passengers on a ship
    int res = 0; //result
    unordered_map<int, int> counter; //to store key-value pairs (nationality-number of passengers)
    queue<passenger> q; //queue to store passenger info (first in first out)

    cin >> n; //input number of ships

    for (int i = 1; i <= n; i++) 
    {
        cin >> t >> k; //input time of arrival and the number of passengers onboard
        
        int x; //passenger nationality
        passenger p;
        for (int j = 1; j <= k; j++) 
        {
            cin >> x; //input passengers' nationalities
            p.nat = x;
            p.t = t;
            q.push(p); //add passenger info to queue
            if (counter[x] == 0) //add new nationality to the counter
            {
                res++;
            }
            counter[x]++; //add 1 if nationality already exists
        }
        //get rid of expired passenger info
        int expirationTime = t - 86400;
        while (!q.empty()) 
        {
            p = q.front();
            if (p.t <= expirationTime) 
            {
                counter[p.nat]--; //minus 1 from the counter
                if (counter[p.nat] == 0)
                {
                    res--; //if that was the last, minus 1 from the result
                }
                q.pop(); //pop expired passenger info
            }
            else break;
        }
        //print result
        cout << res << endl;
    }
    return 0;
}
/* REFERENCE
https://www.cnblogs.com/littlehb/p/15075180.html
*/