/*
Megoldás lényege:
A keresett időszak olyan folytonos napszakasz, amelyben minden nap más városban van, tehát nincs benne két egyforma városszám. Csúszóablakkal dolgozunk: a jobb végpontot napról napra léptetjük, és minden városhoz eltároljuk az utolsó előfordulásának napját. Ha az aktuális város az ablakon belül már előfordult, a bal végpontot az előző előfordulás utáni napra toljuk, így minden nap legfeljebb egyszer lép be és ki az ablakból. Az időigény O(N), a memóriaigény a városok számával arányos.
*/
/*
Hint 1: || Keresd a leghosszabb olyan szakaszt, amelyben minden elem különböző. Ha egy szakasz jó, a része is jó, ezért a jobb végpontot egyesével haladva elég a bal végpontot megfelelően mozgatni, nem kell minden részszakaszt külön ellenőrizni. ||
Hint 2: || Minden városszámhoz tárold az utolsó előfordulásának sorszámát. Ha egy város már szerepel az aktuális szakaszban, a bal végpontot az előző előfordulás utáni napra kell tolni; ha az előző előfordulás a szakaszon kívül esik, a bal végpont nem változik. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> city(n);
    for (int &c : city) cin >> c;

    // last[c]: a c város utolsó előfordulásának indexe (0-tól), -1 ha még nem volt
    vector<int> last(n + 1, -1);
    int left = 0, best = 0;
    for (int right = 0; right < n; right++) {
        int c = city[right];
        if (last[c] >= left) left = last[c] + 1;
        last[c] = right;
        best = max(best, right - left + 1);
    }
    cout << best << '\n';
    return 0;
}
