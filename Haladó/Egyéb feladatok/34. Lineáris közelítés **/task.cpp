/*
Megoldás:
Először megkeressük az összes ismert érték helyét. Két egymást követő ismert pont között a
hiányzó elemeket a két pontot összekötő egyenesből számoljuk ki: az i-edik pozíció értéke az
adott arányban vett lineáris interpoláció, kerekítve a legközelebbi egészre. A bal szélen és a jobb
szélen ugyanezt az egyenest hosszabbítjuk meg, vagyis az első két, illetve az utolsó két ismert
pontból extrapolálunk.

Minden pozíciót pontosan egyszer töltünk ki, ezért az algoritmus O(N) idejű és O(N) memóriájú.
*/
/*
Hint 1: || Először gyűjtsd ki, mely indexeken ismert biztosan a hőmérséklet. ||
Hint 2: || Két ismert pont között az értékek egy egyenes mentén helyezkednek el. ||
Hint 3: || A széleken nincs külön trükk: az első, illetve utolsó ismert szakaszt kell tovább folytatni. ||
*/

#include <cmath>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

long long interpolate(int x1, long long y1, int x2, long long y2, int x) {
    long double value = static_cast<long double>(y1)
        + (static_cast<long double>(y2 - y1) * static_cast<long double>(x - x1))
            / static_cast<long double>(x2 - x1);
    return llround(value);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<long long> values(n);
    vector<int> known;
    for (int i = 0; i < n; ++i) {
        string token;
        cin >> token;
        if (token == "?") {
            values[i] = 0;
        } else {
            values[i] = stoll(token);
            known.push_back(i);
        }
    }

    int first = known[0];
    int second = known[1];
    for (int i = first - 1; i >= 0; --i) {
        values[i] = interpolate(first, values[first], second, values[second], i);
    }

    for (int idx = 0; idx + 1 < static_cast<int>(known.size()); ++idx) {
        int left = known[idx];
        int right = known[idx + 1];
        for (int i = left + 1; i < right; ++i) {
            values[i] = interpolate(left, values[left], right, values[right], i);
        }
    }

    int last = known.back();
    int beforeLast = known[known.size() - 2];
    for (int i = last + 1; i < n; ++i) {
        values[i] = interpolate(beforeLast, values[beforeLast], last, values[last], i);
    }

    for (int i = 0; i < n; ++i) {
        if (i > 0) {
            cout << ' ';
        }
        cout << values[i];
    }
    cout << '\n';
    return 0;
}