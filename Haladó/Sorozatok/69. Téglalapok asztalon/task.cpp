/*
Megoldas lenyege:
Minden lap egy [P,P+K) intervallumon ad egy D magassagot, es M(x) ezek maximuma.
A keresett ertek az upper envelope minimuma, ami csak olyan szakaszokon valtozhat,
ahol valamelyik teglalap kezdodik vagy veget er.

Sweep line-t futtatunk: a kezdeseknel betesszuk, a vegeknel kivesszuk a megfelelo magassagokat
egy multisetbol. Ket egymast koveto esemenypont kozott az aktiv maximum allando; ha a szakasz
pozitiv hosszu, akkor ez jelolt a minimumra. Ha egy ilyen szakaszon nincs aktiv teglalap,
akkor az ertek 0.
*/
/*
Hint 1: || A maximum csak esemenypontoknal valtozhat, a koztuk levo nyilt szakaszon allando. ||
Hint 2: || Kezdesnel beszurunk, vegekor torlunk egy multisetbol. ||
Hint 3: || A minimumot csak pozitiv hosszu szakaszokon szabad vizsgalni. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int h, n, k;
    cin >> h >> n >> k;

    vector<vector<int>> add(h + 1), removeAt(h + 1);
    for (int i = 0; i < n; ++i) {
        int p, d;
        cin >> p >> d;
        add[p].push_back(d);
        removeAt[p + k].push_back(d);
    }

    multiset<int> active;
    int answer = INT_MAX;
    for (int x = 0; x < h; ++x) {
        for (int value : removeAt[x]) {
            auto it = active.find(value);
            if (it != active.end()) active.erase(it);
        }
        for (int value : add[x]) active.insert(value);

        int current = active.empty() ? 0 : *active.rbegin();
        answer = min(answer, current);
    }

    cout << answer << '\n';
    return 0;
}