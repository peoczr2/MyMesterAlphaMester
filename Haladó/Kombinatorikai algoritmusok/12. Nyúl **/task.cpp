/*
   Nyúl: korosztályonkénti szimuláció. Minden évben a szaporodó korú
   nyulak utódainak számát összegyűjtjük, majd az életkorokat eltoljuk.
   Az állapot az egyes korosztályok létszáma. Egy év alatt az újszülöttek
   száma a K..L éves nyulak létszámának és a hozzájuk tartozó R_i értékek
   szorzatainak összege; utána minden korosztály eggyel idősebb lesz, az L
   évesek pedig kiesnek. Mivel csak összeadás és szorzás szerepel, a MOD
   minden lépésben alkalmazható, így a számok nem csordulnak túl. Az idő
   O(N * L), ami N <= 100 és L <= 10 mellett bőven belefér.
*/
/*
Hint 1: || Az állapot elég: egy tömb, amely korosztályonként megadja a nyulak számát (1..L). Egy évnyi lépés: először az újszülöttek számát számold ki, utána léptesd a korosztályokat. ||
Hint 2: || Az újszülöttek száma a K-tól L-ig terjedő korosztályokra összegzett cnt[i] * R[i] szorzatok összege. Mivel csak szorzás és összeadás van, a MOD bármikor alkalmazható. ||
Hint 3: || A léptetésnél a régi cnt[i-1] érték kerül cnt[i]-be, az 1 éves nyulak száma pedig az újszülöttek száma. Ezt a tömbben visszafelé, az L-től a 2-ig haladva érdemes végrehajtani, hogy ne írjuk felül a még szükséges értéket. ||
*/
#include <bits/stdc++.h>
using namespace std;

static const int MOD = 1000000;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, L, K;
    cin >> N >> L >> K;
    vector<int> cnt(L + 1, 0), birth(L + 1, 0);
    for (int i = 1; i <= L; ++i) {
        cin >> cnt[i];
        if (i >= K) cin >> birth[i];
    }

    for (int year = 0; year < N; ++year) {
        long long newborn = 0;
        for (int age = K; age <= L; ++age) {
            newborn = (newborn + 1LL * cnt[age] * birth[age]) % MOD;
        }
        for (int age = L; age >= 2; --age) cnt[age] = cnt[age - 1];
        cnt[1] = (int)newborn;
    }

    int ans = 0;
    for (int age = 1; age <= L; ++age) ans = (ans + cnt[age]) % MOD;
    cout << ans << '\n';
    return 0;
}