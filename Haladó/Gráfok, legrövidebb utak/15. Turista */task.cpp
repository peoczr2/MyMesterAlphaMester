/*
Megoldás lényege:
A rácspontok csúcsok, két szomszédos rácspont között pontosan akkor van él, ha szintkülönbségük legfeljebb K, és az él ideje 1 + a szintkülönbség abszolút értéke, így minden súly pozitív. Dijkstra-algoritmussal kapjuk a legrövidebb időt; az útszakaszok számára a döntetlenek feloldására a kulcs (idő, szakaszok száma) rendezett pár, amelyet egy 64 bites számba csomagolunk (idő · 2^20 + szakaszok), így a relaxálás egyetlen összeadás. A kiírt szakaszszám a legrövidebb idejű utak közül a legkevesebb szakaszút adja. A sorban indexelt bináris halmaz csökkentési kulccsal legfeljebb egyszer tartalmaz csúcsot, az időigény O(NM log(NM)), a 600×600-as rácson a futás a 0,3 mp-es időlimit alatt marad.
*/
/*
Hint 1: || Minden szakasz ideje 1 + a szintkülönbség, és a K-nál nagyobb szintkülönbségű szakasz nem használható. Így súlyozott legrövidebb út feladat, a súlyok pozitívak, ezért Dijkstra működik. ||
Hint 2: || Két mennyiséget kell kezelni: az időt és az útszakaszok számát. Az időt elsődlegesen, a szakaszszámot másodlagosan minimalizáld úgy, hogy egy kulcsban adod meg, például idő · 2^20 + szakaszok, így a két szempont egy összehasonlításban megjelenik. ||
*/
#include <bits/stdc++.h>
using namespace std;

// Beolvasás pufferelt módon; a nem számjegy karaktereket (pl. CRLF, nem törő szóköz) kihagyja.
static char ibuf[1 << 16];
static int ilen = 0, ipos = 0;

int gc() {
    if (ipos == ilen) {
        ilen = (int)fread(ibuf, 1, sizeof(ibuf), stdin);
        ipos = 0;
        if (ilen <= 0) return -1;
    }
    return ibuf[ipos++];
}

long long readInt() {
    int c = gc();
    while (c != -1 && c != '-' && (c < '0' || c > '9')) c = gc();
    bool neg = false;
    if (c == '-') {
        neg = true;
        c = gc();
    }
    long long x = 0;
    while (c >= '0' && c <= '9') {
        x = x * 10 + (c - '0');
        c = gc();
    }
    return neg ? -x : x;
}

// Indexelt bináris halmaz: heapArr a csúcsok sora, posOf[v] a v helye a sorban (-1: nincs benne, -2: már lezárt).
vector<long long> key;
vector<int> heapArr, posOf;
int hsz = 0;

void siftUp(int i) {
    int v = heapArr[i];
    while (i > 0) {
        int p = (i - 1) >> 1;
        if (key[heapArr[p]] <= key[v]) break;
        heapArr[i] = heapArr[p];
        posOf[heapArr[i]] = i;
        i = p;
    }
    heapArr[i] = v;
    posOf[v] = i;
}

void siftDown(int i) {
    int v = heapArr[i];
    while (true) {
        int c = 2 * i + 1;
        if (c >= hsz) break;
        if (c + 1 < hsz && key[heapArr[c + 1]] < key[heapArr[c]]) c++;
        if (key[heapArr[c]] >= key[v]) break;
        heapArr[i] = heapArr[c];
        posOf[heapArr[i]] = i;
        i = c;
    }
    heapArr[i] = v;
    posOf[v] = i;
}

int main() {
    int N = (int)readInt(), M = (int)readInt();
    long long K = readInt();

    int total = N * M;
    vector<long long> h(total);
    for (int i = 0; i < total; i++) h[i] = readInt();

    const long long SH = 1LL << 20;  // a szakaszszám ennyi helyet kap a kulcsban
    const long long INF = LLONG_MAX;
    key.assign(total, INF);
    posOf.assign(total, -1);
    heapArr.assign(total, 0);
    key[0] = 0;
    heapArr[0] = 0;
    posOf[0] = 0;
    hsz = 1;

    const int dr[4] = {1, 0, -1, 0};
    const int dc[4] = {0, 1, 0, -1};
    const int target = total - 1;

    while (hsz > 0) {
        int u = heapArr[0];
        posOf[u] = -2;
        hsz--;
        if (hsz > 0) {
            heapArr[0] = heapArr[hsz];
            posOf[heapArr[0]] = 0;
            siftDown(0);
        }
        if (u == target) break;
        int r = u / M, c = u % M;
        for (int d = 0; d < 4; d++) {
            int nr = r + dr[d], nc = c + dc[d];
            if (nr < 0 || nr >= N || nc < 0 || nc >= M) continue;
            int v = nr * M + nc;
            if (posOf[v] == -2) continue;
            long long diff = llabs(h[u] - h[v]);
            if (diff > K) continue;
            long long nk = key[u] + (1 + diff) * SH + 1;
            if (nk < key[v]) {
                key[v] = nk;
                if (posOf[v] == -1) {
                    heapArr[hsz] = v;
                    posOf[v] = hsz;
                    hsz++;
                }
                siftUp(posOf[v]);
            }
        }
    }

    if (key[target] == INF) {
        cout << "NEM ER CELBA" << '\n';
    } else {
        cout << (key[target] / SH) << ' ' << (key[target] % SH) << '\n';
    }
    return 0;
}
