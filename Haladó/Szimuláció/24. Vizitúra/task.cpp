/*
Először egy előre haladó szimulációval nézzük, meddig lehet eljutni, ha minden kikötőben a hajó megtöltését a lehető legtöbbre állítjuk (a kapacitás korlátja mellett): az első olyan kikötő sorszáma, ahol nem tudunk továbbindulni, a válasz. Ha az utolsó kikötőig el lehet jutni, akkor hátulról számoljuk ki, hogy az egyes kikötőkből induláskor mennyi élelmiszer kell az utolsó kikötőig, majd előre haladva minden kikötőben csak a hiányt vesszük fel. Így a hajón mindig a lehető legkevesebb élelmiszer van. A két bejárás O(N) időben fut.
*/
/*
Hint 1: || Érdemes először azt megnézni, meddig lehet eljutni, ha minden kikötőben a lehető legtöbbet visszük, mert ez a legtávolabbi elérhető kikötőt adja. ||
Hint 2: || Ha az utolsó kikötőig el lehet jutni, hátulról számold ki, mennyi élelmiszer kell egy-egy kikötőből induláskor, és előre haladva minden kikötőben csak a hiányzó részt vedd fel. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, h;
    cin >> n >> h;
    vector<int> food(n - 1), need(n - 1);
    for (int i = 0; i < n - 1; ++i) cin >> food[i] >> need[i];

    vector<int> required(n, 0);
    for (int i = n - 2; i >= 0; --i) {
        required[i] = max(0, need[i] + required[i + 1] - food[i]);
    }

    // Ha mindig a lehető legtöbbet visszük, ezzel jutunk el a legtávolabbra
    int fuel = 0;
    int reach = n;
    for (int i = 0; i < n - 1; ++i) {
        fuel = min(h, fuel + food[i]);
        if (fuel < need[i]) {
            reach = i + 1;
            break;
        }
        fuel -= need[i];
    }

    if (reach < n) {
        cout << reach << '\n';
        return 0;
    }

    vector<int> take(n - 1, 0);
    int carry = 0;
    for (int i = 0; i < n - 1; ++i) {
        int target = need[i] + required[i + 1];
        take[i] = max(0, target - carry);
        carry += take[i] - need[i];
    }
    for (int i = 0; i < n - 1; ++i) {
        if (i) cout << ' ';
        cout << take[i];
    }
    cout << '\n';
    return 0;
}