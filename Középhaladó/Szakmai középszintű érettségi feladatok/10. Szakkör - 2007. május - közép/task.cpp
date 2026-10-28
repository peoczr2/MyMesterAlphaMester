/*
Megoldás lényege:
A matematika szakkörre jelentkezők neveit egy halmazba (set) tesszük, a magyar szakkörösök neveit pedig egyesével ellenőrizzük. Ha a név szerepel a matematika-halmazban, akkor a tanuló mindkét szakkörre jelentkezett, és bekerül egy második halmazba. A set a neveket növekvő sorrendben tárolja, így a kiírás már ábécé szerinti lesz, külön rendezésre nincs szükség. Mivel a halmaz minden nevet csak egyszer tárol, a közös nevek száma a második halmaz mérete. Az időigény O((N + M) log N), ahol N és M legfeljebb 10 000, a memóriaigény O(N + M).
*/
/*
Hint 1: || Két névlista közös elemeit kell megtalálnod. Keresd meg azt az adatszerkezetet, amelyben egy név megkeresése gyorsan megy, és az egyik listát tedd bele. ||
Hint 2: || Tedd a matematikások neveit egy std::set<string>-be, majd a magyarosok listáját végigjárva minden nevet nézz meg a halmazban. A közös neveket egy másik set<string>-be gyűjtsd: a set rendezetten tárolja őket, így a kiíráshoz nem kell sort. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    set<string> math;
    for (int i = 0; i < n; i++) {
        string name;
        cin >> name;
        math.insert(name);
    }

    set<string> both;
    for (int i = 0; i < m; i++) {
        string name;
        cin >> name;
        if (math.count(name)) both.insert(name);
    }

    cout << both.size() << "\n";
    for (const string& s : both) {
        cout << s << "\n";
    }

    return 0;
}
