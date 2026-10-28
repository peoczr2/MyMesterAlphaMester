/*
Megoldás lényege:
A kupac tetejéről csak azonos színű zsetonok vehetők el, ezért a játék a futamok hosszainak sorozatával írható le. Jelölje g_j, hogy a j-edik futam teljes hosszával kezdődő helyzetben a lépő nyer-e: g_j akkor hamis, ha a j-edik futam egy zsetonos és a következő futam kezdő helyzetében a következőként lépő fél nyer, minden más esetben igaz. Ezt a sorozat végétől indulva, egy bejárással kiszámoljuk. Egy futam részleges elvétele után is ugyanez a szabály érvényes: a helyzet vesztő, ha a futamból 1 zseton maradt és a mögötte lévő futam az ellenfélnek nyerő. A minimális eltávolítás az első olyan kezdőpozíció sorszámánál eggyel kisebb szám, ahonnan a kezdő nyer. A vesztesnek mindig csak 1 zseton elvétele lehetséges, így a lejátszás egyértelmű, és játékonként O(N) az idő.
*/
/*
Hint 1: || A kupac tetejéről csak egy futamot lehet bontani, ezért a sorozatot érdemes a színek szerinti összefüggő futamokkal, azok hosszaival leírni. ||
Hint 2: || Jobbról balra haladva számold ki, hogy egy futam teljes hosszával kezdve a lépő nyer-e: ha a következő futam kezdő helyzetében az ellenfél nyerne, akkor a jelenlegi futamból pontosan 1 zsetont kell meghagyni, különben az egész futamot el kell venni. ||
Hint 3: || Az eltávolítás után az első olyan zsetont keresd, ahonnan a kezdő nyer; ez előtt a zsetonok száma adja a válasz első számát. Utána a lépéseket ugyanezzel a szabállyal szimuláld: a nyerő fél a fenti döntést hozza, a vesztes mindig 1 zsetont vesz el. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    for (int game = 0; game < m; game++) {
        vector<int> z(n);
        for (int &x : z) cin >> x;

        // futamok hossza a kupac tetejétől
        vector<int> len;
        for (int i = 0; i < n;) {
            int j = i;
            while (j < n && z[j] == z[i]) j++;
            len.push_back(j - i);
            i = j;
        }
        int t = len.size();

        // g[j]: a j-edik futam teljes hosszával kezdve a lépő nyer-e
        vector<bool> g(t + 1, false);
        for (int j = t - 1; j >= 0; j--)
            g[j] = g[j + 1] ? (len[j] != 1) : true;

        // minimális eltávolítás: az első nyerő kezdőpozíció
        int d = 0, sj = 0, sx = 0;
        int start = 1;
        bool found = false;
        for (int j = 0; j < t && !found; j++) {
            int e = start + len[j] - 1;
            for (int p = start; p <= e; p++) {
                if (!(g[j + 1] && p == e)) {
                    d = p - 1;
                    sj = j;
                    sx = e - p + 1;
                    found = true;
                    break;
                }
            }
            start = e + 1;
        }

        // optimális lejátszás: a nyerő fél egyértelmű lépést tesz, a vesztes 1 zsetont vesz el
        cout << d;
        int j = sj, x = sx;
        while (j < t) {
            int take;
            if (!g[j + 1]) take = x;          // a következő futam vesztő: az egészet elviszi
            else if (x >= 2) take = x - 1;    // az ellenfélnek csak 1 zseton marad
            else take = 1;                    // vesztő helyzet: csak 1 zseton vehető el
            cout << ' ' << take;
            x -= take;
            if (x == 0) {
                j++;
                if (j < t) x = len[j];
            }
        }
        cout << '\n';
    }
    return 0;
}
