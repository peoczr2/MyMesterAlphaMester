/*
Megoldás lényege:
A vonat teljes útja N-1 szakaszból áll, így a kiadás (N-1)·M Ft.
Egy utas minden megtett szakaszért K Ft-ot fizet, ezért a bevétel K-szorosa annak, hány utas-szakasz fordul elő összesen.
Az i. és az (i+1). állomás közötti szakaszon azok utaznak, akik az i. állomás után a vonaton vannak, így egy bejárásban a futó létszámokat összegezzük; az utolsó állomás utáni létszámhoz nincs szakasz.
Ha a kiadás szigorúan nagyobb a bevételnél, a vonat üzemeltetése veszteséges, és a program 1-et ír ki, különben 0-t.
Az összegek nagyok lehetnek, ezért 64 bites egészeket használunk. Az időigény O(N), a memóriaigény O(1).
*/
/*
Hint 1: || A két összeget kell összehasonlítani: a vonat teljes útjának költségét és az utasok által megfizetett bevételt. ||
Hint 2: || Egy szakaszon az utazók száma megegyezik az előző állomás utáni létszámmal; ezt szorozd be a személyenkénti egységárral, és összegezd az összes szakaszra. ||
Hint 3: || Az utolsó állomás után nincs szakasz, ezért ott már nem kell bevételt számolni; a vonat költsége (N-1) szakasz ára. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    long long k, m;
    cin >> n >> k >> m;

    long long cur = 0;      // a vonaton lévő utasok száma
    long long revenue = 0;  // az összes utas által megfizetett ár
    for (int i = 1; i <= n; i++) {
        long long le, fel;
        cin >> le >> fel;
        if (i < n) {
            cur += fel - le;
            revenue += k * cur;  // a következő szakaszon utazók fizetnek
        }
    }
    long long cost = m * (n - 1);  // a vonat (N-1) szakaszt tesz meg

    cout << (cost > revenue ? 1 : 0) << "\n";
    return 0;
}
