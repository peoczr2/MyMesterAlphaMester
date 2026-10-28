/*
Csoportképek

Feladat: M vendég érkezési és távozási idejét ismerjük (érkezéskor már, távozáskor még fényképezhető).
Csoportképeket készítünk: minden képen pontosan K vendég van, mindenki legfeljebb egy képen szerepel,
egy időpontban több kép is készülhet. Adjuk meg a képek számát, és minden képhez az időpontját és
a rajta szereplők sorszámát!

Megoldás (távozási idő szerinti mohó): Egy kép időpontja mindig eltolható a rajta szereplők közül
legkorábban távozó vendég távozási idejére. Ezért időrendben haladunk, és egy min-kupacban tartjuk
a jelen lévő, még képre nem került vendégeket távozási idő szerint. A t időpontban először betesszük
a most érkezőket. Ezután amíg a kupac tetején t-ben távozó vendég áll: ha legalább K vendég van bent,
akkor a K legkorábban távozóból (köztük ő) képet készítünk t-ben; ha nincs K vendég, akkor ő már
semmilyen képre nem kerülhet fel, kivesszük. A legkorábban távozók felhasználása a többieket a
későbbi képekre hagyja.

Időigény: O(M log M + maxIdő).

Megjegyzés: K <= 2 esetén ez a mohó bizonyíthatóan optimális (K = 2 az intervallumgráf maximális
párosítása). K >= 3-ra a feladat a diszjunkt K-klikkek pakolása intervallumgráfban, amire nem ismert
egyszerű pontos módszer, és ez a mohó ott nem mindig optimális. Ellenpélda: K = 3, vendégek
[1,1] [1,5] [1,10] [5,5] [5,5] [10,10] [10,10]: a mohó 1 képet ad, pedig 5-kor {2,4,5} és
10-kor {3,6,7} két kép. A feladatlap példájának kimenete pontosan ezt a mohó stratégiát követi.
*/
/*
Hint 1: || Egy kép időpontja eltolható a rajta lévők közül legkorábban távozó távozási idejére. ||
Hint 2: || Időrendben haladva azt a vendéget nézd, aki éppen távozik: most kell képre kerülnie, vagy soha. ||
Hint 3: || A távozó mellé a bent lévő, még szabad vendégek közül a legkorábban távozókat válaszd (min-kupac távozási idő szerint). ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // beolvasás
    int m, k;
    cin >> m >> k;
    vector<int> erk(m), tav(m);
    int maxIdo = 0;
    for (int i = 0; i < m; i++) {
        cin >> erk[i] >> tav[i];
        maxIdo = max(maxIdo, tav[i]);
    }

    // érkezők időpontonként
    vector<vector<int>> erkezok(maxIdo + 1);
    for (int i = 0; i < m; i++) erkezok[erk[i]].push_back(i);

    // bent lévő, még szabad vendégek: (távozási idő, sorszám), a legkorábban távozó van felül
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> bent;
    vector<int> kepIdo;   // a képek időpontjai
    vector<int> tagok;    // a képek szereplői, képenként K darab egymás után

    for (int t = 1; t <= maxIdo; t++) {
        for (int i : erkezok[t]) bent.push({tav[i], i});

        // aki most távozik, az most kerül képre, vagy soha
        while (!bent.empty() && bent.top().first == t) {
            if ((int)bent.size() >= k) {
                kepIdo.push_back(t);
                for (int j = 0; j < k; j++) {
                    tagok.push_back(bent.top().second + 1);
                    bent.pop();
                }
            } else {
                bent.pop();   // nincs mellette elég ember, kimarad
            }
        }
    }

    // kiírás: képek száma, majd soronként időpont és szereplők
    int f = kepIdo.size();
    cout << f << '\n';
    for (int p = 0; p < f; p++) {
        cout << kepIdo[p];
        for (int j = 0; j < k; j++) cout << ' ' << tagok[p * k + j];
        cout << '\n';
    }
    return 0;
}
