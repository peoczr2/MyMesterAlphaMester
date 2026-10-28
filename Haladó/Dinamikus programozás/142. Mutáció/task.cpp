/*
Megoldás lényege:
Ez szerkesztési távolság jellegű dinamikus programozás, más költségekkel: egy betű cseréjének ára a két betű körkörös
ábécé-távolsága (min(d, 26-d), mert a z után újra az a jön), a belső beszúrás és törlés ára 2, a kód elejéről és végéről
viszont 1 energiáért lehet törölni. Ezért az optimális megoldás három részre bontható: olcsón eldobott prefix (és a második
kód elejére 2-ért beszúrt betűk), egy középső, valódi szerkesztési blokk, végül olcsón eldobott suffix (és a második kód
végére 2-ért beszúrt betűk). A középső blokk mindkét végén betűpár (egyezés vagy csere) áll, mert egy szélső beszúrást vagy
törlést olcsóbb lenne a prefix, illetve a suffix részbe áttenni. Legyen dp[i][j] a legolcsóbb olyan középső blokk ára, amely
s első i és t első j betűjét dolgozza fel, és már tartalmaz legalább egy betűpárt: az (i,j) pár vagy az (i-1,j-1) cellából
folytatódik, vagy itt kezdődik (ekkor a megelőző rész ára (i-1) + 2*(j-1)); a belső törlés és beszúrás a szomszéd cellákból
jön. Ha a blokkot az (i,j) párral zárjuk, a teljes ár dp + (M-i) + 2*(N-j), a válasz ezek minimuma (és M + 2*N, ha egyetlen
betűt sem tartunk meg). Az időigény O(M*N), a memóriaigény két sor miatt O(N).
*/
/*
Hint 1: || Ez a szerkesztési távolság (edit distance) feladat rokona: az első kód első i betűjéből a második kód első j betűjét építjük, a csere ára a két betű körkörös ábécé-távolsága, a beszúrás és a belső törlés ára 2. ||
Hint 2: || Mivel a kód elejéről és végéről 1 energiáért lehet törölni, érdemes külön kezelni a kezdő és a záró szakaszt: egy prefixet és egy suffixet olcsón eldobunk, a köztük lévő részen csak a szokásos (drágább) műveletek vannak. ||
Hint 3: || A középső rész két szélét mindig egy betűpár (egyezés vagy csere) rögzíti, különben a szélső beszúrást vagy törlést olcsóbb lenne a prefixbe, illetve a suffixbe tenni. Tárold dp[i][j]-ben a legolcsóbb középső rész árát, amely az s[i-1] és t[j-1] betűpárral végződhet; elég két sort tárolni. ||
Hint 4: || Ha a blokkot az (i,j) párral zárod, a hátralévő M-i betű törlése 1-1, a hátralévő N-j betű beszúrása 2-2 energia: ezt minden cellában vedd a válasz minimumába, a kezdőérték M + 2*N. ||
*/

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int atalakitasi_ar(char bal, char jobb) {
    int kulonbseg = abs(bal - jobb);
    return min(kulonbseg, 26 - kulonbseg);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int m, n;
    string s, t;
    cin >> m >> s >> n >> t;

    const int VEGTELEN = 1'000'000'000;

    vector<int> elozo(n + 1, VEGTELEN);
    int valasz = m + 2 * n;

    for (int i = 1; i <= m; ++i) {
        vector<int> aktualis(n + 1, VEGTELEN);

        for (int j = 1; j <= n; ++j) {
            int ar = atalakitasi_ar(s[i - 1], t[j - 1]);

            int parositas = min(elozo[j - 1], (i - 1) + 2 * (j - 1)) + ar;
            aktualis[j] = min({
                parositas,
                elozo[j] + 2,
                aktualis[j - 1] + 2
            });

            valasz = min(valasz, parositas + (m - i) + 2 * (n - j));
        }

        swap(elozo, aktualis);
    }

    cout << valasz << '\n';
    return 0;
}