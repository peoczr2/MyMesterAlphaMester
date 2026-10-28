/*
    Két ember akkor találkozik, ha zárt intervallumaik metszik egymást. Egy E ember
    találkozóinak száma: az összes olyan ember, akinek az érkezése nem későbbi E
    távozásánál, mínusz azok, akik még E érkezése előtt távoztak, mínusz E maga.
    Ezt rendezett kezdő- és végpontlistákon, bináris kereséssel számoljuk ki, így
    az időigény O(N log N).
*/
/*
Hint 1: || Két ember pontosan akkor találkozik, ha intervallumaik átfedik egymást, és az érintkezés is számít: ha az egyik ugyanabban az időpontban távozik, amikor a másik érkezik, akkor még találkoznak. ||

Hint 2: || Egy E ember [x, y] intervallumához képest két csoport nem találkozik: akik még x előtt távoztak, és akik y után érkeztek. Minden más ember találkozik vele, E-t magát leszámítva. ||

Hint 3: || Tárold külön rendezve az érkezési és a távozási időpontokat, és minden E emberre binárisan keresve számold meg a két nem találkozó csoport létszámát. A legtöbb találkozót adó E sorszámát és a találkozók számát kell kiírni. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<pair<int,int>> a(n + 1);
    for (int i = 1; i <= n; ++i) cin >> a[i].first >> a[i].second;

    vector<int> starts, ends;
    for (int i = 1; i <= n; ++i) {
        starts.push_back(a[i].first);
        ends.push_back(a[i].second);
    }
    sort(starts.begin(), starts.end());
    sort(ends.begin(), ends.end());

    int bestId = 1, bestCnt = -1;
    for (int i = 1; i <= n; ++i) {
        int x = a[i].first, y = a[i].second;
        int left = upper_bound(starts.begin(), starts.end(), y) - starts.begin();
        int right = lower_bound(ends.begin(), ends.end(), x) - ends.begin();
        int cnt = left - right - 1;
        if (cnt > bestCnt) {
            bestCnt = cnt;
            bestId = i;
        }
    }

    cout << bestId << '\n' << bestCnt << '\n';
    return 0;
}