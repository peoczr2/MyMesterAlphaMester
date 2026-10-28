/*
    Ha egy bázis hiányzik egy K hosszú szakaszból, akkor a szakasz hossza legfeljebb
    az adott bázis két szomszédos előfordulása közti lyuk. Ezért elég minden bázisra
    megkeresni a leghosszabb hiányzó részt. Ha valamelyik bázis egyáltalán nem szerepel,
    a válasz az S hossza. Az időigény O(|S|).
*/
/*
Hint 1: || Fordítsd meg a kérdést: egy K hosszú szakasz pontosan akkor nem tartalmaz egy bázist, ha az a bázis hiányzik belőle. Így az a K jó, amelynél nincs olyan K hosszú részlet, amely valamelyik bázist kihagyja. ||

Hint 2: || Bázisonként keresd meg a leghosszabb olyan részt, amelyben az adott bázis nincs: ez a két egymás utáni előfordulás közti hézag, illetve az eleje és a vége. Ha ez g hosszú, akkor K legalább g+1; a válasz ezek maximuma, de ha valamelyik bázis hiányzik, akkor a szöveg hossza. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;

    int ans = 0;
    string b = "ACGT";
    for (char c : b) {
        int last = -1, best = 0;
        for (int i = 0; i < (int)s.size(); ++i) {
            if (s[i] == c) {
                best = max(best, i - last - 1);
                last = i;
            }
        }
        if (last == -1) {
            ans = (int)s.size();
            break;
        }
        best = max(best, (int)s.size() - last - 1);
        ans = max(ans, best + 1);
    }

    cout << ans << '\n';
    return 0;
}