/*
Megoldás lényege:
Minden K hosszú ablaknál az egyenletesség a maximum és minimum különbsége. Ezért csúszóablakban
egyszerre kell fenntartani az aktuális minimumot és maximumot. Mindkettőre monoton deque használható.

Az első olyan ablakot kell megtartani, amelyik a legkisebb különbséget adja.
*/
/*
Hint 1: || A kérdés minden K hosszú ablakra csak a minimumtól és maximumtól függ. ||
Hint 2: || Csúszó minimumra és maximumra külön monoton deque vezethető. ||
Hint 3: || Holtversenyben a legkorábbi kezdőpozíció maradjon meg. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; ++i) cin >> a[i];

    deque<int> minDeque, maxDeque;
    int bestStart = 1;
    int bestDiff = numeric_limits<int>::max();

    for (int i = 1; i <= n; ++i) {
        while (!minDeque.empty() && a[minDeque.back()] >= a[i]) minDeque.pop_back();
        minDeque.push_back(i);
        while (!maxDeque.empty() && a[maxDeque.back()] <= a[i]) maxDeque.pop_back();
        maxDeque.push_back(i);

        while (!minDeque.empty() && minDeque.front() <= i - k) minDeque.pop_front();
        while (!maxDeque.empty() && maxDeque.front() <= i - k) maxDeque.pop_front();

        if (i >= k) {
            int diff = a[maxDeque.front()] - a[minDeque.front()];
            int start = i - k + 1;
            if (diff < bestDiff) {
                bestDiff = diff;
                bestStart = start;
            }
        }
    }

    cout << bestStart << ' ' << bestDiff << '\n';
    return 0;
}