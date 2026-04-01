/*
Megoldási ötlet:
Minden szócikk pontosan egy másikra mutat, tehát funkcionális gráfot kapunk. Ennek minden komponense egy ciklusból
és az arra befelé csatlakozó fákból áll.

Az első és a harmadik kérdéshez elég megkeresni a ciklusokat. Az in-degree alapján lefaragjuk az összes olyan csúcsot,
amely biztosan nem ciklusban van. Ami megmarad, az pontosan a ciklusok uniója. Ebből kapjuk a körök számát és a
leghosszabb kör hosszát.

A második kérdéshez minden levágott csúcsra feltekerjük, hány csúcs vezethető el onnan a saját ciklusáig. Ezt a levágási
sorrend visszafelé járásával lehet megtenni: kezdetben minden csúcs értéke 1, majd egy csúcs értékét hozzáadjuk annak a
csúcsnak az értékéhez, ahova mutat. Egy ciklus teljes mérete a rajta levő csúcsok ilyen értékeinek összege.
*/
/*
Hint 1: || A funkcionális gráf komponenseiben pontosan egy ciklus van. ||
Hint 2: || Az in-degree 0 csúcsok biztosan nem tartoznak ciklushoz, őket sorban le lehet vágni. ||
Hint 3: || A ciklusba vezető fa méreteit a levágási sorrend visszafelé járva lehet összegyűjteni. ||
*/

#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> nextNode(n + 1), indeg(n + 1, 0), headRev(n + 1, -1), to(n + 1), nextEdge(n + 1);
    for (int node = 1; node <= n; ++node) {
        cin >> nextNode[node];
        ++indeg[nextNode[node]];
        to[node] = node;
        nextEdge[node] = headRev[nextNode[node]];
        headRev[nextNode[node]] = node;
    }

    queue<int> q;
    vector<char> removed(n + 1, false);
    for (int node = 1; node <= n; ++node) {
        if (indeg[node] == 0) {
            q.push(node);
            removed[node] = true;
        }
    }

    while (!q.empty()) {
        int node = q.front();
        q.pop();
        int parent = nextNode[node];
        if (--indeg[parent] == 0 && !removed[parent]) {
            removed[parent] = true;
            q.push(parent);
        }
    }

    vector<char> seenCycle(n + 1, false);
    vector<char> seenRemoved(n + 1, false);
    int cycleCount = 0;
    int longestCycle = 0;
    long long bestReach = 0;

    for (int node = 1; node <= n; ++node) {
        if (!removed[node] && !seenCycle[node]) {
            int cur = node;
            long long total = 0;
            int length = 0;
            vector<int> stack;
            do {
                seenCycle[cur] = true;
                for (int e = headRev[cur]; e != -1; e = nextEdge[e]) {
                    int child = to[e];
                    if (removed[child] && !seenRemoved[child]) {
                        seenRemoved[child] = true;
                        stack.push_back(child);
                    }
                }
                ++length;
                cur = nextNode[cur];
            } while (cur != node);

            while (!stack.empty()) {
                int u = stack.back();
                stack.pop_back();
                ++total;
                for (int e = headRev[u]; e != -1; e = nextEdge[e]) {
                    int child = to[e];
                    if (removed[child] && !seenRemoved[child]) {
                        seenRemoved[child] = true;
                        stack.push_back(child);
                    }
                }
            }

            total += length;

            ++cycleCount;
            longestCycle = max(longestCycle, length);
            bestReach = max(bestReach, total);
        }
    }

    cout << cycleCount << '\n';
    cout << bestReach << '\n';
    cout << longestCycle << '\n';
    return 0;
}
