/*
Megoldás lényege:
Megfelelő pár csak olyan két játékosból áll, akiknek pólója különböző színű, így kétféle pár képezhető: zöld az első csapatból és piros a másodikból, illetve piros az elsőből és zöld a másodikból.
A két típus más-más játékosokat használ, ezért függetlenül egymástól párosíthatók; az első típusból min(az első csapat zöldjei, a második csapat pirosai) pár alakítható, a másodikból min(az első csapat pirosai, a második csapat zöldjei).
A két szám összege adja a maximumot; a karakterek megszámlálása O(N + M), ami az időkorláton belül van.
*/
/*
Hint 1: || Csak a különböző színű párok számítanak, és két ilyen típus van. Gondold végig, hogy a két típus használ-e közös játékost. ||
Hint 2: || Mindkét típusnál a két érintett csoport kisebbike adja a párok számát; számold ki a csapatonkénti zöld és piros játékosok számát, majd a két típus eredményét add össze. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    string a, b;
    cin >> n >> a >> m >> b;
    int a_z = 0, a_p = 0, b_z = 0, b_p = 0;
    for (char c : a) {
        if (c == 'z') {
            a_z++;
        } else if (c == 'p') {
            a_p++;
        }
    }
    for (char c : b) {
        if (c == 'z') {
            b_z++;
        } else if (c == 'p') {
            b_p++;
        }
    }
    int ans = min(a_z, b_p) + min(a_p, b_z);
    cout << ans << "\n";
    return 0;
}
