/*
Megoldás lényege:
Minden naphoz csak az számít, hogy az 1-es alkalmazott belépett-e, illetve a 2-es alkalmazott belépett-e.
Ezért naponként egy 2 bites maszkot tartunk fenn. A bemenet végigolvasása után azokat a napokat kell
kiírni, ahol a maszk nem 3, vagyis nem járt bent mindkét alkalmazott.
*/
/*
Hint 1: || Egy nap ugyanaz az ember többször is beléphet, de ez a válaszon nem változtat. ||
Hint 2: || Elég azt tárolni naponként, hogy az 1-es és a 2-es alkalmazott megjelent-e. ||
Hint 3: || A keresett napok azok, ahol a napi maszk nem teljes. ||
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
        if (mask[day] != 3) answer.push_back(day);
    }

    cout << answer.size() << '\n';
    for (int i = 0; i < (int)answer.size(); ++i) {
        if (i) cout << ' ';
        cout << answer[i];
    }
    cout << '\n';
    return 0;
}