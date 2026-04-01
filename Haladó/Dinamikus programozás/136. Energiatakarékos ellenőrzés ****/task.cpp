/*
Megoldási ötlet:
Gyökerezzük a fát az 1-es szobában. Legyen dp[v] a minimális energia, ha Antal a v szobában áll,
csak a v lámpája ég, bejárja v teljes részfáját, majd visszatér ugyanide úgy, hogy a végén ismét
csak a v lámpája ég. Egy v gyerekének, c-nek a részfáját kétféleképpen érdemes feldolgozni.

1. A v lámpája végig ég marad. Ekkor lemegyünk c-be és visszajövünk (ez 2 energia), és amíg c
   részfáját a saját optimális módján bejárjuk, a v lámpája minden mozgás alatt plusz 1 energiát
   fogyaszt. A c részfájában pontosan 2 * (meret[c] - 1) mozgás történik, ezért ez az eset
   dp[c] + 2 * meret[c].

2. "Átvisszük" az egyetlen égő lámpát c-be. Ehhez v->c, c->v, v->c mozgásokkal és kapcsolásokkal
   4 energia kell, így c-ben marad egyedül égve a lámpa. A részfa optimális bejárása dp[c], majd
   ugyanezzel a trükkel 4 energiáért visszahozzuk az égő lámpát v-be. Ez összesen dp[c] + 8.

Más lehetőség nem lehet jobb: egy gyerekrészfa feldolgozása közben vagy a szülő lámpája marad égve,
vagy egyszer átvisszük az égő lámpát a gyökérbe és a végén vissza. Ezért

dp[v] = osszeg(dp[c] + min(2 * meret[c], 8)).

A részfák egymástól függetlenek, ezért a gyerekek hozzájárulásai egyszerűen összeadódnak. A választ
dp[1] adja, mert kezdetben felkapcsolhatjuk az 1-es lámpáját, a legvégén pedig ott le is kapcsolhatjuk.
*/
/*
Hint 1: || Először egyetlen gyerekrészfa optimális bejárását vizsgáld: jobb-e a szülő lámpáját végig égve hagyni, vagy inkább "átadni" az égő lámpát a gyereknek? ||
Hint 2: || Ha egy részfa gyökerében csak egyetlen lámpa ég, akkor a részfán belüli mozgások száma fix: minden élén pontosan kétszer kell áthaladni. ||
Hint 3: || Egy gyerekrészfára két költség közül kell választani: dp[gyerek] + 2 * meret[gyerek] vagy dp[gyerek] + 8. ||
Hint 4: || Gyökerezz a 1-es csúcsban, számold ki alulról felfelé a részfák méretét és a dp értékeket. ||
*/

#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<vector<int>> szomszedok(n + 1);
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        szomszedok[u].push_back(v);
        szomszedok[v].push_back(u);
    }

    vector<int> szulo(n + 1, 0);
    vector<int> sorrend;
    sorrend.reserve(n);
    sorrend.push_back(1);
    szulo[1] = -1;

    for (int i = 0; i < (int)sorrend.size(); ++i) {
        int csucs = sorrend[i];
        for (int szomszed : szomszedok[csucs]) {
            if (szomszed == szulo[csucs]) {
                continue;
            }
            szulo[szomszed] = csucs;
            sorrend.push_back(szomszed);
        }
    }

    vector<int> meret(n + 1, 1);
    vector<long long> dp(n + 1, 0);

    for (int i = n - 1; i >= 0; --i) {
        int csucs = sorrend[i];
        for (int gyerek : szomszedok[csucs]) {
            if (gyerek == szulo[csucs]) {
                continue;
            }
            meret[csucs] += meret[gyerek];
            dp[csucs] += dp[gyerek] + min(2LL * meret[gyerek], 8LL);
        }
    }

    cout << dp[1] << '\n';
    return 0;
}