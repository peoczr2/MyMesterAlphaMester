/*
Feladat: A rendezett osztálynévsorokat a lehető legkevesebb lépésben kell összefésülni.
Ötlet: Ez az optimális összefésülési fa klasszikus esete: mindig a két legkisebb sorozatot érdemes összefésülni, vagyis Huffman-stratégia.
Hint 1: || Ha két sorozatot összefűzöl, a költségük összeadódik. ||
Hint 2: || A kisebb sorozatokat érdemes előbb egymáshoz adni, mert így később kevesebbszer fizeted meg ugyanazokat az elemeket. ||
Hint 3: || Min-heapből mindig a két legkisebbet vedd ki. ||
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