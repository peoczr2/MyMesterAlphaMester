/*
Megoldas lenyege:
Minden etel soraban felsoroljak az alapanyagkodokat es a mennyisegeket. Ezeket egy mapben
osszegezzuk, mert a map automatikusan novekvo sorrendben tarolja a kulcsokat. A vegso valasz
ennyi: azonos kodok mennyisegenek osszeadasa, majd a rendezett kiiras.
*/
/*
Hint 1: || Ugyanaz az alapanyag több ételben is szerepelhet, ezért össze kell adni a mennyiségeket. ||
Hint 2: || A kódok szerint növekvő sorrendhez elég egy rendezett asszociatív tároló. ||
Hint 3: || Az első szám minden sorban csak azt mondja meg, hány (kód, mennyiség) pár következik. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    map<int, long long> total;
    for (int i = 0; i < n; ++i) {
        int m;
        cin >> m;
        for (int j = 0; j < m; ++j) {
            int code, amount;
            cin >> code >> amount;
            total[code] += amount;
        }
    }

    cout << total.size() << '\n';
    for (const auto &entry : total) {
        cout << entry.first << ' ' << entry.second << '\n';
    }

    return 0;
}
