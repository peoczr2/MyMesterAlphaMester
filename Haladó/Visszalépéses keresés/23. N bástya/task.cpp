/*
Hungarian megoldás: az N bástya feladatban az összes permutációt kell kiírni,
mert minden sorhoz pontosan egy oszlop tartozik, és az egymást nem ütő bástyák
pontosan egy permutációt adnak.

Hint 1: || Egy bástya sem maradhat ugyanabban az oszlopban, ezért minden sorhoz
egyetlen oszlopot választunk. ||
Hint 2: || Az összes jó elhelyezés pontosan az 1..N permutációja. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> p(n);
    iota(p.begin(), p.end(), 1);
    do {
        for (int i = 0; i < n; ++i) {
            if (i) cout << ' ';
            cout << p[i];
        }
        cout << '\n';
    } while (next_permutation(p.begin(), p.end()));
    return 0;
}