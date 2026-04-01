/*
Stabil toronyban alulrol felfele sem az oldalhossz, sem a suly nem nohet. A kockakat oldalhossz,
majd suly szerint csokkenobe rendezve eleg egy olyan lancot keresni, ahol minden kovetkezo kocka
mindket adatban legfeljebb akkora, mint az elozo. Legyen dp[i] az i-edik rendezett kockaval
vegzodo legnagyobb kockaszamu torony. Ekkor dp[i] = 1 + max(dp[j]) minden olyan j-re, amelyik
ala teheto az i-edik kocka. A szulo tomb segitsegevel a konkret torony is visszaepitheto.
*/
/*
Hint 1: || Ugyanaz a reszben rendezett lanc kell, mint az elozo toronyfeladatban, csak mas az ertekfuggveny. ||
Hint 2: || Most nem az osszmagassagot, hanem a kockak darabszamat maximalizaljuk. ||
Hint 3: || A rendezett lista felett egyszeru O(N^2) DP elegendo a korlatokhoz. ||
*/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct Cube {
    int side;
    int weight;
    int index;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<Cube> cubes(n);
    for (int i = 0; i < n; ++i) {
        cin >> cubes[i].side >> cubes[i].weight;
        cubes[i].index = i + 1;
    }

    sort(cubes.begin(), cubes.end(), [](const Cube& left, const Cube& right) {
        if (left.side != right.side) {
            return left.side > right.side;
        }
        if (left.weight != right.weight) {
            return left.weight > right.weight;
        }
        return left.index < right.index;
    });

    vector<int> dp(n, 1);
    vector<int> parent(n, -1);
    int best = 0;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
            if (cubes[j].side >= cubes[i].side && cubes[j].weight >= cubes[i].weight) {
                if (dp[j] + 1 > dp[i]) {
                    dp[i] = dp[j] + 1;
                    parent[i] = j;
                }
            }
        }
        if (dp[i] > dp[best]) {
            best = i;
        }
    }

    vector<int> answer;
    for (int cur = best; cur != -1; cur = parent[cur]) {
        answer.push_back(cubes[cur].index);
    }
    reverse(answer.begin(), answer.end());

    cout << dp[best] << '\n';
    for (int i = 0; i < static_cast<int>(answer.size()); ++i) {
        if (i > 0) {
            cout << ' ';
        }
        cout << answer[i];
    }
    cout << '\n';
    return 0;
}