/*
Megoldás lényege:
Először összegyűjtjük a győzteseket: egyéni győztes az, akinek egy versenyen a legnagyobb pontszám jutott (döntetlennél mindazok, akik ezt elérték), az összetett győztesek pedig a minden versenyen elindult és a minimumokat teljesítő tanulók közül a legnagyobb összpontszámúak. Ezután minden tanulóra eldöntjük, indult-e legalább egy versenyen, és nincs-e győzelme sem egyéni, sem összetett versenyben. Ezek sorszámát növekvő sorrendben, a darabszámukkal együtt írjuk ki. A pontszámokat táblázatban tároljuk, a nem induló tanulóknak a -1 értéket adjuk, így az indulás és a minimum ellenőrzése egyszerűen elvégezhető. Az időigény O(N·M), ami a korlátok mellett gyors.
*/
/*
Hint 1: || Két halmazt kell előállítanod: az összes győztest (versenyenként és az összetettben is), és az összes olyan tanulót, aki legalább egy versenyen indult. A keresett tanulók az indulók közül kerülnek ki, akik nincsenek a győztesek között. ||
Hint 2: || Tárold versenyenként a pontszámokat egy táblázatban (a nem indulókhoz -1 tartozik), és a győzteseket egy logikai tömbben jelöld. Az összetett győztesekhez csak azokat vedd figyelembe, akik minden versenyen indultak és elérték a minimumot. ||
Hint 3: || Az összetett versenyben a szűrt tanulók összpontszámának maximumát keresd meg, és minden ezt elérő tanulót jelölj győztesnek. Végül a legalább egy versenyen indult, de nem jelölt tanulók sorszámát írd ki. ||
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

    vector<bool> hasWon(n + 1, false);

    // egyéni győztesek: versenyenként a legnagyobb pontszámot elérők
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
                hasWon[s] = true;
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
    for (int s = 1; s <= n; s++) {
        if (qualified[s] && total[s] == bestTotal) {
            hasWon[s] = true;
        }
    }

    // legalább egy versenyen indult, de sehol sem győzött
    vector<int> answer;
    for (int s = 1; s <= n; s++) {
        bool participated = false;
        for (int i = 0; i < m; i++) {
            if (score[i][s] >= 0) {
                participated = true;
                break;
            }
        }
        if (participated && !hasWon[s]) {
            answer.push_back(s);
        }
    }

    cout << answer.size();
    for (int s : answer) {
        cout << ' ' << s;
    }
    cout << '\n';
    return 0;
}
