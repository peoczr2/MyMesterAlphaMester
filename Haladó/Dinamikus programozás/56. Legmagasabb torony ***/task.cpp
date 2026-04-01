/*
Egy stabil toronyban alulrol felfele haladva a kockak oldalhossza es sulya is nemnovekvo. Ha a
kockakat oldalhossz, majd suly szerint csokkenobe rendezzuk, akkor egy olyan lancot kell keresni,
amelyben minden kovetkezo kocka mindket adatban legfeljebb akkora, mint az elozo. Legyen dp[i]
az i-edik rendezett kockaval vegzodo legnagyobb elerheto toronymagassag. Ekkor dp[i] az i-edik
kocka oldalhossza, plusz a legjobb olyan elozo allapot, amelyre az elozo kocka ala teheto. A
szulo tombbol egy optimalis torony visszaepitheto.
*/
/*
Hint 1: || A torony alulrol felfele nemnovekvo oldalhosszu es nemnovekvo sulyu sorozat. ||
Hint 2: || Rendezd a kockakat, es keress a reszben rendezett sikban egy legjobb lancot. ||
Hint 3: || Itt az ertek nem a kockak szama, hanem az oldalhosszak osszege. ||
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

    vector<int> dp(n, 0);
    vector<int> parent(n, -1);
    int best = 0;

    for (int i = 0; i < n; ++i) {
        dp[i] = cubes[i].side;
        for (int j = 0; j < i; ++j) {
            if (cubes[j].side >= cubes[i].side && cubes[j].weight >= cubes[i].weight) {
                if (dp[j] + cubes[i].side > dp[i]) {
                    dp[i] = dp[j] + cubes[i].side;
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