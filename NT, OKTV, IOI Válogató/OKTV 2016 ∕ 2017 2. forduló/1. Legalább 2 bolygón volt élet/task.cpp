/*
Megoldás lényege: minden időszakaszt két eseménnyel írunk le: a kezdő évben +1, a vég utáni évben -1 bolygó. Az eseményeket koordináta szerint rendezzük, és végigmegyünk rajtuk. Két esemény között a futó összeg azt adja meg, hány bolygón volt élet, így ahol ez legalább 2, ott van keresett időszak. Az egymást közvetlenül követő ilyen szakaszokat egyetlen időszakba vonjuk össze, hogy a kimenet maximális intervallumokat adjon. Az azonos koordinátájú eseményeket együtt dolgozzuk fel, így a szomszédos időszakok sem okoznak hibás számlálást. Az időigény O(N log N), ahol N = A+B+C legfeljebb 300000.
*/
/*
Hint 1: || Ne évenként járd végig az időt (a koordináták 10^9-ig mennek), hanem arra figyelj, hogy a számláló csak az időszakok kezdő- és záróeseményeinél változik. ||
Hint 2: || Rendezd az összes kezdő (+1) és vég+1 (-1) eseményt koordináta szerint. Azonos koordinátájú eseményeket egyszerre dolgozz fel, majd a következő eseményig tartó szakaszon nézd, hogy a számláló legalább 2-e. Az egymást követő ilyen szakaszokat egyesítsd. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int a, b, c;
    cin >> a >> b >> c;
    int n = a + b + c;

    vector<pair<int, int>> ev;
    ev.reserve(2 * n);
    for (int i = 0; i < n; i++) {
        int s, e;
        cin >> s >> e;
        ev.push_back({s, +1});
        ev.push_back({e + 1, -1});
    }
    sort(ev.begin(), ev.end());

    vector<pair<int, int>> res;
    int cur = 0;
    size_t i = 0;
    while (i < ev.size()) {
        int x = ev[i].first;
        while (i < ev.size() && ev[i].first == x) {
            cur += ev[i].second;
            i++;
        }
        if (i == ev.size()) break;
        int nx = ev[i].first;
        if (cur >= 2) {
            if (!res.empty() && res.back().second == x - 1)
                res.back().second = nx - 1;
            else
                res.push_back({x, nx - 1});
        }
    }

    cout << res.size() << '\n';
    for (auto &p : res) cout << p.first << ' ' << p.second << '\n';
    return 0;
}
