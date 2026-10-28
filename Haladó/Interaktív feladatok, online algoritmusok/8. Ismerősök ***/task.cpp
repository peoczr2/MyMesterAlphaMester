/*
Megoldás lényege:
A csoportok száma mindig N − (a feszítőerdő éleinek száma), ezért elég egy feszítőerdőt karbantartani. Új ismeretségnél, ha a két ember még nem volt összefüggő, az él az erdőbe kerül és a csoportok száma eggyel csökken; különben az él csak a gráfban marad. Törlésnél, ha a törölt él nem volt az erdőben, semmi nem változik. Ha az erdő éle volt, a fa két részre esik: a két rész között keresünk másik meglévő ismeretséget (szomszédsági bitsorokkal gyorsan), és ha találunk, az erdő pótéllel marad összefüggő, a csoportok száma nem változik; ha nincs, a csoportok száma eggyel nő. Egy művelet O(N + N^2 / 64) időt igényel. Az ismeretségek számát is nyilvántartjuk, így az ismétlődő kapcsolatfelvétel és törlés helyesen kezelhető.
*/
/*
Hint 1: || A csoportok száma minden pillanatban N mínusz annyi él, amennyi egy feszítőerdőben van. Így nem kell minden lépésnél újraszámolni a gráfot, elég az erdőt karbantartani. ||
Hint 2: || Új ismeretségnél az él csak akkor kerül az erdőbe, ha a két ember még nem volt összefüggő. Törlésnél csak az erdő éleinek törlése változtatja meg a csoportok számát. ||
Hint 3: || Erdő-él törlésekor a fa két részre esik. Keress a két rész között egy másik meglévő ismeretséget: ha van, az erdő pótéllel marad összefüggő, ha nincs, a csoportok száma eggyel nő. A szomszédsági mátrix sorait bitsorokban tárolva ez gyorsan megy. ||
*/
#include <bits/stdc++.h>
using namespace std;

int n;
int cnt[1000][1000];       // hány ismeretség van az adott pár között
bitset<1000> adj[1000];    // adj[u][v] = 1, ha cnt[u][v] > 0
bool inTree[1000][1000];   // a feszítőerdő éle-e
vector<int> tree[1000];    // a feszítőerdő szomszédsági listái
int treeEdges = 0;

int seenStamp[1000], curStamp = 0;
int stk[1000], compArr[1000], compLen = 0;

// Bejárja s komponensét a feszítőerdőben. Ha target >= 0, megáll, amint eléri; visszaadja, megtalálta-e.
// Ha target < 0, a teljes komponens a compArr[0..compLen) tömbbe kerül.
bool bejar(int s, int target) {
    ++curStamp;
    int sp = 0, len = 0;
    stk[sp++] = s;
    seenStamp[s] = curStamp;
    while (sp > 0) {
        int u = stk[--sp];
        compArr[len++] = u;
        if (u == target) {
            compLen = len;
            return true;
        }
        for (int v : tree[u])
            if (seenStamp[v] != curStamp) {
                seenStamp[v] = curStamp;
                stk[sp++] = v;
            }
    }
    compLen = len;
    return false;
}

void erdoElBe(int a, int b) {
    inTree[a][b] = inTree[b][a] = true;
    tree[a].push_back(b);
    tree[b].push_back(a);
}

void erdoElKi(int a, int b) {
    inTree[a][b] = inTree[b][a] = false;
    tree[a].erase(find(tree[a].begin(), tree[a].end(), b));
    tree[b].erase(find(tree[b].begin(), tree[b].end(), a));
}

void felvetel(int a, int b) {
    bool wasZero = (cnt[a][b] == 0);
    ++cnt[a][b];
    ++cnt[b][a];
    if (!wasZero) return;  // már volt kapcsolat a két ember között, az erdő nem változik

    adj[a][b] = 1;
    adj[b][a] = 1;
    if (!bejar(a, b)) {
        erdoElBe(a, b);
        ++treeEdges;
    }
}

void torles(int a, int b) {
    --cnt[a][b];
    --cnt[b][a];
    if (cnt[a][b] > 0) return;

    adj[a][b] = 0;
    adj[b][a] = 0;
    if (!inTree[a][b]) return;

    erdoElKi(a, b);
    bejar(a, -1);  // a fa a része, b része nincs benne
    bitset<1000> inSide;
    for (int i = 0; i < compLen; ++i) inSide[compArr[i]] = 1;
    for (int i = 0; i < compLen; ++i) {
        int u = compArr[i];
        bitset<1000> cand = adj[u] & ~inSide;
        if (cand.any()) {
            int v = cand._Find_first();  // pótél a két rész között
            erdoElBe(u, v);
            return;  // a fa egy éllel cserélődött, a csoportok száma nem változik
        }
    }
    --treeEdges;  // nincs pótél: a fa két részre esett
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // A bemenetet tokenenként olvassuk: a minta soraiban a helyes válasz számsora kimarad.
    cin >> n;
    string tok;
    while (cin >> tok) {
        if (tok == "v") break;
        if (tok == "f" || tok == "t") {
            int a, b;
            cin >> a >> b;
            --a;
            --b;
            if (tok == "f") felvetel(a, b);
            else torles(a, b);
            cout << n - treeEdges << '\n';
        }
    }
    return 0;
}
