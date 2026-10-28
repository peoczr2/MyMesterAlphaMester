/*
Megoldás lényege:
A munkákat a határidők szerinti növekvő sorrendben (EDD-szabály) végezzük el, mert ez minimalizálja a legnagyobb késést. Két szomszédos munka cseréjénél látszik, hogy a korábbi határidejű munka előre hozása nem növeli a késések maximumát, így a határidő szerinti sorrend optimális. Egy munka befejezési ideje az addig elvégzett munkák idejének összege, a késése pedig ez mínusz a határidő. A válasz a késések maximuma, de ha minden munka a határidő előtt készül el, a válasz 0, mert a késés nem negatív időtartam. A rendezés miatt az időigény O(N log N).
*/
/*
Hint 1: || Két szomszédos munka sorrendjét cseréld meg úgy, hogy a korábbi határidejű munka kerüljön előre, és figyeld meg, mi történik a késésekkel. ||
Hint 2: || Minden munka befejezési ideje az addig elvégzett munkák idejének összege; ebből kell kivonni a munka határidejét. ||
Hint 3: || Rendezd a munkákat határidő szerint, végigmenve add össze az időket, és tartsd nyilván a késések maximumát. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<pair<int,int>> jobs(n);
    for (int i = 0; i < n; ++i) cin >> jobs[i].first >> jobs[i].second;
    sort(jobs.begin(), jobs.end(), [](auto &a, auto &b) {
        if (a.second != b.second) return a.second < b.second;
        return a.first < b.first;
    });

    long long time = 0, ans = 0;
    for (auto [t, d] : jobs) {
        time += t;
        ans = max(ans, time - d);
    }
    cout << ans << '\n';
    return 0;
}