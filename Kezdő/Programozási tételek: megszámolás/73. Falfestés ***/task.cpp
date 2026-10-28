/*
Megoldás lényege:
Ugyanaz a szabály, mint egy lécsorban, csak most a fal egy N×M-es rácsa, és minden cellát
külön nyilvántartunk. Cellánként tároljuk a festések számát és az utolsó két festés színét.
A cella színe: fehér, ha nem festették; a festés színe, ha egyszer festették; az utolsó két
festés színe, ha az egyforma; minden más esetben barna. A festéseket sorban dolgozzuk fel:
minden téglalap minden celláját frissítjük. A végén a rácsot egyszer bejárva megszámoljuk
a piros és a zöld cellákat. Az idő O(K·N·M), ami K, N, M ≤ 100 mellett legfeljebb 10^6 lépés.
*/
/*
Hint 1: || A feladat ugyanaz, mint egy lécsorban, csak most egy sor–oszlop rácson dolgozunk, ezért minden cellát külön kell nyilvántartani. ||
Hint 2: || Cellánként tárolj három adatot: a festések számát, az utolsó festés színét és az azt megelőző festés színét. ||
Hint 3: || A téglalapok sorban jönnek, és mindegyik téglalap minden cellájára ugyanazt a frissítést végezd el. A végén minden cellánál döntsd el a színt, és számold a pirosat és a zöldet. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int w, h, k; // w: a fal hossza (oszlop), h: a magassága (sor), k: emberek száma
    cin >> w >> h >> k;

    vector<vector<int>> cnt(h + 1, vector<int>(w + 1, 0));
    vector<vector<char>> last(h + 1, vector<char>(w + 1, 'F')), prev(h + 1, vector<char>(w + 1, 'F'));
    for (int t = 0; t < k; t++) {
        char c;
        int r1, c1, r2, c2;
        cin >> c >> r1 >> c1 >> r2 >> c2;
        for (int r = r1; r <= r2; r++) {
            for (int col = c1; col <= c2; col++) {
                prev[r][col] = last[r][col];
                last[r][col] = c;
                cnt[r][col]++;
            }
        }
    }

    int piros = 0, zold = 0;
    for (int r = 1; r <= h; r++) {
        for (int col = 1; col <= w; col++) {
            if (cnt[r][col] == 0) continue;
            if (cnt[r][col] == 1 || last[r][col] == prev[r][col]) {
                if (last[r][col] == 'P') piros++;
                else zold++;
            }
        }
    }
    cout << piros << " " << zold << "\n";
    return 0;
}
