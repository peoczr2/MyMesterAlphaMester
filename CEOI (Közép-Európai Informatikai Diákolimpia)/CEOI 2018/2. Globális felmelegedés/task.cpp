/*
Megoldás lényege:
Elég azt az esetet nézni, amikor egy előtag minden eleméből pontosan x-et vonunk le. Ha egy [l, r] intervallumhoz
d > 0-t adunk, akkor legalább ilyen jó a teljes [l, n] utótaghoz adni: az utótagon belül a sorrend nem változik,
az előtte álló elemekhez képest pedig csak könnyebb növekedni; d < 0 esetén ugyanígy az [1, r] előtagból érdemes
levonni. Mindkét esetben |d| = x a legjobb, és egy utótaghoz x-et adni ugyanaz, mint az előtagból x-et levonni.
Ekkor az LNR egy i-ig tartó, eredeti értékekkel növekvő részből és egy i utáni, szintén növekvő részből áll, és a
kettő akkor kapcsolódik, ha a második rész első eleme nagyobb t_i - x-nél. Balról a szokásos O(n log n) LNR-rel
kiszámoljuk pre[i]-t (az i-re végződő LNR hosszát), jobbról pedig ugyanezt tükrözve tartjuk, hogy az eddig látott
utótagban adott hosszú növekvő részsorozat legfeljebb milyen nagy elemmel kezdődhet; ebből bináris kereséssel
kapjuk a leghosszabb t_i - x-nél nagyobb elemmel induló folytatást. Az időigény O(n log n), független x-től.
*/
/*
Hint 1: || Nem kell minden d-t és minden intervallumot kipróbálni: mutasd meg, hogy elég egy előtag minden eleméből pontosan x-et levonni (ami ugyanaz, mint egy utótaghoz x-et adni). ||
Hint 2: || Ha az LNR előtagbeli része az i. elemmel végződik, akkor a hossz pre[i] + (az i utáni rész leghosszabb olyan növekvő részsorozata, amelynek első eleme nagyobb t_i - x-nél), ahol pre[i] az i-re végződő LNR hossza. ||
Hint 3: || A klasszikus LNR-ben tails[k] a k+1 hosszú növekvő részsorozatok legkisebb utolsó eleme. Jobbról balra haladva tartsd a tükörképét: heads[k] a k+1 hosszú részsorozatok legnagyobb első eleme (ez csökkenő tömb), és bináris kereséssel számold meg, hány k-ra nagyobb heads[k] egy küszöbnél. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    long long x;
    cin >> n >> x;
    vector<long long> t(n);
    for (auto &y : t) cin >> y;

    // pre[i]: az i-re végződő LNR hossza.
    // tails[k]: a k+1 hosszú növekvő részsorozatok legkisebb lehetséges utolsó eleme (növekvő tömb).
    vector<int> pre(n);
    vector<long long> tails;
    for (int i = 0; i < n; ++i) {
        int k = lower_bound(tails.begin(), tails.end(), t[i]) - tails.begin();
        if (k == (int)tails.size()) tails.push_back(t[i]);
        else tails[k] = t[i];
        pre[i] = k + 1;
    }

    // heads[k]: a már feldolgozott utótagban a k+1 hosszú növekvő részsorozatok
    // legnagyobb lehetséges első eleme (csökkenő tömb).
    vector<long long> heads;
    auto longestAbove = [&](long long v) {  // a leghosszabb, v-nél nagyobb elemmel kezdődő LNR hossza
        return (int)(partition_point(heads.begin(), heads.end(),
                                     [&](long long h) { return h > v; }) - heads.begin());
    };

    int best = 0;
    for (int i = n - 1; i >= 0; --i) {
        // az 1..i előtagból x-et vonunk le: az i-re végződő rész után t_j > t_i - x elemmel folytatható
        best = max(best, pre[i] + longestAbove(t[i] - x));
        int k = longestAbove(t[i]);  // az i-nél kezdődő LNR hossza k + 1
        if (k == (int)heads.size()) heads.push_back(t[i]);
        else heads[k] = t[i];
    }
    cout << best << '\n';
    return 0;
}
