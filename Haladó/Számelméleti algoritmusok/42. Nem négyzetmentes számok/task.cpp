/*
Egy szám akkor nem négyzetmentes, ha osztható valamely p^2 számmal (p >= 2). Ezért Eratoszthenész szitájához hasonlóan, minden p-re megjelöljük a p^2 összes többszörösét egy L méretű táblán, majd a megjelölt számokat sorban megszámoljuk: az N-edik megjelölt szám a válasz.
A nem négyzetmentes számok sűrűsége kb. 1 - 6/pi^2 = 0,39, ezért az N-edik szám durván 2,55 * N; az L = 3N + 100 határ általában elég, ha mégsem, megduplázzuk és újrakezdjük.
Egy p-re L/p^2 jelölés történik, összesen kb. 0,65 * L lépés: N = 100 000 esetén néhány százezer művelet, vagyis ezredmásodpercek alatt lefut, szemben a számonkénti próbaosztással.
*/
/*
Hint 1: || A keresett számok pontosan azok, amelyeket valamelyik p^2 (p >= 2) osztja; ezek a p^2 többszörösei, tehát nem kell minden számról külön eldönteni az osztást, elég a többszöröseket megjelölni. ||
Hint 2: || Vegyél egy L = 3N + 100 elemű logikai tömböt, és minden p-re (p * p <= L) jelöld meg a p*p, 2*p*p, 3*p*p, ... helyeket. Ezután számold a megjelölt helyeket 1-től felfelé; az N-edik megjelölt index a válasz. Ha L kevés volt (nincs N jelölt), duplázd az L-t. ||
*/

#include "../common.hpp"

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    for (long long limit = 3LL * n + 100;; limit *= 2) {
        vector<char> bad(limit + 1, 0);
        for (long long p = 2; p * p <= limit; ++p) {
            for (long long j = p * p; j <= limit; j += p * p) bad[j] = 1;
        }
        int count = 0;
        for (long long x = 1; x <= limit; ++x) {
            if (bad[x] && ++count == n) {
                cout << x << '\n';
                return 0;
            }
        }
    }
}
