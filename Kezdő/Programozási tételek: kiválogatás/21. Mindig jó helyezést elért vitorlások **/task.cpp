/*
Megoldás lényege:
A pontozás, az L legjobb pontszám és a holtversenyes szabályok a kérdésre nem hatnak, ezeket
nem kell kiszámolni. Elég minden versenyzőhöz megszámolni, hány futamban került be az első K
helyezett közé. Azok a versenyzők felelnek meg, akiknek a számlálója pontosan N, vagyis minden
futamban az első K hely valamelyikén végeztek. Az eredmény első száma a darabszám, utána
növekvő sorrendben a versenyzők sorszámai következnek. Az időigény O(N*K + M), ami bőven belefér.
*/
/*
Hint 1: || Nem kell a pontszámokkal foglalkozni. Minden versenyzőhöz tartsd nyilván, hány futamban szerepelt az első K helyen. ||
Hint 2: || Az a versenyző felel meg, akinek a számlálója pontosan a futamok száma (N). A kiíráskor előbb a darabszám, utána a sorszámok kerüljenek ki növekvő sorrendben. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k, l, m;
    cin >> n >> k >> l >> m;

    vector<int> reszvetel(m + 1, 0);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < k; j++) {
            int s;
            cin >> s;
            reszvetel[s]++;
        }
    }

    vector<int> valasztott;
    for (int s = 1; s <= m; s++) {
        if (reszvetel[s] == n) {
            valasztott.push_back(s);
        }
    }

    cout << valasztott.size();
    for (int s : valasztott) {
        cout << " " << s;
    }
    cout << "\n";
    return 0;
}
