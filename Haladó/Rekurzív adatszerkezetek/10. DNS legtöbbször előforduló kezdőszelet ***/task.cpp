#include <bits/stdc++.h>
using namespace std;

/*
Megoldási ötlet:
Csak az első K hosszú kezdőszeleteket vizsgáljuk, tehát minden szekvenciából
legfeljebb egy darab számít. A feladat így egy egyszerű számlálás: melyik K hosszú
prefix fordul elő a legtöbbször az N szekvencia között.

Trie helyett itt elég egy hash-map is, mert K legfeljebb 50, a szekvenciák hossza
pedig rövid. Minden prefixet kulccsá alakítunk, megszámoljuk az előfordulásokat,
és a legnagyobbat kiírjuk.

Hint 1: || Minden bemeneti sorból csak az első K karakter számít. ||
Hint 2: || Az azonos prefixeket egy kulccsal könnyen összeszámolhatod. ||
Hint 3: || A válaszhoz az előfordulások számát és magát a prefixet is el kell menteni. ||
*/

int code(char c) {
    if (c == 'A') return 0;
    if (c == 'C') return 1;
    if (c == 'G') return 2;
    return 3;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, K;
    cin >> N >> K;
    unordered_map<string, int> freq;
    string best = "";
    int bestCount = 0;

    for (int i = 0; i < N; ++i) {
        string s;
        cin >> s;
        string pref = s.substr(0, min<int>(K, s.size()));
        int c = ++freq[pref];
        if (c > bestCount || (c == bestCount && pref < best)) {
            bestCount = c;
            best = pref;
        }
    }

    cout << bestCount << '\n' << best << '\n';
    return 0;
}