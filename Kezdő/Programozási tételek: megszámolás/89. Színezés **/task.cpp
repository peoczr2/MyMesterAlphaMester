/*
Megoldás lényege:
Jelöljük V-vel azoknak a szomszédos golyópároknak a számát, ahol a szín változik. Egy művelet egy összefüggő, azonos színű szakaszt
színez át; a szakasz belsejében nincs színváltás, így csak a szakasz két szélénél lévő határ változhat, vagyis V legfeljebb 2-vel csökken.
Mivel a végállapotban V = 0, legalább ceil(V/2) művelet kell. Ez el is érhető: ha V >= 2, egy belső futamot átszínezve két váltás egyszerre
tűnik el, V = 1 esetén pedig egyetlen művelet kell. A válasz tehát (V + 1) / 2 egész osztással.
Egy golyó átszínezésekor csak a vele szomszédos két pár változik, így V egy lekérdezésben O(1) alatt frissíthető.
Az időigény O(N + Q), a memóriaigény O(N).
*/
/*
Hint 1: || Nézd a golyókat szomszédos párokban: hány olyan hely van, ahol a két egymás melletti golyó színe eltér? Egy művelet csak a kiválasztott szakasz két szélét érintheti. ||
Hint 2: || Ha a színváltások száma V, akkor legalább ceil(V/2) művelet kell, és ki is hozható. Gondolj arra, hogy egy belső színes szakasz átszínezésekor két váltás egyszerre szűnik meg. ||
Hint 3: || Egy golyó átszínezésekor csak a két szomszédos pár állapota változhat. Ezeket a párokat a változtatás előtt és után is ellenőrizve a váltások száma O(1) alatt frissíthető. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;
    string s;
    cin >> s;
    vector<int> c(n);
    for (int i = 0; i < n; i++) c[i] = s[i] - '0';

    int valtas = 0;
    for (int i = 0; i + 1 < n; i++)
        if (c[i] != c[i + 1]) valtas++;
    cout << (valtas + 1) / 2 << "\n";

    while (q--) {
        int k;
        cin >> k;
        k--;
        if (k > 0 && c[k - 1] != c[k]) valtas--;
        if (k + 1 < n && c[k] != c[k + 1]) valtas--;
        c[k] ^= 1;
        if (k > 0 && c[k - 1] != c[k]) valtas++;
        if (k + 1 < n && c[k] != c[k + 1]) valtas++;
        cout << (valtas + 1) / 2 << "\n";
    }
    return 0;
}
