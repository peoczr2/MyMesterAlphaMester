/*
Megoldás lényege: a kupac azonos színű blokkokból áll, és egy lépés mindig a legfelső blokkból vesz el zsetonokat, így a játék egy blokk-sorozaton fut. Egy a elemű legfelső blokk játékértéke az alatta lévő rész x értékétől függ: ha a ≤ x, akkor a-1, egyébként a. Ezt alulról felfelé számolva megkapjuk a teljes kupac értékét; ha ez nem nulla, a kezdő játékos nyer (IGEN). A nyerő lépés egyértelmű: ha x = 0, az egész legfelső blokkot elvesszük, egyébként a blokkból pontosan egy zsetont hagyunk meg, a vesztes ilyenkor csak az egyetlen zsetont veheti el. A lépéseket ezzel a szabállyal szimuláljuk, így egy játék O(N) időben megoldható.
*/
/*
Hint 1: || Egy lépés mindig a legfelső blokkból vesz el zsetonokat, ezért a kupacot blokkok sorozataként érdemes kezelni, és az alatta lévő rész játékértékét vizsgálni. ||
Hint 2: || Alulról felfelé haladva minden blokk értékét az alatta lévő rész értékéből számolhatod: ha a blokk mérete a, az alatta lévő rész értéke x, akkor a > x esetén az érték a, egyébként a-1. ||
Hint 3: || A nyerő lépés egyértelmű: ha x = 0, vedd el az egész legfelső blokkot; ha x > 0, hagyj benne pontosan egy zsetont, a vesztes ilyenkor csak egyet vehet el. ||
*/
#include <bits/stdc++.h>
using namespace std;

// Egy a elemű legfelső blokk értéke, ha az alatta lévő rész értéke x.
int ertek(int a, int x) {
    return (a <= x) ? a - 1 : a;
}

int main() {
    int n, m;
    cin >> n >> m;
    for (int game = 0; game < m; game++) {
        vector<int> szin(n);
        for (auto& c : szin) cin >> c;

        vector<int> s;  // blokkok mérete felülről lefelé
        for (int i = 0; i < n;) {
            int j = i;
            while (j < n && szin[j] == szin[i]) j++;
            s.push_back(j - i);
            i = j;
        }
        int b = s.size();

        vector<int> g(b + 1, 0);  // g[k]: a k-tól kezdődő blokkok értéke
        for (int k = b - 1; k >= 0; k--) g[k] = ertek(s[k], g[k + 1]);

        vector<int> lepesek;
        int k = 0;
        int a = (b > 0) ? s[0] : 0;
        while (k < b) {
            int x = g[k + 1];
            if (ertek(a, x) != 0) {
                if (x == 0) {
                    lepesek.push_back(a);
                    k++;
                    if (k < b) a = s[k];
                } else {
                    lepesek.push_back(a - 1);
                    a = 1;
                }
            } else {
                lepesek.push_back(1);
                k++;
                if (k < b) a = s[k];
            }
        }

        cout << (g[0] != 0 ? "IGEN" : "NEM");
        for (int v : lepesek) cout << ' ' << v;
        cout << "\n";
    }
    return 0;
}
