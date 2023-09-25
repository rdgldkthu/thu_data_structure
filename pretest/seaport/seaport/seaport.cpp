#include <iostream>
#include <vector>
#include <set>
using namespace std;

int main()
{
    int n; //number of ships
    int t; //time of arrival
    int k; //number of passengers
    vector<int> timeStamps; //
    vector<int> ships; //each passenger's nationality    

    //input number of ships
    cin >> n;

    //input and store ships data
    for (int i = 0; i < n; i++)
    {
        cin >> t >> k;

        timeStamps.push_back(t * -1);
        ships.push_back(t * -1);

        int temp;
        //input each passenger's nationality
        for (int j = 0; j < k; j++)
        {
            cin >> temp;
            ships.push_back(temp);
        }
    }

    bool toggleInsert = false; //if true, insert data to uniqueNationalities
    for (auto& arrivalTime : timeStamps)
    {
        set<int> uniqueNationalities; //unique nationalities
        int endTime = arrivalTime; //actual end time * -1
        int startTime = endTime + 86400; //actual start time * -1

        for (auto& data : ships)
        {
            if (data < 0)
            {
                if ((data < startTime) && (data >= endTime))
                {
                    toggleInsert = true;
                }
                else
                {
                    toggleInsert = false;
                }
            }
            if (toggleInsert && data > 0)
            {
                uniqueNationalities.insert(data);
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