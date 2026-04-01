/*
Megoldási ötlet:
A B[i] értéke azt mondja meg, hogy az i. helyen álló elemhez jobbra melyik a legközelebbi nagyobb elem helye.
Ez egy erdőt ad: ha B[i] = j, akkor i-nek j a szülője. Az ilyen erdőben a szülő mindig jobbra van, és nagyobb értéket
kap a gyermekénél.

Ha az erdőt gyökerekkel együtt balról jobbra, gyerekeit balról jobbra bejárva preorderben bejárjuk, majd a bejárási
sorrend szerint N, N-1, ..., 1 értékeket írunk az indexekre, akkor éppen a kívánt next greater tömb adódik.
*/
/*
Hint 1: || A B tömbből egy jobbra mutató faerdő épül, ahol a szülő mindig nagyobb és jobbra van. ||
Hint 2: || A megfelelő sorrend egy preorder bejárás, amelyben a gyökereket és a gyerekeket is növekvő index szerint vesszük. ||
Hint 3: || A bejárási sorrend első eleme kapja a legnagyobb számot, az utolsó az 1-et. ||
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
    vector<int> nextGreater(n + 1);
    for (int i = 1; i <= n; ++i) cin >> nextGreater[i];

    vector<vector<int>> children(n + 1);
    vector<int> roots;
    for (int i = 1; i <= n; ++i) {
        if (nextGreater[i] == -1) roots.push_back(i);
        else children[nextGreater[i]].push_back(i);
    }

    vector<int> order;
    order.reserve(n);
    vector<int> stack;
    for (int i = static_cast<int>(roots.size()) - 1; i >= 0; --i) stack.push_back(roots[i]);
    while (!stack.empty()) {
        int node = stack.back();
        stack.pop_back();
        order.push_back(node);
        const auto& ch = children[node];
        for (int i = static_cast<int>(ch.size()) - 1; i >= 0; --i) stack.push_back(ch[i]);
    }

    vector<int> answer(n + 1, 0);
    for (int i = 0; i < n; ++i) answer[order[i]] = n - i;
    for (int i = 1; i <= n; ++i) {
        if (i > 1) cout << ' ';
        cout << answer[i];
    }
    cout << '\n';
    return 0;
}
