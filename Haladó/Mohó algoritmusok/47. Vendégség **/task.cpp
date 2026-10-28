/*
Feladat: N vendég érkezési (E) és távozási (T) idejét ismerjük. Két vendég akkor találkozott, ha
E1 <= T2 és E2 <= T1, vagyis ha a két zárt időintervallum metszi egymást. Melyik vendég találkozott
a legkevesebb másik vendéggel, és hánnyal? Kiírás: először a találkozások száma, utána a vendég sorszáma.

Megoldás: Az i. vendég pontosan akkor NEM találkozott a j. vendéggel, ha j már az érkezése előtt
elment (T_j < E_i), vagy csak a távozása után jött (E_j > T_i). A két eset kizárja egymást, és az
i. vendég maga egyikbe sem esik bele, ezért
    találkozások(i) = (N - 1) - #{j : T_j < E_i} - #{j : E_j > T_i}.
Az idők legfeljebb 100 000-ig mennek, így időpontonkénti darabszámokból prefixösszeggel (illetve
szuffixösszeggel) mindkét darabszám O(1) alatt megvan minden vendégre. Egyenlőség esetén a kisebb
sorszámú vendéget írjuk ki.

Időigény: O(N + maxIdő). Az 1 000 000 sor és a 0,1 mp miatt gyors beolvasást használunk.
*/
/*
Hint 1: || Vendégpáronként számolni túl lassú, számold inkább azokat, akikkel valaki NEM találkozott. ||
Hint 2: || Aki nem találkozott vele, az vagy az érkezése előtt már elment, vagy csak a távozása után érkezett. ||
Hint 3: || Időpontonkénti darabszámokból prefixösszeggel mindkét szám egy lépésben megkapható. ||
*/
#include <bits/stdc++.h>
using namespace std;

const int MAXT = 100000;

// gyors beolvasás pufferrel
char buf[1 << 16];
int bufLen = 0, bufPos = 0;

int readChar() {
    if (bufPos == bufLen) {
        bufLen = (int)fread(buf, 1, sizeof(buf), stdin);
        bufPos = 0;
        if (bufLen <= 0) return -1;
    }
    return buf[bufPos++];
}

int readInt() {
    int c = readChar();
    while (c != -1 && (c < '0' || c > '9')) c = readChar();
    int x = 0;
    while (c >= '0' && c <= '9') {
        x = x * 10 + (c - '0');
        c = readChar();
    }
    return x;
}

int main() {
    // beolvasás és időpontonkénti darabszámok
    int n = readInt();
    vector<int> E(n), T(n);
    vector<int> elotteMent(MAXT + 2, 0), utanaJott(MAXT + 2, 0);
    for (int i = 0; i < n; i++) {
        E[i] = readInt();
        T[i] = readInt();
        elotteMent[T[i] + 1]++;   // t > T[i] esetén számít "korábban elmentnek"
        utanaJott[E[i] - 1]++;    // t < E[i] esetén számít "később jöttnek"
    }

    // elotteMent[t] = hány vendég ment el t előtt (T_j < t)
    for (int t = 1; t <= MAXT + 1; t++) elotteMent[t] += elotteMent[t - 1];
    // utanaJott[t] = hány vendég jött t után (E_j > t)
    for (int t = MAXT; t >= 0; t--) utanaJott[t] += utanaJott[t + 1];

    // a legkevesebb találkozás keresése
    int legjobb = INT_MAX, ki = 0;
    for (int i = 0; i < n; i++) {
        int talalkozas = (n - 1) - elotteMent[E[i]] - utanaJott[T[i]];
        if (talalkozas < legjobb) {
            legjobb = talalkozas;
            ki = i + 1;
        }
    }

    // kiírás: darabszám, sorszám
    printf("%d %d\n", legjobb, ki);
    return 0;
}
