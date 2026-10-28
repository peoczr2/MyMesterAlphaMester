/*
Megoldás lényege:
A Hilbert-görbe minden rácspontot pontosan egyszer érint, ezért minden ponthoz egyértelmű sorszám (0-tól 4^N-1-ig) tartozik, és a pontokat ennek szerint kell sorba rendezni. A sorszámot a görbe rekurzív felépítéséből számoljuk: a legnagyobb résznégyzettől indulva minden szinten megnézzük az x és y koordináta megfelelő bitjét (rx, ry), a negyedek sorszáma (3·rx) xor ry, amit a résznégyzet területével (s·s) szorzunk és hozzáadunk az összeghez. Ha ry = 0, a következő szinten a koordinátákat fel kell cserélni, és rx = 1 esetén tükrözni is kell (a teljes méret-1 értékből kivonva), így a maradék koordinátákkal a következő szinten ugyanúgy folytatható a számítás. Mivel N ≤ 30, a sorszám legfeljebb 60 bites, így 64 bites egész elég. Az idő O(M · N + M log M).
*/
/*
Hint 1: || Nem kell a görbét rajzolni: elég minden ponthoz kiszámolni, hányadik lesz a bejárásban, és ezek szerint rendezni. ||
Hint 2: || Felülről lefelé haladj: a legnagyobb s = 2^(N-1) résznégyzettől kezdve minden szinten nézd meg az x és y koordináta s-bitjét (rx és ry). Ezekből a negyed sorszáma (3·rx) xor ry, amit s²-tel szorozva adsz hozzá a sorszámhoz. ||
Hint 3: || Ha ry = 0, a következő szinten a két koordinátát fel kell cserélni; ha rx = 1 is volt, akkor előtte mindkettőt a (2^N - 1) értékből kell kivonni. Ezután a maradék alsó biteken ugyanígy folytasd. Végül a pontokat a kapott sorszám szerint rendezd és ebben a sorrendben írd ki. ||
*/
#include <bits/stdc++.h>
using namespace std;

// A (x, y) pont sorszáma a 2^N x 2^N-es Hilbert-görbén (0-tól)
long long hilbertIndex(long long side, long long x, long long y) {
    long long d = 0;
    for (long long s = side / 2; s > 0; s /= 2) {
        long long rx = (x & s) > 0 ? 1 : 0;
        long long ry = (y & s) > 0 ? 1 : 0;
        d += s * s * ((3 * rx) ^ ry);
        if (ry == 0) {
            if (rx == 1) {
                x = side - 1 - x;
                y = side - 1 - y;
            }
            swap(x, y);
        }
    }
    return d;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;
    long long side = 1LL << N;
    vector<pair<long long, pair<long long, long long>>> pts(M);
    for (int i = 0; i < M; ++i) {
        long long x, y;
        cin >> x >> y;
        pts[i] = {hilbertIndex(side, x, y), {x, y}};
    }
    sort(pts.begin(), pts.end());

    string out;
    out.reserve((size_t)M * 24);
    for (auto &p : pts) {
        out += to_string(p.second.first);
        out += ' ';
        out += to_string(p.second.second);
        out += '\n';
    }
    cout << out;
    return 0;
}
