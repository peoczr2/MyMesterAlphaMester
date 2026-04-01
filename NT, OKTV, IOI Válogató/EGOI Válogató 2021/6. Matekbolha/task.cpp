/*
Megoldas: a zarojelek nesting-tree-jeben dolgozunk.
Minden paros zarojel-intervalum egy ketterminalu gepesitett szakasz: a sajat bal/
jobb vegpontja kozotti utat, illetve a belso komponensek elott/utani prefixeket
szamoljuk. Egy komponens lehet sima atmeneti gap vagy egy belso zarojelpar.
A bolha egy adott intervallumban csak ket iranyban mehet: a hatarvonal menten,
vagy az adott intervallum sajat zarojel-elereset hasznalva a masik vegpont fele.
Ezert az adott pozicio bal/jobb vegponttól mért legrövidebb és leghosszabb utja
rekurzivan, alulról felfelé szamolhato. A ket x kozotti utat a legkisebb kozos
zarojel-intervalumban ezután a hatarvonalas ut es a sajat zarojelegyuttesen
atmeno ut kozul valasztjuk.
*/

#include <bits/stdc++.h>
using namespace std;

struct Node {
    int l = 0, r = 0;
    int parent = 0;
    vector<int> child;
    array<long long, 2> term{}; // [0]=min, [1]=max
    array<vector<long long>, 2> compLen;
    array<vector<long long>, 2> pref;
};

struct Location {
    int compIdx = 0;
    int childIdx = -1;
    bool inChild = false;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    string s;
    cin >> s;

    vector<int> match(n + 1, -1);
    vector<int> openStack;
    openStack.reserve(n);
    vector<int> posSmallestPair(n + 1, 0);
    vector<int> xPos;

    for (int i = 1; i <= n; ++i) {
        char c = s[i - 1];
        if (c == '(') {
            openStack.push_back(i);
        } else if (c == ')') {
            int j = openStack.back();
            openStack.pop_back();
            match[i] = j;
            match[j] = i;
        }
    }

    vector<pair<int, int>> pairs;
    pairs.reserve(n / 2);
    vector<int> openToId(n + 1, 0);
    vector<int> closeToId(n + 1, 0);

    openStack.clear();
    for (int i = 1; i <= n; ++i) {
        char c = s[i - 1];
        if (c == '(') {
            int id = (int)pairs.size() + 1;
            openToId[i] = id;
            openStack.push_back(id);
            pairs.push_back({i, -1});
            posSmallestPair[i] = id;
        } else if (c == ')') {
            int id = openStack.back();
            openStack.pop_back();
            pairs[id - 1].second = i;
            closeToId[i] = id;
            posSmallestPair[i] = id;
        } else {
            posSmallestPair[i] = openStack.empty() ? 0 : openStack.back();
            if (c == 'x') xPos.push_back(i);
        }
    }

    int m = (int)pairs.size();
    vector<Node> nodes(m + 1);
    nodes[0].l = 1;
    nodes[0].r = n;

    for (int id = 1; id <= m; ++id) {
        nodes[id].l = pairs[id - 1].first;
        nodes[id].r = pairs[id - 1].second;
    }

    vector<int> parentPair(m + 1, 0);
    openStack.clear();
    for (int i = 1; i <= n; ++i) {
        char c = s[i - 1];
        if (c == '(') {
            int id = openToId[i];
            parentPair[id] = openStack.empty() ? 0 : openStack.back();
            openStack.push_back(id);
        } else if (c == ')') {
            openStack.pop_back();
        }
    }

    for (int id = 1; id <= m; ++id) {
        nodes[id].parent = parentPair[id];
        if (parentPair[id] == 0) nodes[0].child.push_back(id);
        else nodes[parentPair[id]].child.push_back(id);
    }
    sort(nodes[0].child.begin(), nodes[0].child.end(), [&](int a, int b) { return nodes[a].l < nodes[b].l; });
    for (int id = 1; id <= m; ++id) {
        auto& ch = nodes[id].child;
        sort(ch.begin(), ch.end(), [&](int a, int b) { return nodes[a].l < nodes[b].l; });
    }

    auto locate = [&](int nodeId, int pos) -> Location {
        const auto& ch = nodes[nodeId].child;
        int k = (int)(upper_bound(ch.begin(), ch.end(), pos, [&](int value, int childId) {
            return value < nodes[childId].l;
        }) - ch.begin());
        int j = k - 1;
        if (j >= 0 && pos <= nodes[ch[j]].r) {
            return {2 * j + 1, j, true};
        }
        int mchild = (int)ch.size();
        int gapIdx;
        if (j < 0) gapIdx = 0;
        else if (j == mchild - 1) gapIdx = 2 * mchild;
        else gapIdx = 2 * j + 2;
        return {gapIdx, j, false};
    };

    // Elore kiszamoljuk a komponensek hosszat mindket metrikara.
    vector<int> order;
    order.reserve(m);
    for (int id = 1; id <= m; ++id) order.push_back(id);
    sort(order.begin(), order.end(), [&](int a, int b) {
        int la = nodes[a].r - nodes[a].l;
        int lb = nodes[b].r - nodes[b].l;
        if (la != lb) return la < lb;
        return a < b;
    });

    for (int id : order) {
        int childCount = (int)nodes[id].child.size();
        for (int mode = 0; mode < 2; ++mode) {
            auto& len = nodes[id].compLen[mode];
            auto& pref = nodes[id].pref[mode];
            len.clear();
            len.reserve(2 * childCount + 1);
            int prev = nodes[id].l;
            for (int cid : nodes[id].child) {
                len.push_back(nodes[cid].l - prev);
                len.push_back(nodes[cid].term[mode]);
                prev = nodes[cid].r;
            }
            len.push_back(nodes[id].r - prev);
            pref.assign(len.size() + 1, 0);
            for (int i = 0; i < (int)len.size(); ++i) pref[i + 1] = pref[i] + len[i];

            long long boundaryLen = pref.back();
            nodes[id].term[mode] = mode ? max(1LL, boundaryLen) : min(1LL, boundaryLen);
        }
    }

    auto solveMode = [&](int mode) -> long long {
        function<pair<long long, long long>(int, int)> fullEnds;
        function<long long(int, int, int)> solveNode;

        auto componentEnds = [&](int nodeId, const Location& loc, int pos) -> pair<long long, long long> {
            const auto& nd = nodes[nodeId];
            const auto& ch = nd.child;

            if (!loc.inChild) {
                int start;
                if (ch.empty() || loc.compIdx == 0) start = nd.l;
                else start = nodes[ch[loc.childIdx]].r;
                int end;
                if (ch.empty() || loc.compIdx == 2 * (int)ch.size()) end = nd.r;
                else end = nodes[ch[loc.childIdx + 1]].l;
                return {pos - start, end - pos};
            }

            int cid = ch[loc.childIdx];
            return fullEnds(cid, pos);
        };

        fullEnds = [&](int nodeId, int pos) -> pair<long long, long long> {
            if (nodeId == 0) return {0, 0};
            if (pos == nodes[nodeId].l) return {0, nodes[nodeId].term[mode]};
            if (pos == nodes[nodeId].r) return {nodes[nodeId].term[mode], 0};

            Location loc = locate(nodeId, pos);
            if (!loc.inChild) {
                const auto& nd = nodes[nodeId];
                const auto& ch = nd.child;
                int start;
                if (ch.empty() || loc.compIdx == 0) start = nd.l;
                else start = nodes[ch[loc.childIdx]].r;
                int end;
                if (ch.empty() || loc.compIdx == 2 * (int)ch.size()) end = nd.r;
                else end = nodes[ch[loc.childIdx + 1]].l;

                long long left = pos - start;
                long long right = end - pos;
                if (mode) return {max(left, 1 + right), max(right, 1 + left)};
                return {min(left, 1 + right), min(right, 1 + left)};
            }

            int cid = nodes[nodeId].child[loc.childIdx];
            return fullEnds(cid, pos);
        };

        solveNode = [&](int nodeId, int u, int v) -> long long {
            if (u == v) return 0;
            Location lu = locate(nodeId, u);
            Location lv = locate(nodeId, v);

            if (lu.compIdx == lv.compIdx) {
                if (!lu.inChild) return llabs((long long)v - u);
                int cid = nodes[nodeId].child[lu.childIdx];
                return solveNode(cid, u, v);
            }

            if (lu.compIdx > lv.compIdx) {
                swap(u, v);
                swap(lu, lv);
            }

            const auto& nd = nodes[nodeId];
            const auto& pref = nd.pref[mode];
            long long cycleLen = pref.back() + 1;

            auto eu = componentEnds(nodeId, lu, u);
            auto ev = componentEnds(nodeId, lv, v);

            long long forward = pref[lv.compIdx + 1] - pref[lu.compIdx];
            long long backward = cycleLen - forward;

            long long cand1 = eu.first + forward + ev.second;
            long long cand2 = eu.first + backward + ev.second;

            return min(cand1, cand2);
        };

        int a = xPos[0], b = xPos[1];
        if (a > b) swap(a, b);

        int commonPair = 0;
        int cur = posSmallestPair[a];
        while (cur != 0) {
            if (b >= nodes[cur].l && b <= nodes[cur].r) {
                commonPair = cur;
                break;
            }
            cur = nodes[cur].parent;
        }

        if (commonPair == 0) {
            return llabs((long long)b - a);
        }

        return solveNode(commonPair, a, b);
    };

    long long ansMin = solveMode(0);
    long long ansMax = solveMode(1);
    cout << ansMin << '\n' << ansMax << '\n';

    return 0;
}