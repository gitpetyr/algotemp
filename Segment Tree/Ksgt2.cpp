#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

vector<int> _unique(vector<int>& raw_data)
{
    vector<int> nums = raw_data;
    sort(nums.begin(), nums.end());
    nums.erase(unique(nums.begin(), nums.end()), nums.end());
    return nums;
}

int get_id(const vector<int>& nums, int val)
{

    return lower_bound(nums.begin(), nums.end(), val) - nums.begin() + 1;
}

class sgt {
private:
    struct Node {
        int l, r;
        int sum;
    };

    vector<Node> tr;
    vector<int> roots;
    int range_n;

    int newnode(int cp)
    {
        tr.push_back(tr[cp]);
        return tr.size() - 1;
    }

    int newnode()
    {
        tr.push_back({ 0, 0, 0 });
        return tr.size() - 1;
    }

    int insert(int prev, int l, int r, int val)
    {
        int id = newnode(prev);
        tr[id].sum++;

        if (l == r)
            return id;

        int mid = l + (r - l) / 2;
        if (val <= mid)
            tr[id].l = insert(tr[prev].l, l, mid, val);
        else
            tr[id].r = insert(tr[prev].r, mid + 1, r, val);

        return id;
    }

    int query(int u, int v, int l, int r, int k)
    {
        if (l == r)
            return l;

        int lcnt = tr[tr[v].l].sum - tr[tr[u].l].sum;

        int mid = l + (r - l) / 2;
        if (k <= lcnt) {

            return query(tr[u].l, tr[v].l, l, mid, k);
        } else {

            return query(tr[u].r, tr[v].r, mid + 1, r, k - lcnt);
        }
    }

public:
    sgt(int n, int m)
    {
        range_n = n;

        tr.reserve(m * 25);
        tr.push_back({ 0, 0, 0 });
        roots.reserve(m);
        roots.push_back(0);
    }

    void update(int val)
    {
        int last_root = roots.back();
        int new_root = insert(last_root, 1, range_n, val);
        roots.push_back(new_root);
    }

    int query_k(int L, int R, int k)
    {
        return query(roots[L - 1], roots[R], 1, range_n, k);
    }
};

int main()
{

    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, m;
    cin >> n >> m;

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    vector<int> nums = _unique(a);
    int mxr = nums.size();

    sgt ct(mxr, n);

    for (int x : a) {

        int rank = get_id(nums, x);
        ct.update(rank);
    }

    while (m--) {
        int l, r, k;
        cin >> l >> r >> k;

        int ans = ct.query_k(l, r, k);

        cout << nums[ans - 1] << endl;
    }

    return 0;
}
