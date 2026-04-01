/*
Megoldási ötlet:
Ez a feladat egy gyökeres fára vett minimum csúcsfedés. Minden dolgozóra igaz kell legyen,
hogy vagy ő maga megy képzésre, vagy a közvetlen főnöke. Ez pontosan azt jelenti, hogy a fa
minden élére teljesül: legalább az egyik végpontot kiválasztjuk. Fa esetén erre klasszikus kétállapotú
DP használható. Legyen dp0[u] a minimális kiválasztott dolgozószám az u részfájában, ha u NEM megy
képzésre, és dp1[u], ha u IGEN. Ha u nem megy, akkor minden gyerekének mennie kell. Ha u megy,
akkor minden gyerekénél szabadon választhatjuk a jobbik állapotot. A DP után egy második bejárással
visszaépítjük egy optimális megoldás dolgozóit is.
*/
/*
Hint 1: || Gondold át, mikor sérül a feltétel egy él mentén a főnök és a beosztott között. ||
Hint 2: || Két állapot elég minden csúcsra: mi legyen az optimum, ha az adott dolgozó megy képzésre, illetve ha nem megy. ||
Hint 3: || Ha egy dolgozó nem megy képzésre, akkor a közvetlen gyerekei közül egyik sem maradhat ki. A végén egy második bejárással vissza tudod építeni a kiválasztott halmazt. ||
*/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> parent(n + 1);
    vector<vector<int>> children(n + 1);
    for (int employee = 1; employee <= n; ++employee) {
        cin >> parent[employee];
        if (parent[employee] != 0) {
            children[parent[employee]].push_back(employee);
        }
    }

    vector<int> order;
    order.reserve(n);
    vector<int> stack;
    stack.push_back(1);
    while (!stack.empty()) {
        int node = stack.back();
        stack.pop_back();
        order.push_back(node);
        for (int child : children[node]) {
            stack.push_back(child);
        }
    }

    vector<int> dp0(n + 1, 0);
    vector<int> dp1(n + 1, 0);

    for (int index = n - 1; index >= 0; --index) {
        int node = order[index];
        dp1[node] = 1;
        for (int child : children[node]) {
            dp0[node] += dp1[child];
            dp1[node] += min(dp0[child], dp1[child]);
        }
    }

    vector<int> chosen;
    chosen.reserve(dp1[1]);

    vector<pair<int, bool>> rebuild;
    rebuild.push_back({1, false});
    while (!rebuild.empty()) {
        auto [node, parentChosen] = rebuild.back();
        rebuild.pop_back();

        bool takeNode;
        if (node == 1) {
            takeNode = true;
        } else if (!parentChosen) {
            takeNode = true;
        } else {
            takeNode = (dp1[node] <= dp0[node]);
        }

        if (takeNode) {
            chosen.push_back(node);
        }
        for (int child : children[node]) {
            rebuild.push_back({child, takeNode});
        }
    }

    sort(chosen.begin(), chosen.end());

    cout << chosen.size() << '\n';
    for (size_t i = 0; i < chosen.size(); ++i) {
        if (i > 0) {
            cout << ' ';
        }
        cout << chosen[i];
    }
    cout << '\n';

    return 0;
}