/*
Az A-kat elosztjuk a legnagyobb közös osztójukkal (g), és a legkisebb érmét m-mel jelöljük. Egy maradékosztályban (mod m) elég a legkisebb előállítható számot ismerni, mert onnan +m lépésekkel az összes nagyobb szám is előáll. Ezt a maradékgráfon futó Dijkstra adná, de az n*m (kb. 2*10^8) él túl lassú.
Ehelyett a számegyenest m hosszú blokkokra bontjuk (x = h*m + r), és blokkonként haladunk. Minden érme legalább m, ezért egy szám csak későbbi blokkokban hoz létre újabb számokat. Az x + c számok (minden c érmére) egyszerre jelölhetők meg: az érmék bitkészletét eltolva, 64 bitenként másoljuk a függő blokkokba.
Egy blokkban a megjelölt helyek és a még nem látott maradékok metszete adja azokat a maradékokat, amelyek itt állnak elő először: ezek legkisebb előállítható száma h*m + r, a h-t (lev[r]) eltároljuk.
Egy B-hez t = ceil(B/g) = q*m + s a redukált cél: a q. blokkban a legkisebb s-nél nem kisebb r kell, amelyre lev[r] <= q; ha nincs ilyen, (q+1)*m a válasz. Az eredményt g-vel szorozzuk.
Az előfeldolgozás kb. m*(M - m)/64 + (a blokkok száma)*m/64 szóművelet, a lekérdezések O(m) időigényűek; a legrosszabb esetben is kb. 0,04 mp (a limit 0,3 mp).
*/
/*
Hint 1: || Oszd el az összes A-t a legnagyobb közös osztóval (a végén szorozd vissza), és a legkisebb A-t (m) tekintsd modulusnak: elég maradékosztályonként az m-mel osztva ugyanazt a maradékot adó legkisebb előállítható számot ismerni, mert onnan +m lépésekkel a többi is megvan. ||
Hint 2: || Ha dist[r] ez a legkisebb szám, akkor egy x szám pontosan akkor állítható elő, ha x >= dist[x mod m]; egy B-hez tehát minden maradékosztályban a legalább B-s legkisebb jó számot kell nézni. A dist-et Dijkstra is megadja, de n*m él túl sok, ezért a számegyenest érdemes m hosszú blokkokra osztani, és a maradékokat blokkról blokkra, növekvő sorrendben véglegesíteni. ||
Hint 3: || Minden érme legalább m, ezért egy szám csak a következő blokkoktól kezdve hoz létre számokat. Tárold bitkészletben az érméket és azt, hogy mely maradékokat nem láttad még; egy új maradékból az x + c számok az érmék bitkészletének eltolásával, 64 bitenként jelölhetők meg a későbbi blokkokban. ||
*/

#include "../common.hpp"

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> a(n);
    for (int& x : a) cin >> x;
    int g = 0;
    for (int x : a) g = gcdll(g, x);
    for (int& x : a) x /= g;
    sort(a.begin(), a.end());
    a.erase(unique(a.begin(), a.end()), a.end());
    const int m = a[0], M = a.back();  // m: a legkisebb érme, M: a legnagyobb

    // coin: az érmék bitkészlete (a c. bit 1, ha c érme); load(p) a p. bittől kezdve 64 bitet ad vissza.
    vector<uint64_t> coin((M >> 6) + 2, 0);
    for (int c : a) coin[c >> 6] |= 1ULL << (c & 63);
    auto load = [&](int p) {
        int w = p >> 6, s = p & 63;
        uint64_t v = coin[w] >> s;
        if (s) v |= coin[w + 1] << (64 - s);
        return v;
    };

    // A számegyenest m hosszú blokkokra bontjuk: x = h * m + r. A pend egy gyűrű K blokkra:
    // a megfelelő bit 1, ha az adott x szám biztosan előállítható egy már végleges maradékból.
    const int W = (m + 63) / 64;  // egy blokk szavainak száma
    const int K = M / m + 3;      // ennyi blokkot kell egyszerre tárolni
    vector<uint64_t> pend((size_t)K * W, 0), unseen(W, 0);
    for (int r = 0; r < m; ++r) unseen[r >> 6] |= 1ULL << (r & 63);
    pend[0] = 1;  // az x = 0 szám a 0. blokk 0. helye
    vector<int> lev(m, 0);  // lev[r]: annak a blokknak a sorszáma, ahol az r maradék először előáll
    int found = 0;
    for (int h = 0, slot = 0; found < m; ++h, slot = (slot + 1 == K ? 0 : slot + 1)) {
        uint64_t* cur = &pend[(size_t)slot * W];
        for (int wi = 0; wi < W; ++wi) {
            uint64_t nw = cur[wi] & unseen[wi];  // ezek a maradékok most lesznek végleges
            unseen[wi] ^= nw;
            while (nw) {
                int r = wi * 64 + __builtin_ctzll(nw);
                nw &= nw - 1;
                lev[r] = h;
                ++found;
                // Az x = h*m + r szám után x + c mindegyik érmére előáll: ezeket a későbbi blokkokba
                // egyszerre, szavanként másoljuk át az érmék bitkészletéből (delta az eltolás).
                int s2 = slot;
                for (int delta = m - r; delta <= M; delta += m) {
                    if (++s2 == K) s2 = 0;
                    uint64_t* dst = &pend[(size_t)s2 * W];
                    int lo = max(0, m - delta), hi = min(m - 1, M - delta);
                    for (int w = lo >> 6; w <= (hi >> 6); ++w) dst[w] |= load(64 * w + delta);
                }
            }
        }
        fill(cur, cur + W, 0);
    }

    int q;
    cin >> q;
    for (int i = 0; i < q; ++i) {
        long long b;
        cin >> b;
        long long t = (b + g - 1) / g;  // a redukált egységben legalább t kell
        long long blk = t / m;
        int r = (int)(t % m);
        while (r < m && lev[r] > blk) ++r;  // a blk. blokk első jó helye r-től
        long long x = (r < m) ? blk * m + r : (blk + 1) * m;  // különben a következő blokk eleje
        if (i) cout << ' ';
        cout << x * g;
    }
    cout << '\n';
    return 0;
}
