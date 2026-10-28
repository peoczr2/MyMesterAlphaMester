/*
Megoldás lényege:
Egy megrendelés-halmaz akkor teljesíthető, ha minden t frekvenciára a t-nél nem kisebb frekvenciájú magok száma
legalább a t-nél nem kisebb frekvenciájú megrendelések magigényének összege (Hall-tétel, mert a megrendelések
szomszédsági halmazai egymásba ágyazottak). A számítógépeket és a megrendeléseket frekvencia szerint csökkenően
rendezzük (egyenlőségnél a számítógép kerül elébb), és ebben a sorrendben dinamikus programozást futtatunk:
dp[s] az eddigi legnagyobb nyereség, ha s mag szabad. Vásárlásnál s nő c_i-vel, a nyereség -p_i-vel változik;
elfogadott megrendelésnél s csökken C_j-vel, a nyereség V_j-vel nő. A szabad magok számát felülről a még
hátralévő összes magigény korlátozza, a többletállapotokat erre a határra vonjuk össze. Az idő O((N+M)*T),
ahol T <= 10^5 a magok összege; a legrosszabb eset kb. 2*10^8 egyszerű művelet.
*/
/*
Hint 1: || Egy megrendelés csak akkor kaphat magokat, ha a nála nem kisebb frekvenciájú magok száma elég az összes hasonló vagy nagyobb frekvenciájú igényre; így a feltétel sorrendben, egy számlálóval ellenőrizhető. ||
Hint 2: || Dinamikus programozás a szabad magok száma szerint: az állapot a szabad magok száma, az érték az eddigi legnagyobb nyereség; a többletet a még hátralévő igénnyel vond össze, hogy a táblázat mérete korlátos maradjon. ||
*/
#include <bits/stdc++.h>
using namespace std;

struct Event {
    long long freq;
    int type;       // 0: számítógép, 1: megrendelés
    int cores;      // számítógépnél a magok száma, megrendelésnél a kért magok száma
    long long val;  // számítógépnél -ár, megrendelésnél a befizetett összeg
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<Event> ev;
    ev.reserve(4000);
    for (int i = 0; i < n; ++i) {
        int c;
        long long f, v;
        cin >> c >> f >> v;
        ev.push_back({f, 0, c, -v});
    }

    int m;
    cin >> m;
    long long totalDemand = 0;
    for (int j = 0; j < m; ++j) {
        int c;
        long long f, v;
        cin >> c >> f >> v;
        ev.push_back({f, 1, c, v});
        totalDemand += c;
    }

    // frekvencia szerint csökkenően; egyenlőségnél a számítógép előre
    sort(ev.begin(), ev.end(), [](const Event &x, const Event &y) {
        if (x.freq != y.freq) return x.freq > y.freq;
        return x.type < y.type;
    });

    // nem elérhető állapot: nagy negatív szám (az eltolások kis összege nem ér el a valódi értékekig)
    const long long NEG = -(1LL << 60);
    vector<long long> dp(totalDemand + 64, NEG);
    dp[0] = 0;
    int top = 0;                 // a nem NEG állapotok felső határa
    long long rem = totalDemand; // a még fel nem dolgozott megrendelések magigénye

    for (const Event &e : ev) {
        if (e.type == 0) {
            int nt = top + e.cores;
            for (int s = nt; s >= e.cores; --s)
                dp[s] = max(dp[s], dp[s - e.cores] + e.val);
            // a hátralévő igénynél több szabad mag már felesleges: rem-re vonjuk össze
            for (int s = nt; s > rem; --s) {
                dp[rem] = max(dp[rem], dp[s]);
                dp[s] = NEG;
            }
            top = (int)min<long long>(nt, rem);
        } else {
            for (int s = 0; s + e.cores <= top; ++s)
                dp[s] = max(dp[s], dp[s + e.cores] + e.val);
            rem -= e.cores;
            for (int s = top; s > rem; --s) {
                dp[rem] = max(dp[rem], dp[s]);
                dp[s] = NEG;
            }
            top = (int)min<long long>(top, rem);
        }
    }

    cout << dp[0] << '\n';
    return 0;
}
