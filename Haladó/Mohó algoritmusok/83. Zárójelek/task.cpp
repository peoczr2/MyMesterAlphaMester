/*
Feladat: Adott zárójelsztringeket kell olyan sorrendbe rakni, hogy az összefűzés szabályos zárójelezés legyen.
Ötlet: Minden sztringhez számoljuk: összeg (sum), és minimális prefix-egyenleg (mn). Pozitív (sum>=0) és negatív (sum<0) csoportokra bontunk.
 - Pozitívaknál a kisebb igényűek menjenek előre: need=-mn szerint növekvő (ekvivalensen mn csökkenő).
 - Negatívaknál a „végre maradó tartalék” alapján rendezünk: (sum-mn) csökkenő.
Ezen sorrend után egy lineáris ellenőrzés eldönti a létezést.
Hint 1: || Egy részsztring csak akkor tehető be, ha az aktuális egyenleg + saját minimális prefixe nem megy 0 alá. ||
Hint 2: || A pozitív és negatív összegű sztringeket külön érdemes kezelni. ||
Hint 3: || Végül mindig ellenőrizd a teljes sorrendet szimulációval (prefixek és végső egyenleg). ||
*/

#include <bits/stdc++.h>
using namespace std;

struct Item {
    int id;
    long long sum;
    long long mn;
    string s;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    vector<Item> pos, neg;
    pos.reserve(N);
    neg.reserve(N);

    vector<string> arr(N + 1);
    for (int i = 1; i <= N; ++i) {
        cin >> arr[i];
        long long bal = 0, mn = 0;
        for (char c : arr[i]) {
            if (c == '(') ++bal;
            else --bal;
            mn = min(mn, bal);
        }
        Item it{i, bal, mn, arr[i]};
        if (bal >= 0) pos.push_back(it);
        else neg.push_back(it);
    }

    sort(pos.begin(), pos.end(), [](const Item& a, const Item& b) {
        if (a.mn != b.mn) return a.mn > b.mn;
        return a.id < b.id;
    });

    sort(neg.begin(), neg.end(), [](const Item& a, const Item& b) {
        long long ka = a.sum - a.mn;
        long long kb = b.sum - b.mn;
        if (ka != kb) return ka > kb;
        return a.id < b.id;
    });

    vector<int> order;
    order.reserve(N);
    for (auto& x : pos) order.push_back(x.id);
    for (auto& x : neg) order.push_back(x.id);

    long long bal = 0;
    for (int id : order) {
        for (char c : arr[id]) {
            if (c == '(') ++bal;
            else --bal;
            if (bal < 0) {
                cout << -1 << '\n';
                return 0;
            }
        }
    }

    if (bal != 0) {
        cout << -1 << '\n';
        return 0;
    }

    for (int i = 0; i < N; ++i) {
        if (i) cout << ' ';
        cout << order[i];
    }
    cout << '\n';
    return 0;
}
