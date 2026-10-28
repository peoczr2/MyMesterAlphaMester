/*
Megoldás lényege:
A lejátszási lista végtelenül ismétlődik, ezért a körhossz S a dalok hosszainak összege, és a P-edik másodperc a körön belül a (P-1) mod S eltolásnak felel meg. A dalok végződési időpontjait egyszer előtagösszeggel kiszámoljuk, majd minden lekérdezésnél bináris kereséssel (upper_bound) megkeressük az első olyan dalt, amelynek vége nagyobb az eltolásnál. Így a megoldás O(N + K log N) időben fut, ami a korlátok mellett belefér az időlimitbe. Az összegek akár 10^9 körüliek lehetnek, ezért 64 bites egészeket használunk.
*/
/*
Hint 1: || A lista végtelenül ismétlődik, így a P-edik másodperc ugyanaz, mint a körön belüli (P-1) mod S másodperc, ahol S az összes dal hosszának összege. ||
Hint 2: || Számold ki az előtagösszegeket (az első i dal végződési időpontját), majd bináris kereséssel keresd meg az első olyan dalt, amelynek végződése nagyobb az eltolásnál. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;
    vector<long long> pre(n);
    long long sum = 0;
    for (int i = 0; i < n; i++) {
        long long t;
        cin >> t;
        sum += t;
        pre[i] = sum;
    }

    for (int i = 0; i < k; i++) {
        long long p;
        cin >> p;
        long long offset = (p - 1) % sum;
        int idx = upper_bound(pre.begin(), pre.end(), offset) - pre.begin();
        cout << idx + 1 << (i + 1 < k ? ' ' : '\n');
    }
    return 0;
}
