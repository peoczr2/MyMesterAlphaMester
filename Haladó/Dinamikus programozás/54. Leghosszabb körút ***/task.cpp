/*
Minden jaratot a kisebb sorszamu kikototol a nagyobb fele iranyitva egy kormentes grafot kapunk.
Ket novekvo utat keresunk 1-bol ugyanabba a vegpontba ugy, hogy a ket ut belso csucsai ne fedjek
egymast. Legyen dp[a][b] a legtobb eddig erintett varos szama olyan allapotban, amikor ket ilyen
utunk van, a vegpontjaik a < b csucsok, es b a nagyobbik vegpont. Innen csak uj, b-nel nagyobb
csucsra lephetunk tovabb, igy biztosan nem hasznalunk mar latott varost. Ha a ket aktualis
vegpont kozott is van jarat, akkor az alacsonyabb vegpont utja befejezheto a magasabbikban, es
megkapunk egy ervenyes korutat. A szulok mentesevel egy optimalis ket ut visszaepitheto.
*/
/*
Hint 1: || A kikotok folyasirany szerinti sorrendje miatt minden ervenyes reszut novekvo sorszamokkal irhato le. ||
Hint 2: || Ket egyideju vegponttal erdemes DP-allapotot tartani: a ket reszut belso csucsai mar ekkor diszjunktak. ||
Hint 3: || Ha az aktualis ket vegpont szomszedos, akkor a kisebbikbol bele lehet lepni a nagyobbikba, ez zarja a korutat. ||
*/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct Parent {
    short previous_a;
    short previous_b;
    char type;
};

pair<vector<int>, vector<int>> build_paths(
    int a,
    int b,
    const vector<vector<Parent>>& parent
) {
    Parent info = parent[a][b];
    if (info.previous_a == -1) {
        return {{1}, {1, b}};
    }

    auto previous = build_paths(info.previous_a, info.previous_b, parent);
    if (info.type == 1) {
        vector<int> left = previous.second;
        vector<int> right = previous.first;
        right.push_back(b);
        return {left, right};
    }

    previous.second.push_back(b);
    return previous;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<vector<int>> forward(n + 1);
    vector<vector<char>> adjacent(n + 1, vector<char>(n + 1, false));
    for (int edge = 0; edge < m; ++edge) {
        int a, b;
        cin >> a >> b;
        if (a > b) {
            swap(a, b);
        }
        forward[a].push_back(b);
        adjacent[a][b] = adjacent[b][a] = true;
    }

    for (int node = 1; node <= n; ++node) {
        sort(forward[node].begin(), forward[node].end());
    }

    vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));
    vector<vector<Parent>> parent(n + 1, vector<Parent>(n + 1, Parent{-1, -1, 0}));

    for (int next : forward[1]) {
        dp[1][next] = 2;
        parent[1][next] = Parent{-1, -1, 0};
    }

    int best_value = 1;
    int best_a = 1;
    int best_b = 1;

    for (int b = 2; b <= n; ++b) {
        for (int a = 1; a < b; ++a) {
            int current = dp[a][b];
            if (current == 0) {
                continue;
            }

            if (adjacent[a][b] && current > best_value) {
                best_value = current;
                best_a = a;
                best_b = b;
            }

            for (int next : forward[a]) {
                if (next <= b) {
                    continue;
                }
                if (current + 1 > dp[b][next]) {
                    dp[b][next] = current + 1;
                    parent[b][next] = Parent{static_cast<short>(a), static_cast<short>(b), 1};
                }
            }

            for (int next : forward[b]) {
                if (next <= b) {
                    continue;
                }
                if (current + 1 > dp[a][next]) {
                    dp[a][next] = current + 1;
                    parent[a][next] = Parent{static_cast<short>(a), static_cast<short>(b), 2};
                }
            }
        }
    }

    if (best_value == 1) {
        cout << 1 << '\n';
        cout << 1 << '\n';
        cout << 1 << '\n';
        return 0;
    }

    auto paths = build_paths(best_a, best_b, parent);
    paths.first.push_back(best_b);

    cout << best_value << '\n';
    for (int index = 0; index < static_cast<int>(paths.first.size()); ++index) {
        if (index > 0) {
            cout << ' ';
        }
        cout << paths.first[index];
    }
    cout << '\n';
    for (int index = 0; index < static_cast<int>(paths.second.size()); ++index) {
        if (index > 0) {
            cout << ' ';
        }
        cout << paths.second[index];
    }
    cout << '\n';

    return 0;
}