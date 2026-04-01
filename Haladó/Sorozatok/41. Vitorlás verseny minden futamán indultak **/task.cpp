/*
Megoldas lenyege:
Az indulókat futamonként halmazba gyűjtjük, majd ezek közös metszetét keressük.
Minden futam után az a versenyző marad életben, aki az összes eddigi futamban
szerepelt. A végén a megmaradt azonosítókat növekvő sorrendben írjuk ki.
*/
/*
Hint 1: || Most azok kellenek, akik minden futamban szerepeltek. ||
Hint 2: || Az indulólistákat egymás után metszeni lehet. ||
Hint 3: || A végeredményt rendezetten írd ki. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int f;
    cin >> f;
    set<int> common;
    bool first = true;
    for (int i = 0; i < f; ++i) {
        int k;
        cin >> k;
        set<int> cur;
        for (int j = 0; j < k; ++j) {
            int id;
            cin >> id;
            cur.insert(id);
        }
        if (first) {
            common = move(cur);
            first = false;
        } else {
            set<int> next;
            for (int id : common) if (cur.count(id)) next.insert(id);
            common.swap(next);
        }
    }

    cout << common.size() << '\n';
    if (!common.empty()) {
        bool firstOut = true;
        for (int id : common) {
            if (!firstOut) cout << ' ';
            firstOut = false;
            cout << id;
        }
        cout << '\n';
    }
    return 0;
}
