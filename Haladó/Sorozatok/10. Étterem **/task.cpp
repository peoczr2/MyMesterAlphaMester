/*
Megoldas lenyege:
Minden etel soraban alapanyagkodok es mennyisegek vannak. Az azonos kodu tetelek mennyiseget
egy map-ben osszeadjuk, a map a kulcsokat automatikusan novekvo sorrendben tarolja.
A 0 mennyisegu tetel nem jelent felhasznalast, ezert nem kerul a map-be.
*/
/*
Hint 1: || Ugyanaz az alapanyag több ételben is szerepelhet, ezért össze kell adni a mennyiségeket. ||
Hint 2: || A kódok szerint növekvő sorrendhez elég egy rendezett asszociatív tároló. ||
Hint 3: || A 0 mennyiségű tételek nem számítanak felhasználtnak, ezeket nem kell kiírni. ||
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
            if (amount > 0) total[code] += amount;
        }
    }

    cout << total.size() << '\n';
    for (const auto &entry : total) {
        cout << entry.first << ' ' << entry.second << '\n';
    }

    return 0;
}
