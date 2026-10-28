/*
Megoldás lényege: az azonosítók egyike sem kezdőszelete a másiknak, így minden azonosító egyértelműen megkülönböztethető
a többitől valamelyik kezdőszeletével. Rendezés után a közös előtagú azonosítók egymás mellé kerülnek, ezért
egy azonosító legkisebb egyértelmű kezdőszelete a két szomszédjával való legnagyobb közös előtag hossza plusz egy.
Az eredményt az eredeti sorrendben írjuk ki.
Időigény: O(F log F) összehasonlítás, egy összehasonlítás legfeljebb 10 karakter.
*/
/*
Hint 1: || Egy azonosító k hosszú kezdőszelete akkor egyértelmű, ha nincs olyan másik azonosító, amely ugyanezzel a k karakterrel kezdődik. ||
Hint 2: || Rendezd az azonosítókat betűrendben! Ekkor azok, amelyek közös előtaggal kezdődnek, egymás mellett lesznek. ||
Hint 3: || Egy azonosító válasza a két szomszédja közül a nagyobb közös előtag hossza, plusz egy. A közös előtag hosszát karakterenként számold ki. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int f;
    cin >> f;
    vector<string> id(f);
    for (int i = 0; i < f; i++) {
        int h;
        cin >> h >> id[i];
    }

    vector<int> order(f);
    iota(order.begin(), order.end(), 0);
    sort(order.begin(), order.end(), [&](int x, int y) { return id[x] < id[y]; });

    // két azonosító legnagyobb közös előtagjának hossza
    auto lcp = [&](int x, int y) {
        const string &a = id[x], &b = id[y];
        size_t k = 0;
        while (k < a.size() && k < b.size() && a[k] == b[k]) k++;
        return (int)k;
    };

    vector<int> answer(f);
    for (int pos = 0; pos < f; pos++) {
        int cur = order[pos];
        int common = 0;
        if (pos > 0) common = max(common, lcp(cur, order[pos - 1]));
        if (pos + 1 < f) common = max(common, lcp(cur, order[pos + 1]));
        answer[cur] = common + 1;
    }

    for (int i = 0; i < f; i++) cout << answer[i] << "\n";
    return 0;
}
