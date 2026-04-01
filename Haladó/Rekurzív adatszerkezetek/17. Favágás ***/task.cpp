#include <bits/stdc++.h>
using namespace std;

/*
Megoldási ötlet:
Pontosan K vágást kell választanunk. Egy vágás egy csúcs alatti teljes részfát töröl,
tehát a választott vágások egymást nem fedhetik. A cél a kivágott csomópontok számának
minimalizálása, ezért minden csúcsnál azt számoljuk, hogy a részfájában pontosan k vágással
mennyi csomópontot tudunk eltüntetni.

Minden csúcsnál két alapvető eset van: vagy itt vágunk, ekkor pontosan 1 vágást használunk,
vagy a két gyerek megoldását kombináljuk, és a vágásokat közöttük osztjuk szét. Mivel a fa
bináris, a két gyerek összefésülése monotonná válik, ezért a legjobb split index kifele haladva
csak nő.
*/
/*
Hint 1: || Egy csúcsnál vagy az egész részfát vágod le, vagy a két gyerek exact megoldását kombinálod. ||
Hint 2: || Pontosan k vágásnál a gyermekek közti legjobb elosztás monotonsága miatt kétmutatósan kereshető. ||
Hint 3: || A kiválasztott vágások utólag visszafejthetők, majd a megmaradó ágak száma a teljes méretből vonható le. ||
*/

static const int INF = 1e9;

static inline int addInf(int a, int b) {
    if (a >= INF || b >= INF) return INF;
    return a + b;
}

int N, K;
int rootId;
vector<int> infected, leftChild, rightChild, parentOf, subtreeSize;
vector<char> hasBad;
vector<vector<int>> dp;
vector<vector<int>> splitChoice;
vector<char> cutHere;

void dfs(int u) {
    if (leftChild[u] != -1) dfs(leftChild[u]);
    if (rightChild[u] != -1) dfs(rightChild[u]);

    hasBad[u] = infected[u];
    subtreeSize[u] = 1;
    if (leftChild[u] != -1) {
        hasBad[u] = hasBad[u] || hasBad[leftChild[u]];
        subtreeSize[u] += subtreeSize[leftChild[u]];
    }
    if (rightChild[u] != -1) {
        hasBad[u] = hasBad[u] || hasBad[rightChild[u]];
        subtreeSize[u] += subtreeSize[rightChild[u]];
    }

    auto& cur = dp[u];
    cur.assign(K + 1, INF);
    splitChoice[u].assign(K + 1, -1);

    if (infected[u]) {
        for (int k = 0; k <= K; ++k) cur[k] = INF;
        cur[1] = subtreeSize[u];
        cutHere[u] = 1;
        return;
    }

    vector<int> leftDp(K + 1, INF), rightDp(K + 1, INF);
    leftDp[0] = rightDp[0] = 0;
    if (leftChild[u] != -1) leftDp = dp[leftChild[u]];
    if (rightChild[u] != -1) rightDp = dp[rightChild[u]];

    vector<int> splitDp(K + 1, INF);
    vector<int> bestSplit(K + 1, 0);

    for (int k = 0; k <= K; ++k) {
        int bestVal = INF;
        int bestI = 0;
        for (int i = 0; i <= k; ++i) {
            int cand = addInf(leftDp[i], rightDp[k - i]);
            if (cand < bestVal) {
                bestVal = cand;
                bestI = i;
            }
        }
        splitDp[k] = bestVal;
        bestSplit[k] = bestI;
    }

    for (int k = 0; k <= K; ++k) {
        int best = INF;
        int choice = -1;
        if (k == 0 && !hasBad[u]) {
            best = 0;
        }
        if (k == 1 && u != rootId) {
            best = subtreeSize[u];
            choice = -1;
        }
        if (splitDp[k] < best) {
            best = splitDp[k];
            choice = bestSplit[k];
        }
        cur[k] = best;
        splitChoice[u][k] = choice;
    }
}

void buildCuts(int u, int k, vector<int>& chosen) {
    if (u == -1 || !hasBad[u] || k < 0) return;
    if (infected[u] || splitChoice[u][k] == -1) {
        chosen.push_back(u);
        return;
    }
    int leftK = splitChoice[u][k];
    int rightK = k - leftK;
    if (leftChild[u] != -1) buildCuts(leftChild[u], leftK, chosen);
    if (rightChild[u] != -1) buildCuts(rightChild[u], rightK, chosen);
}

void collectSubtree(int u, vector<int>& out) {
    if (u == -1) return;
    out.push_back(u);
    collectSubtree(leftChild[u], out);
    collectSubtree(rightChild[u], out);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> K;
    infected.assign(N, 0);
    leftChild.assign(N, -1);
    rightChild.assign(N, -1);
    parentOf.assign(N, -1);
    subtreeSize.assign(N, 0);
    hasBad.assign(N, 0);
    dp.assign(N, vector<int>(K + 1, 0));
    splitChoice.assign(N, vector<int>(K + 1, -1));
    cutHere.assign(N, 0);

    for (int i = 0; i < N; ++i) {
        int id, bad, l, r;
        cin >> id >> bad >> l >> r;
        infected[id] = bad;
        leftChild[id] = l;
        rightChild[id] = r;
        if (l != -1) parentOf[l] = id;
        if (r != -1) parentOf[r] = id;
    }

    int root = 0;
    while (root < N && parentOf[root] != -1) ++root;
    rootId = root;

    dfs(root);

    vector<int> chosen;
    buildCuts(root, K, chosen);

    long long removed = 0;
    for (int x : chosen) removed += subtreeSize[x];

    cout << (N - removed) << '\n';
    for (int i = 0; i < (int)chosen.size(); ++i) {
        if (i) cout << ' ';
        cout << chosen[i];
    }
    cout << '\n';
    return 0;
}
