/*
Megoldás lényege:
Egy léc színe csak az utolsó két festés színétől függ: ha még nem festették, vagy az utolsó két festés színe azonos, a léc az utolsó festés színét kapja, különben barna lesz.
Ezért léckénként elég az utolsó festés színét nyilvántartani, és minden festésnél a fenti szabály szerint frissíteni a léc aktuális színét.
A festéseket egyenként végigvezetjük, majd megszámoljuk a piros és a zöld lécet; N és M kicsi, így az időigény O(N * M).
*/
/*
Hint 1: || Egy léc színe csak az utolsó két festéstől függ: ha ezek egyformák, vagy csak egy festés volt, a szín a festés színe lesz, különben barna. Ezt léckénként kell nyilvántartani. ||
Hint 2: || Tárolj léckénként egy „utolsó festés” értéket (0, ha még nem festették), és minden egyes festésnél az új színt ennek alapján számold ki. A végén egyszerű bejárással számold meg a piros és zöld lécet. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    // szin: 'F' fehér, 'P' piros, 'Z' zöld, 'B' barna
    vector<char> szin(n + 1, 'F');
    vector<char> utolso(n + 1, 0);
    for (int e = 0; e < m; e++) {
        char c;
        int k, v;
        cin >> c >> k >> v;
        for (int i = k; i <= v; i++) {
            if (utolso[i] == 0 || utolso[i] == c) {
                szin[i] = c;
            } else {
                szin[i] = 'B';
            }
            utolso[i] = c;
        }
    }
    int piros = 0, zold = 0;
    for (int i = 1; i <= n; i++) {
        if (szin[i] == 'P') {
            piros++;
        } else if (szin[i] == 'Z') {
            zold++;
        }
    }
    cout << piros << " " << zold << "\n";
    return 0;
}
