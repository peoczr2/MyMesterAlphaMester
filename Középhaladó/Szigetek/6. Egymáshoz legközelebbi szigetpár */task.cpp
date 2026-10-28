/*
Megoldás lényege:
A mérési sort ugyanúgy szigetekre bontjuk, és csak a mindkét partjával mért szigeteket tartjuk meg.
Két sziget távolsága a köztük lévő tengerszakasz: a következő sziget bal partjának sorszáma mínusz
az előző sziget jobb partjának sorszáma. Két nem szomszédos sziget távolsága mindig nagyobb,
mert közéjük esik egy harmadik sziget, ezért elég a szomszédos párokat összehasonlítani.
Balról jobbra haladva a legkisebb távolságú párt keressük, egyenlőségnél a korábbit tartjuk meg,
így az Európához legközelebbi megoldást kapjuk. Az időigény O(N).
*/
/*
Hint 1: || Szigeteket keress: a 0-ás mérések közötti, nullától különböző szakaszok közül csak azok számítanak, amelyeknek van előttük és utána 0-ás mérés. ||
Hint 2: || Két szomszédos sziget távolsága: a második sziget bal partjának sorszáma mínusz az első sziget jobb partjának sorszáma. Egy harmadik sziget közbeékelődése miatt a nem szomszédos párok távolsága nagyobb. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> h(n + 2, 0);  // h[1..n] a mérések, h[0] és h[n+1] nulla
    for (int i = 1; i <= n; i++) cin >> h[i];

    // a mindkét partjával mért szigetek [bal, jobb] sorszámai, balról jobbra
    vector<pair<int, int>> szigetek;
    int i = 1;
    while (i <= n) {
        if (h[i] == 0) {
            i++;
            continue;
        }
        int l = i;
        while (i <= n && h[i] > 0) i++;
        int r = i - 1;
        if (l > 1 && r < n) szigetek.push_back({l, r});
    }

    if (szigetek.size() < 2) {
        cout << 0 << '\n';
        return 0;
    }

    // szomszédos szigetpárok távolsága: a következő sziget bal partja mínusz az előző jobb partja
    size_t legjobb = 0;
    int legkisebb = INT_MAX;
    for (size_t k = 0; k + 1 < szigetek.size(); k++) {
        int tav = szigetek[k + 1].first - szigetek[k].second;
        if (tav < legkisebb) {  // egyenlőségnél marad a korábbi pár
            legkisebb = tav;
            legjobb = k;
        }
    }

    cout << szigetek[legjobb].first << ' ' << szigetek[legjobb].second << '\n';
    cout << szigetek[legjobb + 1].first << ' ' << szigetek[legjobb + 1].second << '\n';
    return 0;
}
