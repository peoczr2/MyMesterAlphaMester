/*
Megoldás lényege:
Minden egyéni versenyen megkeressük a legnagyobb olyan pontszámot, amely eléri a verseny minimumát, és az ezt elérő tanulók mindegyike győztes lesz, döntetlen esetén többen is. Az összetett versenyen csak azok indulhatnak, akik mind az M egyéni versenyen indultak és mindegyiken elérték a minimumot. Közülük az összpontszámuk alapján a legnagyobb összegűek nyernek, szintén döntetlennel. Egy logikai tömbben tanulónként nyilvántartjuk, hogy nyert-e valamelyik versenyen, majd a nem nyertes sorszámokat növekvő sorrendben kiírjuk a darabszámukkal együtt. A táblázat minden cellájához legfeljebb egyszer nyúlunk, így az időigény O(N·M), ami a korlátok mellett messze a 0,1 mp alatt marad.
*/
/*
Hint 1: || Egy versenyen a győztesek azok, akik a verseny legnagyobb pontszámát érték el, feltéve hogy ez a pontszám eléri a verseny minimumát. Döntetlennél mindegyik ilyen tanuló győztes. ||
Hint 2: || Készíts egy táblázatot tanulónként és versenyenként az elért pontról, a nem induló helyeket jelöld valamilyen érvénytelen értékkel. Az összetett verseny jogosultjait ebből lehet kiválogatni: mind az M versenyen indult, és mindegyik minimumot elérte. ||
Hint 3: || Az összetett versenyen a jogosultak pontjait versenyenként összeadva kapod az összpontszámot, és az ebből legnagyobbat elérők szintén nyertesek. Végül a nem nyertes tanulók sorszámait 1-től N-ig bejárva írd ki. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    vector<int> mini(m);
    for (int i = 0; i < m; i++) {
        cin >> mini[i];
    }

    // score[s][i] = s. tanuló pontja az i. versenyen, -1 ha nem indult
    vector<vector<int>> score(n + 1, vector<int>(m, -1));
    vector<bool> won(n + 1, false);

    for (int i = 0; i < m; i++) {
        int ind;
        cin >> ind;
        vector<pair<int, int>> res(ind);  // (sorszám, pont)
        int top = -1;
        for (int j = 0; j < ind; j++) {
            cin >> res[j].first >> res[j].second;
            score[res[j].first][i] = res[j].second;
            if (res[j].second >= mini[i]) {
                top = max(top, res[j].second);
            }
        }
        if (top < 0) {
            continue;  // senki nem érte el a minimumot, nincs győztes
        }
        for (auto [s, p] : res) {
            if (p == top) {
                won[s] = true;
            }
        }
    }

    // Összetett verseny: csak az összes versenyen indult és minden minimumot elérő tanulók
    vector<bool> eligible(n + 1, false);
    vector<int> total(n + 1, 0);
    int best = -1;
    for (int s = 1; s <= n; s++) {
        bool ok = true;
        int sum = 0;
        for (int i = 0; i < m; i++) {
            if (score[s][i] < mini[i]) {  // a -1 is kisebb minden minimumnál
                ok = false;
                break;
            }
            sum += score[s][i];
        }
        if (ok) {
            eligible[s] = true;
            total[s] = sum;
            best = max(best, sum);
        }
    }
    if (best >= 0) {
        for (int s = 1; s <= n; s++) {
            if (eligible[s] && total[s] == best) {
                won[s] = true;
            }
        }
    }

    vector<int> ans;
    for (int s = 1; s <= n; s++) {
        if (!won[s]) {
            ans.push_back(s);
        }
    }

    cout << ans.size();
    for (int x : ans) {
        cout << ' ' << x;
    }
    cout << '\n';
    return 0;
}
