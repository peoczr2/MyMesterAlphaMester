/*
Megoldás lényege: a kimaradók számát 0-tól növeljük, és az első olyan értéknél állunk meg, amelynél a maradék tanulóból 5, 7 és 11 fős csapatok kirakhatók. Ha M a beosztott tanulók száma, a 7 fős csapatok száma kez, a 11 fősöké lab, akkor a csapatok összes száma (M - 2 * kez - 6 * lab) / 5, vagyis a nagy csapatok csökkentik a csapatszámot. Nagy N-nél a legjobb megoldásban kez legfeljebb 4 és lab legfeljebb 1, ezért kez és lab 60-ig való végigpróbálása biztosan megtalálja az optimumot. Ha több azonos csapatszámú megoldás van, a több kosárlabdacsapatot tartalmazót írjuk ki.
*/
/*
Hint 1: || Először a kimaradók számát érdemes nézni: legalább 24 tanulónál a kimaradás 0 lehet, mert 5 és 7 fős csapatokkal minden ilyen szám kirakható; kisebb N-nél az első olyan kimaradás a jó, amelynél van megoldás. ||
Hint 2: || Ha M a beosztott tanulók száma, kez a 7 fős, lab a 11 fős csapatok száma, akkor a csapatok összes száma (M - 2 * kez - 6 * lab) / 5, ezért minél kevesebb 7 és 11 fős csapat kell, annál több csapat lesz. ||
Hint 3: || Nagy N-re a legjobb megoldásban kez legfeljebb 4, lab legfeljebb 1, ezért elég ezeket 0-tól 60-ig végigpróbálni. Minden párnál ellenőrizd, hogy a maradék osztható-e 5-tel, és az első olyan kimaradásnál állj meg, ahol van megoldás. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    long long n;
    cin >> n;

    const long long KORLAT = 60;
    for (long long kimarad = 0; kimarad <= n; kimarad++) {
        long long m = n - kimarad;
        long long legjobb = -1, bestKosar = 0, bestKez = 0, bestLab = 0;
        for (long long kez = 0; kez <= KORLAT && 7 * kez <= m; kez++) {
            for (long long lab = 0; lab <= KORLAT && 7 * kez + 11 * lab <= m; lab++) {
                long long maradek = m - 7 * kez - 11 * lab;
                if (maradek % 5 != 0) continue;
                long long kosar = maradek / 5;
                long long csapat = kosar + kez + lab;
                if (csapat > legjobb || (csapat == legjobb && kosar > bestKosar)) {
                    legjobb = csapat;
                    bestKosar = kosar;
                    bestKez = kez;
                    bestLab = lab;
                }
            }
        }
        if (legjobb >= 0) {
            cout << bestKosar << " " << bestKez << " " << bestLab << " " << kimarad << "\n";
            return 0;
        }
    }
    return 0;
}
