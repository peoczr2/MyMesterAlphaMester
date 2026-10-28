/*
Megoldás lényege:
Egy osztály tanulói annyiszor számítanak bele az összköltségbe, ahány összefésülésben részt vesznek, vagyis a költség az összefésülési fában a levelek súlyozott mélységösszege. Ezt a Huffman-stratégia minimalizálja: mindig a két legkisebb sorozatot egyesítjük, így a kicsik kerülnek a legmélyebbre, a nagyok a gyökér közelébe. Min-heapben ez O(N log N) időben megvalósítható, a költségek összege miatt 64 bites egészeket használunk.
*/
/*
Hint 1: || Egy osztály tanulói annyiszor kerülnek be a költségbe, ahány összefésülésben részt vesznek. ||
Hint 2: || A kisebb sorozatokat érdemes előbb egymáshoz adni, mert így később kevesebbszer fizeted meg ugyanazokat az elemeket. ||
Hint 3: || Min-heapből mindig a két legkisebbet vedd ki, egyesítsd, az összeget pedig tedd vissza a heapbe. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    priority_queue<long long, vector<long long>, greater<long long>> pq;
    for (int i = 0; i < n; ++i) {
        long long x;
        cin >> x;
        pq.push(x);
    }

    long long ans = 0;
    while (pq.size() > 1) {
        long long a = pq.top(); pq.pop();
        long long b = pq.top(); pq.pop();
        ans += a + b;
        pq.push(a + b);
    }

    cout << ans << '\n';
    return 0;
}