/*
   Rózsafüzér permutáció: a kanonikus alakban a 1-es második helyen áll,
   és az első elem kisebb a harmadiknál. A következő kanonikus rózsafüzért
   a permutáció második elemétől kezdődő lexikografikus következő segítségével
   állítjuk elő.
*/
#include <bits/stdc++.h>
using namespace std;

static void print(const vector<int>& a) {
    for (int i = 0; i < (int)a.size(); ++i) {
        if (i) cout << ' ';
        cout << a[i];
    }
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    vector<int> p(N);
    for (int i = 0; i < N; ++i) cin >> p[i];

    vector<int> q;
    q.reserve(N - 1);
    for (int x : p) if (x != 1) q.push_back(x);

    if (next_permutation(q.begin() + 1, q.end())) {
        vector<int> ans;
        ans.push_back(q[0]);
        ans.push_back(1);
        ans.insert(ans.end(), q.begin() + 1, q.end());
        print(ans);
        return 0;
    }

    vector<int> rem;
    vector<int> used(N + 1);
    used[1] = 1;
    for (int x : q) used[x] = 1;

    int a0 = q[0];
    for (int cand = a0 + 1; cand <= N; ++cand) {
        if (cand == 1 || used[cand]) continue;
        vector<int> rest;
        for (int v = 2; v <= N; ++v) if (!used[v] && v != cand) rest.push_back(v);
        sort(rest.begin(), rest.end());
        vector<int> ans;
        ans.push_back(cand);
        ans.push_back(1);
        ans.push_back(rest[0]);
        for (size_t i = 1; i < rest.size(); ++i) ans.push_back(rest[i]);
        print(ans);
        return 0;
    }

    vector<int> ans;
    ans.push_back(2);
    ans.push_back(1);
    for (int v = 3; v <= N; ++v) ans.push_back(v);
    print(ans);
    return 0;
}