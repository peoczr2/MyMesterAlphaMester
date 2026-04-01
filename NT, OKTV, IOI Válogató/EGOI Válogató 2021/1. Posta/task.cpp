/*
Megoldas: esemenyszimulacio sorral es legkozelebbi befejezesi idokkel.
Minden erkezes es befejezes idopontjaban eloszor felszabaditjuk az ugyintezoket,
majd beengedjuk a sor elejet addig, amig az elso varakozo ugyintezoje szabad.
Ekkor frissitjuk a legnagyobb vart idot es a legnagyobb sorhosszt.
*/

#include <bits/stdc++.h>
using namespace std;

struct Ember {
    int erkezes;
    int ugy;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;
    vector<int> u(k + 1);
    for (int i = 1; i <= k; ++i) cin >> u[i];

    vector<Ember> emberek(n);
    for (int i = 0; i < n; ++i) cin >> emberek[i].erkezes >> emberek[i].ugy;

    queue<Ember> sor;
    vector<char> foglalt(k + 1, 0);
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> befejezesek;

    long long legnagyobbVarakozas = 0;
    int legnagyobbSor = 0;
    int i = 0;

    auto engedheto = [&](int ugy, long long idopont) {
        return !foglalt[ugy];
    };

    while (i < n || !sor.empty() || !befejezesek.empty()) {
        long long kovErkezes = (i < n ? emberek[i].erkezes : (long long)4e18);
        long long kovBefejezes = (befejezesek.empty() ? (long long)4e18 : befejezesek.top().first);
        long long idopont = min(kovErkezes, kovBefejezes);

        while (!befejezesek.empty() && befejezesek.top().first == idopont) {
            int ugy = befejezesek.top().second;
            befejezesek.pop();
            foglalt[ugy] = 0;
        }

        while (i < n && emberek[i].erkezes == idopont) {
            sor.push(emberek[i]);
            ++i;
        }

        while (!sor.empty() && engedheto(sor.front().ugy, idopont)) {
            Ember e = sor.front();
            sor.pop();
            legnagyobbVarakozas = max(legnagyobbVarakozas, idopont - (long long)e.erkezes);
            foglalt[e.ugy] = 1;
            befejezesek.push({idopont + u[e.ugy], e.ugy});
        }

        legnagyobbSor = max(legnagyobbSor, (int)sor.size());
    }

    cout << legnagyobbVarakozas << '\n' << legnagyobbSor << '\n';
    return 0;
}