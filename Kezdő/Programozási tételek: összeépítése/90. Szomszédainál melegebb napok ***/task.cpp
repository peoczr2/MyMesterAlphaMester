/*
A szomszédainál melegebb nap (csúcs) a 2. és az N-1. nap között lehet, és a mérése nagyobb az előző és a következő mérésnél is. Egyetlen bejárással összegyűjtjük a csúcsok sorszámait növekvő sorrendben. Egy K-elemű részhalmaz két legtávolabbi eleme közti távolságot az legkisebbé az teszi, ha a csúcsok sorozatának K darab egymás utáni eleméből választunk. Ezért a p_{i+K-1} - p_i értékek minimumát keressük, és a minimumot adó ablak elemeit írjuk ki. Ha a csúcsok száma kisebb K-nál, a válasz -1. Az időigény O(N), a memóriaigény O(N).
*/
/*
Hint 1: || Csak a 2. és az N-1. nap között lehet csúcs. Minden ilyen napot hasonlíts az előző és a következő méréséhez, és a sorszámait tárold növekvő sorrendben. ||
Hint 2: || Ha a csúcsok sorszáma p_1 < p_2 < ... < p_c, akkor a K darab csúcs közül a legszorosabb választás mindig egymás utáni K darab. A távolság ilyenkor p_{i+K-1} - p_i, ezek minimumát keresd. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;
    vector<int> h(n + 2, 0);
    for (int i = 1; i <= n; i++) cin >> h[i];

    // a szomszédainál melegebb napok sorszámai növekvő sorrendben
    vector<int> csucs;
    for (int i = 2; i <= n - 1; i++) {
        if (h[i] > h[i - 1] && h[i] > h[i + 1]) csucs.push_back(i);
    }

    int c = (int)csucs.size();
    if (c < k) {
        cout << -1 << "\n";
        return 0;
    }

    int legjobb = INT_MAX, kezdet = 0;
    for (int i = 0; i + k - 1 < c; i++) {
        int szeles = csucs[i + k - 1] - csucs[i];
        if (szeles < legjobb) {
            legjobb = szeles;
            kezdet = i;
        }
    }

    cout << legjobb << "\n";
    for (int i = kezdet; i < kezdet + k; i++) {
        cout << csucs[i] << (i + 1 < kezdet + k ? ' ' : '\n');
    }
    return 0;
}
