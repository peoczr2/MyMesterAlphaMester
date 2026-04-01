#include <bits/stdc++.h>
using namespace std;

/*
Megoldási ötlet:
A bemenet folyókat ad meg, de az ellenőrzés valójában folyószakaszokra történik.
Ha egy folyóba több mellékfolyó ömlik, akkor maga a folyó több darabra szakad:
a forrástól az első találkozásig, két találkozás között, majd az utolsó találkozástól
lefelé. Emiatt az N folyóból pontosan 2N-1 darab folyószakasz keletkezik.

Ezek a folyószakaszok egy bináris fát alkotnak. Egy felelős területe ebben a fában
egy összefüggő komponens, amely legfeljebb K szakaszt tartalmaz. A cél tehát az,
hogy ezt a bináris fát a lehető legkevesebb, legfeljebb K méretű összefüggő részre
bontsuk.

Postorder bejárással minden csúcsnál két adatot tartunk fenn: hány komponens lett már
lezárva a részfában, és mekkora annak az egyetlen nyitott komponensnek a mérete,
amelyet még felvihetünk a szülő felé. Ha a két gyerek nyitott komponense és az aktuális
csúcs együtt belefér K-ba, akkor mindent összevonunk. Ha nem fér bele, a nagyobbik
nyitott komponenst lezárjuk, és a kisebbet visszük tovább, mert azt könnyebb később
még összeolvasztani.
*/
/*
Hint 1: || Először bontsd fel minden folyót a találkozások szerint külön folyószakaszokra; ezekből lesz a valódi fa. ||
Hint 2: || Egy részfában mindig legfeljebb egyetlen nyitott komponens mehet tovább a szülő felé. ||
Hint 3: || Ha két nyitott gyerek-komponens közül csak az egyik fér tovább az aktuális csúccsal együtt, a kisebbet érdemes megtartani. ||
*/

struct NodeResult {
    int closedComponents;
    int openSize;
};

static int K;
static vector<int> leftChild, rightChild;

static NodeResult dfs(int u) {
    if (u == -1) return {0, 0};

    NodeResult leftRes = dfs(leftChild[u]);
    NodeResult rightRes = dfs(rightChild[u]);

    int closed = leftRes.closedComponents + rightRes.closedComponents;
    vector<int> openParts;
    if (leftRes.openSize > 0) openParts.push_back(leftRes.openSize);
    if (rightRes.openSize > 0) openParts.push_back(rightRes.openSize);
    sort(openParts.begin(), openParts.end());

    int total = 1;
    for (int x : openParts) total += x;
    if (total <= K) return {closed, total};

    if (openParts.empty()) return {closed, 1};
    if (openParts.size() == 1) {
        if (1 + openParts[0] <= K) return {closed, 1 + openParts[0]};
        return {closed + 1, 1};
    }

    int smaller = openParts[0];
    int larger = openParts[1];
    if (1 + smaller <= K) return {closed + 1, 1 + smaller};
    if (1 + larger <= K) return {closed + 1, 1 + larger};
    return {closed + 2, 1};
}

static int buildExpandedTree(int river, const vector<vector<int>>& tributaries) {
    int prev = (int)leftChild.size();
    leftChild.push_back(-1);
    rightChild.push_back(-1);

    for (int childRiver : tributaries[river]) {
        int current = (int)leftChild.size();
        leftChild.push_back(-1);
        rightChild.push_back(-1);
        leftChild[current] = prev;
        rightChild[current] = buildExpandedTree(childRiver, tributaries);
        prev = current;
    }

    return prev;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N >> K;

    vector<vector<int>> tributaries(N + 1);
    vector<int> hasParent(N + 1, 0);

    for (int i = 0; i < N - 1; ++i) {
        int A, B;
        cin >> A >> B;
        tributaries[A].push_back(B);
        hasParent[B] = 1;
    }

    int rootRiver = 1;
    for (int i = 1; i <= N; ++i) {
        if (!hasParent[i]) {
            rootRiver = i;
            break;
        }
    }

    leftChild.clear();
    rightChild.clear();
    int rootSection = buildExpandedTree(rootRiver, tributaries);

    NodeResult ans = dfs(rootSection);
    cout << ans.closedComponents + (ans.openSize > 0 ? 1 : 0) << '\n';
    return 0;
}
