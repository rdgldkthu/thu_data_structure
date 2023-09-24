#include <iostream>
#include <vector>
using namespace std;

int main() 
{
    int n, m;
    cin >> n >> m;

    vector<int> X(m);
    for (int i = 0; i < m; ++i) 
    {
        cin >> X[i];
    }
    vector<int> A(m, 0), B(m, 0), C(m, 0), D(m, 0);
    int dif;
    for (int a = 0; a < m; a++) 
    {
        for (int b = 0; b < m; b++) 
        {
            for (int c = 0; c < m; c++) 
            {
                for (int d = 0; d < m; d++) 
                {
                    if (((X[a] >= X[b]) || (X[b] >= X[c]) || (X[c] >= X[d])))
                    {
                        continue;
                    }
                    if ((a==b)||(a==c)||(a==d)||(b==c)||(b==d)||(c==d))
                    {
                        continue;
                    }
                    dif = X[d] - X[c];
                    if ((X[b] - X[a] == 2 * dif) && ((X[c] - X[b])) > 6 * dif)
                    {
                        A[a]++;
                        B[b]++;
                        C[c]++;
                        D[d]++;
                    }
                }
            }
        }
    }
    for (int i = 0; i < m; ++i) 
    {
        cout << A[i] << " " << B[i] << " " << C[i] << " " << D[i] << endl;
    }
    return 0;
}
/*
problems - nested loops(exceeds time limit), count multiplies for magical substances with the same value
int main()
{
    unsigned int n, m;

    cin >> n >> m;

	vector<unsigned int> X;
	vector<vector<unsigned int>> useCounts(m, vector<unsigned int>(5, 0));

	X.reserve(m);

	unsigned int temp;
	for (int i = 0; i < m; i++)
	{
		cin >> temp;
		X.push_back(temp);
		useCounts[i][0] = temp;
	}

	sort(X.begin(), X.end());

	unsigned int dif;
	for (int a = 0; a < m-3; a++)
	{
		for (int b = 1; b < m-2; b++)
		{
			for (int c = 2; c < m - 1; c++)
			{
				for (int d = 3; d < m; d++)
				{
					if (((X[a] >= X[b]) || (X[b] >= X[c]) || (X[c] >= X[d])))
					{
						continue;
					}			
					dif = X[d] - X[c];
					if ((X[b] - X[a] == 2 * dif) && ((X[c] - X[b])) > 6 * dif)
					{
						cout << X[a] << " "
							<< X[b] << " "
							<< X[c] << " "
							<< X[d] << endl;
						for (auto& vec : useCounts)
						{
							if (vec[0] == X[a])
							{
								vec[1]++;
							}
							if (vec[0] == X[b])
							{
								vec[2]++;
							}
							if (vec[0] == X[c])
							{
								vec[3]++;
							}
							if (vec[0] == X[d])
							{
								vec[4]++;
							}
						}
					}
				}
			}
		}
	}

	for (auto& vec : useCounts)
	{
		for (int i = 1; i < 5; i++)
		{
			cout << vec[i] << " ";
		}
		cout << endl;
	}
}
*/
