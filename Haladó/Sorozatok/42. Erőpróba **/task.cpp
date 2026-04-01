/*
Megoldas lenyege:
A három próbán szereplő azonosítókat megszámoljuk. Azok indulhatnak a negyedik
próbán, akik pontosan két próbát teljesítettek a három közül: nekik még van
esélyük a negyedik alkalommal összegyűjteni a három sikeres próbát.
*/
/*
Hint 1: || Az első három próba eredményeit össze kell számolni. ||
Hint 2: || Pontosan azok kellenek, akiknek a gyakorisága 2. ||
Hint 3: || A kimenetet növekvő sorrendben add meg. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    map<int, int> cnt;
    for (int t = 0; t < 3; ++t) {
        int k;
        cin >> k;
        for (int i = 0; i < k; ++i) {
            int id;
            cin >> id;
            ++cnt[id];
        }
    }

    vector<int> ans;
    for (auto &[id, c] : cnt) if (c == 2) ans.push_back(id);

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
