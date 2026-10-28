/*
Megoldás lényege:
Szigetenként külön nem kell foglalkozni: az összes földrengés [kezdő, vég] intervallumát egy közös listába gyűjtjük, és kezdőpont szerint rendezzük. Balról jobbra haladva nyilvántartjuk az eddig látott földrengések legkésőbbi végét (covered). Két egymást követő földrengés között a szabad percek száma: a következő kezdőpont - covered - 1, az utolsó földrengés után pedig M - covered. A válasz ezek maximuma. A rendezés miatt az időigény O(R log R), ahol R legfeljebb 100 000 földrengés.
*/
/*
Hint 1: || Az egyes szigetek külön vizsgálata nem szükséges: a földrengések időintervallumait egyetlen halmazként kell kezelni. Gyűjtsd össze az összes intervallumot, és rendezd kezdőpont szerint. ||
Hint 2: || Rendezés után haladj balról jobbra, és tartsd számon az eddig lefedett utolsó percet. Két földrengés között a szabad percek száma: (következő kezdőpont) - (lefedett utolsó perc) - 1. Az utolsó földrengés után a M és a lefedett perc különbségét is számold ki. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int k;
    long long m;
    cin >> k >> m;

    vector<pair<long long, long long>> quakes;
    for (int i = 0; i < k; i++) {
        int f;
        cin >> f;
        for (int j = 0; j < f; j++) {
            long long start, end;
            cin >> start >> end;
            quakes.push_back({start, end});
        }
    }

    sort(quakes.begin(), quakes.end());

    long long best = 0;
    long long covered = 0;
    for (auto [start, end] : quakes) {
        best = max(best, start - covered - 1);
        covered = max(covered, end);
    }
    best = max(best, m - covered);

    cout << best << "\n";
    return 0;
}
