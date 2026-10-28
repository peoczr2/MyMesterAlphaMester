/*
Megoldás lényege:
A z sorozat a sorozat Z-függvénye: z_i azt adja meg, hogy a sorozat i-edik kezdőszelete mekkora közös
előtaggal kezdődik az elejével. Balról jobbra haladva építjük a sorozatot. Ha az i. elem benne van egy korábbi
i'-től induló „előtag-egyezési” szakaszban (i' <= i <= i'+z_{i'}-1), akkor a_i kényszerűen egyenlő a_{i-i'+1}-gyel.
Ha nincs ilyen szakasz, akkor a_i-nek annyi kényszere van, hogy különbözzön azoktól az a_{z_j+1} elemektől, ahol
j+z_j = i (ezek az eltérések, amelyek miatt a Z-függvény pont z_j lesz). Ezek közül a legkisebb nem tiltott
pozitív egész értéket választjuk, így a kapott sorozat lexikografikusan minimális. Az egyezési szakaszok
kezelése O(N), a tiltott értékek összesen O(N) elemet néznek, így a teljes megoldás O(N log N).
*/
/*
Hint 1: || A Z-függvény értéke egy szakasz hosszát adja meg, amelyen belül a sorozat egy előtagot ismétel: ezen belül az értékek már nem választhatók szabadon. ||
Hint 2: || Egy pozícióra, amelyet nem fed le egyetlen Z-szakasz sem, a tiltott értékek a j+z_j = i pozíciókhoz tartozó a_{z_j+1} elemek. ||
Hint 3: || Balról jobbra haladva tartsd nyilván a legjobbra érő Z-szakaszt; ha az i. pozíciót lefedi, másold a megfelelő korábbi elemet, különben válaszd a legkisebb nem tiltott értéket. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> z(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        cin >> z[i];
    }

    // bucket[p]: azok a j >= 2 indexek, amelyekre j + z_j = p (p <= n)
    vector<vector<int>> bucket(n + 2);
    for (int j = 2; j <= n; ++j) {
        if (j + z[j] <= n) {
            bucket[j + z[j]].push_back(j);
        }
    }

    vector<long long> a(n + 1, 0);
    a[1] = 1;
    int boxL = 0, boxR = 0;  // a legjobbra érő Z-szakasz [boxL, boxR]
    for (int p = 2; p <= n; ++p) {
        if (z[p] > 0 && p + z[p] - 1 > boxR) {
            boxL = p;
            boxR = p + z[p] - 1;
        }
        if (boxR >= p) {
            a[p] = a[p - boxL + 1];
            continue;
        }
        set<long long> forbidden;
        for (int j : bucket[p]) {
            forbidden.insert(a[z[j] + 1]);
        }
        long long v = 1;
        while (forbidden.count(v)) {
            ++v;
        }
        a[p] = v;
    }

    for (int i = 1; i <= n; ++i) {
        cout << a[i] << (i == n ? '\n' : ' ');
    }
    return 0;
}
