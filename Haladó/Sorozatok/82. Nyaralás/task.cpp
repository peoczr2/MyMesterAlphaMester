/*
Megoldás lényege:
Minden K hosszú időszakhoz a benne lévő minimumhőmérséklet számít, és ezek közül kell a legnagyobbat
keresni. A csúszóablak minimumát monoton deque-vel O(N)-ben meg lehet határozni.

Az ablak jobb végét növelve mindig eldobjuk hátulról a nála nem kisebb elemeket, elölről pedig azokat,
amelyek kicsúsztak az aktuális K hosszú ablakból. Az első legjobb ablakot kell kiírni.
*/
/*
Hint 1: || Nem az ablak összege vagy átlaga kell, hanem az ablakon belüli minimum. ||
Hint 2: || Csúszó minimumra a monoton deque a standard lineáris megoldás. ||
Hint 3: || Holtversenyben a legkorábbi kezdőnap maradjon meg. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;
    vector<int> temp(n + 1);
    for (int i = 1; i <= n; ++i) cin >> temp[i];

    deque<int> dq;
    int bestStart = 1;
    int bestMin = numeric_limits<int>::min();

    for (int i = 1; i <= n; ++i) {
        while (!dq.empty() && temp[dq.back()] >= temp[i]) {
            dq.pop_back();
        }
        dq.push_back(i);
        while (!dq.empty() && dq.front() <= i - k) {
            dq.pop_front();
        }

        if (i >= k) {
            int currentMin = temp[dq.front()];
            int start = i - k + 1;
            if (currentMin > bestMin) {
                bestMin = currentMin;
                bestStart = start;
            }
        }
    }

    cout << bestStart << ' ' << bestMin << '\n';
    return 0;
}