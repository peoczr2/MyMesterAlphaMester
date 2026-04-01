/*
Megoldási ötlet:
A súlykorlát nagyon nagy lehet, ezért nem érdemes súly szerinti DP-t építeni. Viszont a tárgyak
hasznossága legfeljebb 1000, és összesen csak 100 tárgy van, ezért a maximális összhaszon legfeljebb
100000. Emiatt érték szerinti dinamikus programozást használunk: dp[v] a v összhaszon eléréséhez
szükséges legkisebb összsúly.

Minden tárgyat egyszer dolgozunk fel, visszafelé járva az értékeket, így egy tárgy legfeljebb egyszer
kerülhet be. A végén a legnagyobb olyan értéket keressük, amelyhez tartozó minimális súly nem haladja
meg K-t, majd az eltárolt elődökből visszaépítjük a választott tárgyak listáját.
*/
/*
Hint 1: || A súlykorlát túl nagy lehet egy klasszikus súly szerinti DP-hez, de az összes haszon felső korlátja kicsi. ||
Hint 2: || Legyen dp[v] az a legkisebb súly, amellyel pontosan v haszon elérhető. ||
Hint 3: || Rekonstrukcióhoz minden javításnál tárold el, melyik előző értékből és melyik tárggyal jutottál oda. ||
*/

#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    long long capacity;
    cin >> n >> capacity;

    vector<int> weight(n + 1), value(n + 1);
    for (int i = 1; i <= n; ++i) cin >> weight[i];
    int maxValue = 0;
    for (int i = 1; i <= n; ++i) {
        cin >> value[i];
        maxValue += value[i];
    }

    const long long inf = numeric_limits<long long>::max() / 4;
    vector<long long> previous(maxValue + 1, inf), current(maxValue + 1, inf);
    vector<vector<char>> take(n + 1, vector<char>(maxValue + 1, 0));
    previous[0] = 0;

    for (int item = 1; item <= n; ++item) {
        current = previous;
        for (int v = value[item]; v <= maxValue; ++v) {
            if (previous[v - value[item]] == inf) continue;
            long long candidate = previous[v - value[item]] + weight[item];
            if (candidate < current[v]) {
                current[v] = candidate;
                take[item][v] = 1;
            }
        }
        swap(previous, current);
    }

    int bestValue = 0;
    for (int v = 0; v <= maxValue; ++v) {
        if (previous[v] <= capacity) bestValue = v;
    }

    vector<int> chosen;
    int currentValue = bestValue;
    for (int item = n; item >= 1; --item) {
        if (currentValue >= 0 && take[item][currentValue]) {
            chosen.push_back(item);
            currentValue -= value[item];
        }
    }
    reverse(chosen.begin(), chosen.end());

    cout << bestValue << '\n';
    cout << chosen.size() << '\n';
    for (size_t i = 0; i < chosen.size(); ++i) {
        if (i > 0) cout << ' ';
        cout << chosen[i];
    }
    cout << '\n';
    return 0;
}