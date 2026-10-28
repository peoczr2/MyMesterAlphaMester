/*
Megoldás lényege:
A térkép minden cellája csúcs, két szomszédos cella között pontosan akkor van él, ha magasságuk különbsége legfeljebb H, és az él súlya 1 + a különbség abszolút értéke. Mivel minden súly pozitív, a P-ből induló Dijkstra-algoritmus adja a legrövidebb időt: amikor Q kikerül a prioritási sorból, a távolsága a válasz, ha a sor kiürül, nincs út és -1 a kimenet. A sorban indexelt bináris halmazt használunk csökkentési kulccsal, így minden cella legfeljebb egyszer kerül a halmazba, és a memóriahasználat néhány 10^6-os tömb (kb. 16 MB), ami a 32 MiB-os limiten belül marad. Az időigény O(NM log(NM)), a legnagyobb 1000×1000-es mintán a mért futásidő a 0,4 mp-es időlimit alatt van.
*/
/*
Hint 1: || Tekints minden cellát csúcsnak, és a szomszédos cellák között húzz élt, ha a magasságkülönbség legfeljebb H; az él súlya 1 + a magasságkülönbség abszolút értéke. Így súlyozott legrövidebb út feladatot kapsz, a súlyok pedig nemnegatívak. ||
Hint 2: || Dijkstra-algoritmust használj P-ből. A prioritási sorban minden cella legfeljebb egyszer szerepeljen (csökkentési kulcs), különben a 32 MiB-os memórialimitet könnyen túllépheted; Q kiemelésekor már megállhatsz. ||
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
vector<int> dist, heapArr, posOf;
int hsz = 0;

void siftUp(int i) {
    int v = heapArr[i];
    while (i > 0) {
        int p = (i - 1) >> 1;
        if (dist[heapArr[p]] <= dist[v]) break;
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
        if (c + 1 < hsz && dist[heapArr[c + 1]] < dist[heapArr[c]]) c++;
        if (dist[heapArr[c]] >= dist[v]) break;
        heapArr[i] = heapArr[c];
        posOf[heapArr[i]] = i;
        i = c;
    }
    heapArr[i] = v;
    posOf[v] = i;
}

int main() {
    int N = (int)readInt(), M = (int)readInt(), H = (int)readInt();
    int ps = (int)readInt(), po = (int)readInt();
    int qs = (int)readInt(), qo = (int)readInt();

    int total = N * M;
    vector<int> h(total);
    for (int i = 0; i < total; i++) h[i] = (int)readInt();

    int P = (ps - 1) * M + (po - 1);
    int Q = (qs - 1) * M + (qo - 1);

    dist.assign(total, INT_MAX);
    posOf.assign(total, -1);
    heapArr.assign(total, 0);
    dist[P] = 0;
    heapArr[0] = P;
    posOf[P] = 0;
    hsz = 1;

    const int dr[4] = {1, 0, -1, 0};
    const int dc[4] = {0, 1, 0, -1};
    long long answer = -1;

    while (hsz > 0) {
        int u = heapArr[0];
        posOf[u] = -2;
        hsz--;
        if (hsz > 0) {
            heapArr[0] = heapArr[hsz];
            posOf[heapArr[0]] = 0;
            siftDown(0);
        }
        if (u == Q) {
            answer = dist[u];
            break;
        }
        int r = u / M, c = u % M;
        for (int d = 0; d < 4; d++) {
            int nr = r + dr[d], nc = c + dc[d];
            if (nr < 0 || nr >= N || nc < 0 || nc >= M) continue;
            int v = nr * M + nc;
            if (posOf[v] == -2) continue;
            int diff = abs(h[u] - h[v]);
            if (diff > H) continue;
            int nd = dist[u] + 1 + diff;
            if (nd < dist[v]) {
                dist[v] = nd;
                if (posOf[v] == -1) {
                    heapArr[hsz] = v;
                    posOf[v] = hsz;
                    hsz++;
                }
                siftUp(posOf[v]);
            }
        }
    }

    cout << answer << '\n';
    return 0;
}
