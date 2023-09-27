#include<iostream>
using namespace std;
int n, m;
int X[40006]; //magical value
int indicator[15006]; //indicate values in the array
int A[15006], B[15006], C[15006], D[15006]; //result

//let d-c = t
//then b-a = 2t, c-b > 6t
//
//must satisfy d-a > 9t
//
//therefore the ranges are as below
//a:        1 <= a <= n - 9t -1
//d:   9t + 2 <= d <= n
//t:        1 <= t <= (n-1)/9 (will use "9t+1 <= n" to remove division)

int main()
{
    //input values
    cin >> n >> m;
    for (int i = 1; i <= m; i++)
    {
        cin >> X[i];
        indicator[X[i]]++;
    }
    //calculation
    for (int t = 1; t * 9 + 1 <= n; t++)
    {
        int sum = 0;
        for (int d = t * 9 + 2; d <= n; d++) //iterate through possible range of d (9t + 2 <= d <= n)
        {
            int a = d - 9 * t - 1;
            int b = d - 7 * t - 1;
            int c = d - t;

            sum += indicator[b] * indicator[a]; //check for values exactly 2 * t apart (b-a = 2t)
            C[c] += indicator[d] * sum;
            D[d] += indicator[c] * sum;
        }

        sum = 0;
        for (int a = n - t * 9 - 1; a >= 1; a--) //iterate through possible range of a (1 <= a <= n - 9t -1)
        {
            int b = a + 2 * t;
            int c = a + t * 8 + 1;
            int d = a + t * 9 + 1;

            sum += indicator[d] * indicator[c]; //check for values exactly t apart (d-c = t)
            A[a] += indicator[a + 2 * t] * sum;
            B[b] += indicator[a] * sum;
        }
    }
    //print result
    for (int i = 1; i <= m; i++)
    {
        cout << A[X[i]] << ' ' << B[X[i]] << ' ' << C[X[i]] << ' ' << D[X[i]] << endl;
    }
    return 0;
}
/* REFERENCE
https://codeleading.com/article/88753821404/
*/