/*
Megoldás lényege:
Egyéni győztes az, akinek egy versenyen a legnagyobb pontszám jutott, döntetlen esetén mindazok, akik ezt elérték. Az összetett versenyben csak azok értékelhetők, akik minden versenyen elindultak és mindenhol elérték a versenyhez tartozó minimumot; az ő összpontszámukat számoljuk ki, és az összetett győztesek a legnagyobb összpontszámú értékelhetők (döntetlennél többen is). A pontszámokat egy táblázatban tároljuk, versenyek szerint sorban, és a nem induló tanulóknak a -1 értéket adjuk, mert a minimum és a pontszám is nemnegatív, így a minimum-ellenőrzés ezeknél automatikusan hibát ad. Végül a tanulók sorszám szerint növekvő sorrendben kerülnek kiírásra: minden összetett győztes mellé az IGEN vagy NEM szó kerül aszerint, hogy volt-e egyéni győzelme. Az időigény O(N·M), ami a korlátok mellett gyors.
*/
/*
Hint 1: || Két részt kell külön kezelni: az egyéni győzteseket versenyenként keresd meg, az összetett győzteseket pedig csak a szűrt tanulók közül válaszd ki. Döntetlen esetén mindenki győztes. ||
Hint 2: || Tárold egy táblázatban (versenyek × tanulók), ki mennyi pontot ért el, a nem induló tanulóknak pedig jelölő értéket (pl. -1) adj. Így egyszerűen ellenőrizhető, ki indult és ki érte el a minimumot minden versenyen. ||
Hint 3: || Az összetett pontszám csak a szűrt tanulókra számolható: add össze a pontjaikat, keresd meg a legnagyobb összeget, és az ezt elérő tanulók az összetett győztesek. Az egyéni győzelmeket egy külön logikai tömbben jegyezd fel. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    vector<int> minimum(m);
    for (int i = 0; i < m; i++) {
        cin >> minimum[i];
    }

    // score[i][s]: a s. tanuló pontszáma az i. versenyen, -1 ha nem indult
    vector<vector<int>> score(m, vector<int>(n + 1, -1));
    for (int i = 0; i < m; i++) {
        int ind;
        cin >> ind;
        for (int j = 0; j < ind; j++) {
            int s, p;
            cin >> s >> p;
            score[i][s] = p;
        }
    }

    // egyéni győztesek: versenyenként a legnagyobb pontszámot elérők (döntetlennél mindenki)
    vector<bool> wonIndividually(n + 1, false);
    for (int i = 0; i < m; i++) {
        int best = -1;
        for (int s = 1; s <= n; s++) {
            best = max(best, score[i][s]);
        }
        if (best < 0) {
            continue;  // nem volt indulló
        }
        for (int s = 1; s <= n; s++) {
            if (score[i][s] == best) {
                wonIndividually[s] = true;
            }
        }
    }

    // összetett: csak aki minden versenyen indult és elérte a minimumot
    vector<bool> qualified(n + 1, false);
    vector<long long> total(n + 1, 0);
    long long bestTotal = -1;
    for (int s = 1; s <= n; s++) {
        bool ok = true;
        long long sum = 0;
        for (int i = 0; i < m && ok; i++) {
            if (score[i][s] < minimum[i]) {
                ok = false;  // a -1 (nem indult) is ide esik, mert a minimum >= 0
            } else {
                sum += score[i][s];
            }
        }
        if (ok) {
            qualified[s] = true;
            total[s] = sum;
            bestTotal = max(bestTotal, sum);
        }
    }

    vector<int> composite;
    for (int s = 1; s <= n; s++) {
        if (qualified[s] && total[s] == bestTotal) {
            composite.push_back(s);
        }
    }

    cout << composite.size() << '\n';
    for (int s : composite) {
        cout << s << ' ' << (wonIndividually[s] ? "IGEN" : "NEM") << '\n';
    }
    return 0;
}
