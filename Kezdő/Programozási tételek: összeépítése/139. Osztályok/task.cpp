/*
Megoldás lényege:
Két képpont pontosan akkor kerül egy osztályba, ha fényességük különbsége legfeljebb 1, ezért az osztályok a képen előforduló fényességértékek egymást követő, összefüggő szakaszai. Az összevonás d-nél azokat a határokat szünteti meg, ahol a két szomszédos osztály közötti rés legfeljebb d, így d-nél az osztályok száma 1 + (d-nél nagyobb rések száma). A legkisebb olyan d, amellyel az osztályok száma legfeljebb K, a rések csökkenő sorrendjében a K-adik legnagyobb rés. Ha az osztályok száma eleve legfeljebb K, a válasz 0. Az idő a képpontok számával arányos (legfeljebb 100 000), plusz a rések rendezése.
*/
/*
Hint 1: || Vedd észre, hogy két osztály között csak akkor van rés, ha két egymás utáni előforduló fényességérték különbsége legalább 2. Először azt érdemes megállapítani, mely értékek fordulnak elő egyáltalán. ||
Hint 2: || Az előforduló értékeket növekvő sorrendben bejárva az egymást követő értékek egy osztályt alkotnak. Két szomszédos osztály közötti rés az második osztály legkisebb és az első osztály legnagyobb értékének különbsége. ||
Hint 3: || Gondold végig: d-nél az osztályok száma 1 + (d-nél nagyobb rések száma). Melyik d az legkisebb, amelyre ez K-nál nem több? Rendezd a réseket csökkenő sorrendbe. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    const int MAXV = 100000;
    int n, m, k;
    cin >> n >> m >> k;

    vector<bool> van(MAXV + 1, false);
    for (int i = 0; i < n * m; i++) {
        int f;
        cin >> f;
        van[f] = true;
    }

    // Az osztályok: az előforduló értékek összefüggő szakaszai.
    vector<int> eleje, vege;
    for (int v = 1; v <= MAXV; v++) {
        if (!van[v]) continue;
        if (!vege.empty() && vege.back() + 1 == v) {
            vege.back() = v;
        } else {
            eleje.push_back(v);
            vege.push_back(v);
        }
    }

    int osztalyok = eleje.size();
    if (osztalyok <= k) {
        cout << 0 << "\n";
        return 0;
    }

    // Két szomszédos osztály közötti rések.
    vector<int> resek;
    for (int i = 0; i + 1 < osztalyok; i++) {
        resek.push_back(eleje[i + 1] - vege[i]);
    }
    sort(resek.begin(), resek.end(), greater<int>());

    cout << resek[k - 1] << "\n";
    return 0;
}
