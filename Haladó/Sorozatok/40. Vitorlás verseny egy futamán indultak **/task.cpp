/*
Megoldas lenyege:
Az összes futam indulólistáját egy gyakorisági táblába gyűjtjük. Azok a versenyzők
kellenek, akik pontosan egyszer szerepelnek, ezért a végén a darabszámuk szerint
kiválogatjuk azokat az azonosítókat, amelyek gyakorisága 1.
*/
/*
Hint 1: || Minden induló azonosítóját számold meg. ||
Hint 2: || Pontosan azok kellenek, amelyeknek a gyakorisága 1. ||
Hint 3: || A kimenethez a jó azonosítókat rendezd növekvő sorrendbe. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int f;
    cin >> f;
    map<int, int> cnt;
    for (int i = 0; i < f; ++i) {
        int k;
        cin >> k;
        for (int j = 0; j < k; ++j) {
            int id;
            cin >> id;
            ++cnt[id];
        }
    }

    vector<int> ans;
    for (auto &[id, c] : cnt) if (c == 1) ans.push_back(id);
    cout << ans.size() << '\n';
    if (!ans.empty()) {
        for (int i = 0; i < (int)ans.size(); ++i) {
            if (i) cout << ' ';
            cout << ans[i];
        }
        cout << '\n';
    }
    return 0;
}
