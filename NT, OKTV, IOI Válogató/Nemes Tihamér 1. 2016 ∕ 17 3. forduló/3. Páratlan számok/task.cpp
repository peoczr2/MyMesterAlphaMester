#include <bits/stdc++.h>
using namespace std;

/*
    Sorban végigszámoljuk a természetes számokat, és csak azokat számláljuk,
    amelyek bináris alakjában páratlan számú 1-es bit szerepel.
*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int i;
    cin >> i;

    int db = 0;
    long long szam = 0;
    while (db < i) {
        ++szam;
        if (__builtin_popcountll(szam) & 1) {
            ++db;
        }
    }

    cout << szam << '\n';
    return 0;
}