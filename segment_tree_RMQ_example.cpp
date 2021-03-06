// Codechef problem link
// https://www.codechef.com/COOK116B/problems/MAXBTY



#include<bits/stdc++.h>
using namespace std;

#define int long long int
const int mxN = 1e5;
int n, q;
int a[mxN];

struct segtree {
    int *tree = new int[1<<18];
    int *lazy = new int[1<<18];

    void build(int *a, int i=1, int s = 0, int e = n-1) {
        if(s > e)
            return;
        if(s == e) {
            tree[i] = a[s];       
            return;
        }
        int mid = (s + e)/2;
        build(a, 2*i, s, mid);
        build(a, 2*i+1, mid+1, e);
        tree[i] = max(tree[2*i], tree[2*i+1]);
    }

    void update( int l, int r, int inc, int i = 1, int s = 0, int e = n-1) {
        if(lazy[i] != 0) {
            tree[i] += lazy[i];
            if(s != e) {     // not a leaf node - propagate the update in lazy tree 
                lazy[2*i] += lazy[i];
                lazy[2*i + 1] += lazy[i];
            }
            lazy[i] = 0;
        }
        if(l > e || r < s)
            return;

        if(l <= s && e <= r) {
            tree[i] += inc;
            if(s != e) {
                lazy[2*i] += inc;
                lazy[2*i + 1] += inc;
            }
            return;
        }

        int mid = (s + e)/ 2;
        update(l, r, inc, 2*i, s, mid);
        update(l, r, inc, 2*i + 1, mid + 1, e);
        tree[i] = max(tree[2*i], tree[2*i + 1]);

    }

    int query(int l, int r, int i=1, int s =0 , int e= n-1) {
        if(lazy[i] != 0) {
            tree[i] += lazy[i];
            if(s != e) {
                lazy[2*i] += lazy[i];
                lazy[2*i + 1] += lazy[i];
            }    
            lazy[i] = 0;
        }
        if(l > e || r < s)
            return -1e18;

        if(l <= s && e <= r)
            return tree[i];

        int mid = (s + e)/2;
        int leftans = query( l, r, 2*i, s, mid);
        int rightans = query( l, r, 2*i + 1, mid + 1, e);

        return max(leftans, rightans);
    }
    void disp(int n)
    {
        for(int i = 0; i < 4*n+1; i++)
            cout << tree[i] << " ";
        cout << endl;
        for(int i = 0; i < 4*n+1; i++)
            cout << lazy[i] << " ";
        cout << endl;
    }
};

void solve() {
     cin >> n >> q;
    for(int i = 0; i < n; i++)
        cin >> a[i];

    int l, r, choice, inc;
    segtree sr, sl;
    
    for(int i = 0; i < n; i++)
        sr.update(i, n-1, a[i]);
    for(int i = 0; i < n; i++)
        sl.update(i, n-1, -a[i]);

    for(int x, y; q--; ) {
		char qt;
		cin >> qt >> x >> y;
		if(qt=='Q') {
            int ans1 = sr.query(y-1, n-1);
            int ans2 = 0;
            if(x-2 >= 0)
                ans2 = sl.query(0, x-2);
            if(ans2 < 0)
                ans2 = 0;

            cout << ans1 + ans2 << endl;
		} else {
			sr.update(x-1, n-1, y-a[x-1]); 
			sl.update(x-1, n-1, a[x-1]-y);
			a[x-1]=y;
		}
	}
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    while(t--) {
        solve();
    }
}