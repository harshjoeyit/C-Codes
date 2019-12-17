// basic approach - O(n^3)


// hashing O(n^2) - O(n) - space 


// 2 pointer approach O(n^2) 
// space O(1)

#include<bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cin >> n;

    vector<int> v(n);
    for(int i = 0; i < n; i++)
        cin >> v[i];

    sort(v.begin(), v.end());

    int i = 0, l, r;
    bool flag = true;

    while((v[i] <= 0) && flag)
    {
        //cout << "a[i]: " << v[i] << endl;
        l = i+1;
        r = n-1;

        while(l < r)
        {
            //cout << "l: " << v[l] << ", r: " << v[r] << endl;
            int sum = v[i] + v[l] + v[r];
            
            if(sum == 0)
            {
                flag = false;
                break;
            }
            else 
            if(sum > 0)
                --r;
            else
            if(sum < 0)
                ++l;
        }
        ++i;
    }

    if(!flag)
        cout << v[i-1] << " " << v[l] << " " << v[r] << endl;
    else
        cout << "not possible" << endl;
}