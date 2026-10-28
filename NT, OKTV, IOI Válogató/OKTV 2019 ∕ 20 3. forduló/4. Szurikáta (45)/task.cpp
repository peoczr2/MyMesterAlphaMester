/*
Megoldás lényege:
A madár a (0, P) pontban van, az i-edik szurikáta feje (x_i, y_i). Egy balra lévő j szurikáta (x_j < x_i) takarja az i-ediket, ha a j feje a madártól az i fejéig húzott szakasz alatt nincs, vagyis a madártól a j fejéhez mutató meredekség legalább akkora, mint az i-edik meredeksége. Ezért az i. szurikáta akkor látja a madarat, ha a s_i = (y_i - P) / x_i meredekség szigorúan nagyobb minden előző s_j-nél, így a válasz az s-sorozat szigorú prefixmaximum-rekordjainak száma. Egy kukucskálás néhány magasságot változtat, ezeket módosítjuk, majd visszaállítjuk az eredeti értékeket. A meredekségeket törtként, keresztszorzással hasonlítjuk össze, így nincs pontatlanság. Szegmensfában minden csúcs tárolja a tartománya legmeredekebb elemének indexét, és azt, hány rekord van a jobb gyerekben, ha a bal gyerek maximuma a kezdőérték; ebből egy módosítás O(log^2 N), egy lekérdezés O(log N) időt igényel, az összes kukucskálás időigénye O((sum Db + Q) log^2 N).
*/
/*
Hint 1: || Az i. szurikáta akkor látja a madarat, ha a madártól hozzá húzott szakasz minden tőle balra lévő szurikáta feje alatt halad el. Ez pontosan azt jelenti, hogy a (y_i - P) / x_i meredekség szigorúan nagyobb minden tőle balra lévő szurikáta meredekségénél. ||
Hint 2: || A kérdés így: hány olyan elem van a meredekségsorozatban, amely szigorúan nagyobb minden előtte álló elemnél. Egy kukucskálásban csak kevés magasság változik, ezért érdemes a meredekségeket szegmensfában kezelned, és a változtatás után csak az érintett elemeket frissítened, nem az egész sorozatot. ||
Hint 3: || Szegmensfa minden csúcsában tárold a tartomány legmeredekebb elemének indexét, és azt, hány rekord van a jobb gyerekben, ha a bal gyerek maximuma a kezdőérték. Erre a rekordszámra rekurzív leszállással O(log N) lépésben kapsz választ, a csúcsok frissítése pedig egy módosításnál O(log^2 N). A meredekségeket törtként, keresztszorzással hasonlítsd össze. ||
*/
#include <bits/stdc++.h>
using namespace std;

int N;
long long P;
vector<long long> X, Y;  // X: a üregek helye (fix), Y: aktuális magasságok
vector<int> mxIdx;       // szegmensfa: a tartomány legmeredekebb elemének indexe
vector<int> rc;          // szegmensfa: a jobb gyerek rekordjai, ha a bal gyerek maximuma a kezdőérték

// Az i-edik meredeksége (Y[i]-P)/X[i] szigorúan nagyobb-e a j-edikénél; j = -1 a -végtelen.
bool steeper(int i, int j) {
    if (j < 0) return true;
    return (Y[i] - P) * X[j] > (Y[j] - P) * X[i];
}

// A [l, r] tartomány rekordjainak száma, ha a kezdő maximum a j-edik elem meredeksége.
int calc(int node, int l, int r, int j) {
    if (l == r) return steeper(l, j) ? 1 : 0;
    int mid = (l + r) / 2;
    int L = 2 * node, R = 2 * node + 1;
    if (!steeper(mxIdx[L], j)) return calc(R, mid + 1, r, j);
    return calc(L, l, mid, j) + rc[node];
}

void pull(int node, int l, int r) {
    int mid = (l + r) / 2;
    int L = 2 * node, R = 2 * node + 1;
    mxIdx[node] = steeper(mxIdx[L], mxIdx[R]) ? mxIdx[L] : mxIdx[R];
    rc[node] = calc(R, mid + 1, r, mxIdx[L]);
}

void build(int node, int l, int r) {
    if (l == r) {
        mxIdx[node] = l;
        return;
    }
    int mid = (l + r) / 2;
    build(2 * node, l, mid);
    build(2 * node + 1, mid + 1, r);
    pull(node, l, r);
}

void update(int node, int l, int r, int pos) {
    if (l == r) return;
    int mid = (l + r) / 2;
    if (pos <= mid)
        update(2 * node, l, mid, pos);
    else
        update(2 * node + 1, mid + 1, r, pos);
    pull(node, l, r);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int q;
    cin >> N >> P >> q;
    X.assign(N + 1, 0);
    Y.assign(N + 1, 0);
    for (int i = 1; i <= N; ++i) cin >> X[i];
    for (int i = 1; i <= N; ++i) cin >> Y[i];
    vector<long long> Y0 = Y;

    mxIdx.assign(4 * N + 4, 0);
    rc.assign(4 * N + 4, 0);
    build(1, 1, N);

    string out;
    for (int t = 0; t < q; ++t) {
        int d;
        cin >> d;
        vector<pair<int, long long>> ch(d);
        for (auto& p : ch) cin >> p.first >> p.second;

        for (auto& p : ch) {
            Y[p.first] = Y0[p.first] + p.second;
            update(1, 1, N, p.first);
        }
        int ans = calc(1, 1, N, -1);
        out += to_string(ans);
        out += (t + 1 < q) ? ' ' : '\n';

        for (auto& p : ch) {
            Y[p.first] = Y0[p.first];
            update(1, 1, N, p.first);
        }
    }
    cout << out;
    return 0;
}
