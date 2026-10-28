/*
Megoldás lényege:
Az állapot a korosztályonkénti rókaszám-vektor: egy év alatt minden róka eggyel idősebb lesz, az L éves rókák pedig ekkor elpusztulnak, ezért a vektort egy pozícióval jobbra toljuk. Az újszülöttek száma ebben az évben a szaporodó korú (K-tól L-ig terjedő) rókák összege, ezt az 1 éves korosztály kapja. Ezt a lépést N-szer végrehajtjuk, a válasz pedig az összes korosztály összege az utolsó év után. Egy év O(L) munka, így a teljes futás O(N·L), ami a korlátok mellett elenyésző. A számokat minden lépésben MOD szerint tartjuk, így az összegzés sosem csordul túl.
*/
/*
Hint 1: || Elég a korosztályonkénti darabszámokat nyilvántartani: egy év alatt minden korosztály eggyel feljebb lép, az újszülöttek száma pedig a szaporodó korú rókák összege. ||
Hint 2: || Tárolj egy tömböt az életkor szerint, és évente idősebbtől a fiatalabb felé haladva másold át az értékeket (cnt[kor] = cnt[kor-1]); az L éves rókák így automatikusan kihalnak. ||
*/
#include <bits/stdc++.h>
using namespace std;

static const int MOD = 1000000;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, L, K;
    cin >> N >> L >> K;
    vector<int> cnt(L + 1, 0);
    for (int i = 1; i <= L; ++i) cin >> cnt[i];

    for (int year = 0; year < N; ++year) {
        long long newborn = 0;
        for (int age = K; age <= L; ++age) newborn = (newborn + cnt[age]) % MOD;
        for (int age = L; age >= 2; --age) cnt[age] = cnt[age - 1];
        cnt[1] = (int)newborn;
    }

    int ans = 0;
    for (int age = 1; age <= L; ++age) ans = (ans + cnt[age]) % MOD;
    cout << ans << '\n';
    return 0;
}
