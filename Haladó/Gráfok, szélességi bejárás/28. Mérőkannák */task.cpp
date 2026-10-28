/*
Megoldás lényege:
Egy állapot a két kannában lévő víz mennyiségének (a, b) párja, összesen legfeljebb (A+1)(B+1) ≤ 10^6 állapot van. A hat művelet mindegyike egy élt jelent az állapotgráfban, és minden művelet egy lépésnek számít, ezért a legkevesebb lépés szélességi bejárással (BFS) található meg. A BFS-ben minden állapothoz eltároljuk az előző állapotot és a használt műveletet, így az első olyan állapot, ahol az A-literes kannában L liter van, visszakövetéssel adja a lépéssorozatot. Ha a célállapot nem érhető el, nincs megoldás, és 0-t írunk ki. Az idő és a memória O(A·B).
*/
/*
Hint 1: || Az állapot legyen a két kanna aktuális vízmennyiségének párja (a, b), és a hat művelet mindegyike egy állapotból egy másik állapotba visz át. ||
Hint 2: || Minden művelet egy lépés, ezért a legkevesebb lépés szélességi bejárással adódik; az áttöltésnél (5, 6) a mennyiség a forrás tartalmának és a cél szabad helyének minimuma, például az 5-ösnél t = min(a, B − b). ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int A, B, L;
    cin >> A >> B >> L;

    int W = B + 1;
    auto id = [&](int a, int b) { return a * W + b; };
    int total = (A + 1) * (B + 1);
    vector<int> par(total, -1);
    vector<char> op(total, 0);
    vector<char> seen(total, 0);

    int start = id(0, 0);
    seen[start] = 1;
    queue<int> q;
    q.push(start);

    int target = -1;
    while (!q.empty() && target < 0) {
        int cur = q.front();
        q.pop();
        int a = cur / W, b = cur % W;
        for (int o = 1; o <= 6; ++o) {
            int na = a, nb = b;
            if (o == 1) na = A;
            else if (o == 2) nb = B;
            else if (o == 3) na = 0;
            else if (o == 4) nb = 0;
            else if (o == 5) {
                int t = min(a, B - b);
                na = a - t;
                nb = b + t;
            } else {
                int t = min(b, A - a);
                nb = b - t;
                na = a + t;
            }
            int nid = id(na, nb);
            if (seen[nid]) continue;
            seen[nid] = 1;
            par[nid] = cur;
            op[nid] = (char)o;
            if (na == L) {
                target = nid;
                break;
            }
            q.push(nid);
        }
    }

    if (target < 0) {
        cout << 0 << "\n";
        return 0;
    }

    vector<int> steps;
    for (int v = target; v != start; v = par[v]) steps.push_back(op[v]);
    reverse(steps.begin(), steps.end());

    cout << steps.size() << "\n";
    for (size_t i = 0; i < steps.size(); ++i) {
        if (i) cout << ' ';
        cout << steps[i];
    }
    cout << "\n";
    return 0;
}
