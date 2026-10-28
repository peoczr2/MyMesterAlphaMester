/*
Megoldás lényege:
A lexikografikusan legnagyobb részsorozatot betűnként építjük: mindig a lehető legnagyobb betűt választjuk, amelyhez még van érvényes folytatás.
Ha van folytatás, a hosszabb sorozat mindig nagyobb, ezért nem állunk meg, amíg lehet bővíteni. Egy betű kiválasztásánál a legkorábbi, még nem használt előfordulását vesszük, mert így a hátralévő rész a lehető legbővebb.
Egy választás akkor jó, ha minden olyan betűből, amelyből a részsorozatban 1 és K-1 közötti darab van, a hátralévő részben a hiányzó darabok is megvannak.
Ezt úgy ellenőrizzük, hogy minden ilyen betűre kiszámoljuk azt a felső korlátot, amelyet a következő választott pozíciónak el kell érnie, így egy lépésben O(26) munka kell.
Az összidő O(26·N), ami N ≤ 100 000 mellett kb. 2,6·10^6 művelet.
*/
/*
Hint 1: || A lexikografikusan legnagyobb részsorozatot betűnként érdemes építeni: mindig a lehető legnagyobb betűt válaszd, amelyhez még van érvényes folytatás. Ha van folytatás, a hosszabb sorozat mindig nagyobb, ezért nem érdemes megállni. ||
Hint 2: || Egy betű kiválasztásánál a még nem használt legkorábbi előfordulását vedd, mert így a hátralévő rész a lehető legbővebb. Egy választás akkor jó, ha minden olyan betűből, amelyből a részsorozatban 1 és K-1 közötti darab van, a hátralévő részben még a hiányzó darabok is megvannak. ||
Hint 3: || Ha a részsorozatban egy c betűből cnt darab van, és K - cnt darab hiányzik, legyen T a c teljes előfordulásszáma. A hiányzó darabok akkor vannak meg a q pozíció után, ha q kisebb a c betű (T - (K - cnt))-edik, 0-tól számozott előfordulásának helyénél. Így minden lépésben elég ezeket a korlátokat kiszámolni és a legkisebbet, illetve a második legkisebbet ismerni. ||
*/
#include <bits/stdc++.h>
using namespace std;

const int A = 26;
const int INF = INT_MAX;

int main() {
    int n, k;
    string s;
    cin >> n >> k >> s;

    // pos[c]: a c betű előfordulásainak helyei (1-alapú, növekvő sorrendben)
    vector<vector<int>> pos(A);
    for (int i = 0; i < (int)s.size(); i++) pos[s[i] - 'a'].push_back(i + 1);

    vector<int> cnt(A, 0);  // a már kiválasztott részsorozatban az egyes betűk darabszáma
    vector<int> nxt(A, 0);  // nxt[c]: pos[c]-ben az első olyan index, amely az utolsó választott pozíció után van
    int last = 0;           // az utolsó kiválasztott pozíció (1-alapú), kezdetben 0
    string ans;

    // Ha a c betűből már have darab van (1 <= have < K), a hiányzó K - have darab akkor teljesíthető,
    // ha a legkorábbi választott pozíció q-nál ezek mind későbbre esnek, vagyis q < pos[c][T - (K - have)].
    // Ezt a felső korlátot adja vissza; ha nincs korlát, INF, ha nem teljesíthető, 0.
    auto bound = [&](int c, int have) -> int {
        if (have < 1 || have >= k) return INF;
        int need = k - have;
        int t = pos[c].size();
        if (t - need < 0) return 0;
        return pos[c][t - need];
    };

    while (true) {
        // a jelenlegi állapot két legkisebb felső korlátja és a hozzájuk tartozó betű
        int m1 = -1, m1v = INF, m2v = INF;
        for (int c = 0; c < A; c++) {
            int v = bound(c, cnt[c]);
            if (v < m1v) {
                m2v = m1v;
                m1v = v;
                m1 = c;
            } else if (v < m2v) {
                m2v = v;
            }
        }

        bool found = false;
        for (int c = A - 1; c >= 0 && !found; c--) {
            if (nxt[c] >= (int)pos[c].size()) continue;
            int q = pos[c][nxt[c]];
            // a többi hiányos betű korlátja: ha c volt a legszigorúbb, a második legkisebbet kell nézni
            int otherBound = (m1 == c) ? m2v : m1v;
            int own = bound(c, cnt[c] + 1);
            if (q < otherBound && q < own) {
                found = true;
                ans += char('a' + c);
                cnt[c]++;
                last = q;
            }
        }
        if (!found) break;

        for (int d = 0; d < A; d++) {
            while (nxt[d] < (int)pos[d].size() && pos[d][nxt[d]] <= last) nxt[d]++;
        }
    }

    cout << ans << "\n";
    return 0;
}
