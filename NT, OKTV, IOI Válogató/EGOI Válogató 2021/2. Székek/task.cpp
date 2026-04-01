/*
Megoldas: ciklusbontas a szekek es a diakok permutaciojan.
Az i. szekre a jelenlegi ott ulo diak helyett az a szek kerul, ahova neki kellene
ulnie. Ezt a permutaciot ciklusokra bontva adodik a minimalis atlulesek szama:
egy ures szeket tartalmazo ciklus hossza-1, a tobbi hibas ciklus hossza+1.
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> hely(n + 1), szek(n + 2, 0);
    for (int i = 1; i <= n; ++i) {
        cin >> hely[i];
        szek[hely[i]] = i;
    }

    vector<int> kov(n + 2);
    for (int i = 1; i <= n + 1; ++i) {
        if (szek[i] == 0) kov[i] = n + 1;
        else kov[i] = szek[i];
    }

    vector<char> latott(n + 2, 0);
    long long valasz = 0;
    for (int i = 1; i <= n + 1; ++i) {
        if (latott[i]) continue;
        int aktualis = i;
        vector<int> ciklus;
        while (!latott[aktualis]) {
            latott[aktualis] = 1;
            ciklus.push_back(aktualis);
            aktualis = kov[aktualis];
        }
        if ((int)ciklus.size() == 1 && kov[i] == i) continue;
        bool vanUres = false;
        for (int x : ciklus) if (x == n + 1) vanUres = true;
        if (vanUres) valasz += (int)ciklus.size() - 1;
        else valasz += (int)ciklus.size() + 1;
    }

    cout << valasz << '\n';
    return 0;
}