/*
Megoldás lényege:
Az előadásokat befejezési idő szerint növekvő sorrendben dolgozzuk fel, és minden előadást olyan teremnek adunk, amelyben az utolsó előadás már befejeződött az új kezdés előtt. Ha mindkét terem megfelel, azt választjuk, amelyik később szabadult fel, így a korábban szabaduló terem szabad ideje megmarad a későbbi előadásoknak. Ha egyik terem sem szabad, az előadást kihagyjuk. Ez a mohó választás maximális számú előadást ad, és mivel a feldolgozás befejezési idő szerint halad, a termekben az előadások időrendben követik egymást. Két teremnél elég két utolsó befejezési időt nyilvántartani, az időigény O(N log N).
*/
/*
Hint 1: || A legkorábban befejeződő előadások hagyják meg a legtöbb lehetőséget a többi előadásnak, ezért ezekkel érdemes kezdeni. ||
Hint 2: || Egy előadás egy terembe csak akkor mehet, ha a kezdési ideje nagyobb a teremben lévő utolsó előadás befejezési idejénél. ||
Hint 3: || Ha mindkét terem szabad, a később felszabaduló (nagyobb befejezési idejű) terem kapja az előadást, így a másik terem korábbi szabadsága megmarad. ||
*/

#include <bits/stdc++.h>
using namespace std;

struct Event {
    int s, e, id;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<Event> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i].s >> a[i].e;
        a[i].id = i + 1;
    }
    sort(a.begin(), a.end(), [](const Event &x, const Event &y) {
        if (x.e != y.e) return x.e < y.e;
        if (x.s != y.s) return x.s < y.s;
        return x.id < y.id;
    });

    int endA = 0, endB = 0;
    vector<int> roomA, roomB;
    for (const auto &ev : a) {
        bool fitA = ev.s > endA, fitB = ev.s > endB;
        // a szabad termek közül azt választjuk, amelyik később szabadult fel
        if (fitA && (!fitB || endA >= endB)) {
            endA = ev.e;
            roomA.push_back(ev.id);
        } else if (fitB) {
            endB = ev.e;
            roomB.push_back(ev.id);
        }
    }

    cout << roomA.size() << ' ' << roomB.size() << '\n';
    for (int i = 0; i < (int)roomA.size(); ++i) {
        if (i) cout << ' ';
        cout << roomA[i];
    }
    cout << '\n';
    for (int i = 0; i < (int)roomB.size(); ++i) {
        if (i) cout << ' ';
        cout << roomB[i];
    }
    cout << '\n';
    return 0;
}