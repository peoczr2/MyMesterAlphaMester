/*
Megoldás lényege:
Minden naphoz csak az számít, hogy az 1-es, 2-es és 3-as rendőr közül kik léptek be legalább egyszer.
Ezért naponként egy 3 bites maszkot tárolunk. A keresett napok azok, ahol a maszk nem nulla, de nem
is teljes, vagyis járt bent valaki, de nem mind a hárman.
*/
/*
Hint 1: || Többszöri belépés ugyanazon a napon nem számít többet, mint egy. ||
Hint 2: || A napi állapotot 3 bites maszkkal lehet kényelmesen tárolni. ||
Hint 3: || Azok a napok kellenek, ahol a maszk se nem 0, se nem 7. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, b;
    cin >> n >> b;
    vector<int> mask(n + 1, 0);
    for (int i = 0; i < b; ++i) {
        int id, day;
        cin >> id >> day;
        mask[day] |= 1 << (id - 1);
    }

    vector<int> answer;
    for (int day = 1; day <= n; ++day) {
        if (mask[day] != 0 && mask[day] != 7) answer.push_back(day);
    }

    cout << answer.size() << '\n';
    for (int i = 0; i < (int)answer.size(); ++i) {
        if (i) cout << ' ';
        cout << answer[i];
    }
    cout << '\n';
    return 0;
}