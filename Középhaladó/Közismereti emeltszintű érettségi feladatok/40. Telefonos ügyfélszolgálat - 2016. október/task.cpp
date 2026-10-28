/*
Megoldás lényege:
A munkatárs egyetlen vonalon dolgozik, a hívókat érkezési sorrendben szolgálja ki, ezért a hívásokat kezdési időpont szerint dolgozzuk fel egyetlen menetben. Egy hívás fogadási ideje a nyitás (8:00), a hívás kezdete és a munkatárs szabad ideje (az előző sikeres hívás vége) közül a legnagyobb. A hívás sikeres, ha a hívó a fogadás pillanatáig még vonalban van, vagyis a vége későbbi a fogadási időnél; ekkor a munkatárs szabad ideje a hívás végére ugrik. A sikertelen hívás a munkatársat nem foglalja le. A 12:00 után kezdődő hívás nem fogadható. Egy T időpontban a vonalban lévők száma a kezdés ≤ T < vége feltételt teljesítő hívások száma, ebből a most beszélgetőt le kell vonni. Az időigény O(N log N) a rendezés miatt, N ≤ 5000 mellett bőven elég.
*/
/*
Hint 1: || A munkatárs csak egy hívással tud foglalkozni, ezért minden hívás fogadási ideje a nyitás, a hívás kezdete és az előző sikeres hívás vége közül a legnagyobb. ||
Hint 2: || Egy hívás akkor sikeres, ha a vége későbbi a fogadási időpontnál. Sikertelen hívás után a munkatárs szabad ideje nem változik. ||
Hint 3: || Egy adott T időpontban a vonalban lévő hívások száma azoké, amelyekre a kezdés ≤ T < vége igaz; ebből egy hívó a beszélgetésben van, ha a fogadási idő ≤ T is teljesül. ||
*/
#include <bits/stdc++.h>
using namespace std;

struct Hivas {
    int sorszam;
    int kezd, veg;    // másodperc a nap kezdetétől
    int fogadas = -1; // a fogadás ideje, -1 ha a hívás nem volt sikeres
};

int ido(int ora, int perc, int mp) { return ora * 3600 + perc * 60 + mp; }

void kiir_ido(int t) {
    cout << t / 3600 << " " << (t / 60) % 60 << " " << t % 60;
}

int main() {
    int n;
    cin >> n;
    int to, tp, tm;
    cin >> to >> tp >> tm;
    const int T = ido(to, tp, tm);

    vector<Hivas> h(n);
    for (int i = 0; i < n; i++) {
        int a, b, c, d, e, f;
        cin >> a >> b >> c >> d >> e >> f;
        h[i].sorszam = i + 1;
        h[i].kezd = ido(a, b, c);
        h[i].veg = ido(d, e, f);
    }
    const int NYITAS = 8 * 3600, ZARAS = 12 * 3600;

    // 1. részfeladat: óránként a bejövő hívások száma (kezdés szerint)
    int orankent[24] = {0};
    for (const auto& x : h) orankent[x.kezd / 3600]++;
    cout << "#\n";
    for (int o = 0; o < 24; o++)
        if (orankent[o] > 0) cout << o << " " << orankent[o] << "\n";

    // 2. részfeladat: a leghosszabb hívás (sikeres vagy nem), a legkorábbi a döntetlennél
    int legi = 0, legh = -1;
    for (const auto& x : h) {
        int hossz = x.veg - x.kezd;
        if (hossz > legh || (hossz == legh && x.sorszam < legi)) {
            legh = hossz;
            legi = x.sorszam;
        }
    }
    cout << "#\n" << legi << " " << legh << "\n";

    // 3-5. részfeladat: a munkatárs szimulációja a kezdési sorrendben
    vector<int> sorrend(n);
    for (int i = 0; i < n; i++) sorrend[i] = i;
    stable_sort(sorrend.begin(), sorrend.end(),
                [&](int a, int b) { return h[a].kezd < h[b].kezd; });

    int szabad = NYITAS;  // mikortól áll rendelkezésre a munkatárs
    int utolso = -1;      // az utoljára fogadott hívás indexe
    for (int i : sorrend) {
        if (h[i].kezd >= ZARAS) continue;  // 12:00 után érkezett, nem fogadható
        int fogadas = max(szabad, max(h[i].kezd, NYITAS));
        if (h[i].veg > fogadas) {          // a hívó még vonalban van, amikor sorra kerül
            h[i].fogadas = fogadas;
            szabad = h[i].veg;
            utolso = i;
        }
    }

    // 3. részfeladat: a T időpontban beszélgető hívó és a várakozók száma
    int vonalban = 0, beszelgeto = -1;
    for (const auto& x : h) {
        if (x.kezd <= T && T < x.veg) vonalban++;
        if (x.fogadas != -1 && x.fogadas <= T && T < x.veg) beszelgeto = x.sorszam;
    }
    cout << "#\n";
    if (beszelgeto == -1) cout << "Nem\n";
    else cout << beszelgeto << " " << vonalban - 1 << "\n";

    // 4. részfeladat: az utoljára fogadott hívó sorszáma és várakozási ideje
    cout << "#\n";
    if (utolso == -1) cout << "Nem\n";
    else cout << h[utolso].sorszam << " " << h[utolso].fogadas - h[utolso].kezd << "\n";

    // 5. részfeladat: a sikeres hívások adatai sorszám szerint
    cout << "#\n";
    for (const auto& x : h) {
        if (x.fogadas == -1) continue;
        cout << x.sorszam << " ";
        kiir_ido(x.fogadas);
        cout << " ";
        kiir_ido(x.veg);
        cout << "\n";
    }
    return 0;
}
