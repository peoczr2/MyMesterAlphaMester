/*
Megoldás lényege:
A megmaradó sorozat minden lépés után mindig egy olyan blokk lesz, amelyet a jelenlegi intervallum
két felére vágásával kaptunk. Ezért a feladat rekurzívan oldható: ha egy blokk már csupa azonos,
akkor onnan 0 további felezés kell; különben egy felezés után a bal vagy a jobb félben folytathatjuk,
és a jobbik választást kell venni.

A rekurzió minden csúcsára eltároljuk, hogy az adott blokk egyszínű-e, illetve ha nem, akkor melyik
félben érhető el kevesebb további felezéssel egyszínű blokk.
*/
/*
Hint 1: || A megengedett végső blokk mindig egy rekurzív felezéssel kapott félblokk. ||
Hint 2: || Egy blokk akkor egyszínű, ha mindkét fele egyszínű és ugyanaz az érték bennük. ||
Hint 3: || Ha egy blokk nem egyszínű, akkor egy felezés után a jobbik fél optimális megoldását kell választani. ||
*/

#include <bits/stdc++.h>
using namespace std;

struct Result {
    bool uniform;
    int value;
    int steps;
    int bestValue;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> a(n);
    for (int &x : a) cin >> x;

    function<Result(int,int)> solve = [&](int l, int r) -> Result {
        if (r - l == 1) {
            return {true, a[l], 0, a[l]};
        }
        int m = (l + r) / 2;
        Result left = solve(l, m);
        Result right = solve(m, r);

        if (left.uniform && right.uniform && left.value == right.value) {
            return {true, left.value, 0, left.value};
        }
        if (left.steps <= right.steps) {
            return {false, -1, left.steps + 1, left.bestValue};
        }
        return {false, -1, right.steps + 1, right.bestValue};
    };

    Result answer = solve(0, n);
    cout << answer.steps << '\n' << answer.bestValue << '\n';
    return 0;
}