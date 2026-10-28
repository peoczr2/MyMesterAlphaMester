/*
Megoldás lényege:
Két törzs egymás elleni háborúinak száma nem függ attól, ki támadott, ezért a párt mindig rendezve, a kisebb sorszámmal írjuk fel. A párok előfordulását egy map-ben számoljuk, a kulcs a rendezett sorszámpár. A map kulcs szerint növekvően jár be, így egyenlő darabszám esetén az első, lexikografikusan legkisebb párt tartjuk meg. Az időigény O(K log K), ami K ≤ 2000 mellett azonnali.
*/
/*
Hint 1: || A két törzs közötti háborúk száma nem függ attól, ki támadott: a párt mindig a kisebb sorszámmal írd fel, így a (3, 1) és az (1, 3) ugyanaz a pár. ||
Hint 2: || Számold a párok előfordulását egy map-ben, ahol a kulcs a rendezett sorszámpár. A map kulcs szerint rendezetten jár be, így a szigorú > összehasonlítással az első legnagyobb darabszámú pár marad meg. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    map<pair<int, int>, int> cnt;
    for (int i = 0; i < k; i++) {
        int a, b, s, e;
        cin >> a >> b >> s >> e;
        cnt[make_pair(min(a, b), max(a, b))]++;
    }

    pair<int, int> best{0, 0};
    int bestCnt = 0;
    for (const auto &[p, c] : cnt) {
        if (c > bestCnt) {
            bestCnt = c;
            best = p;
        }
    }

    cout << best.first << " " << best.second << "\n";
    return 0;
}
