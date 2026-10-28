/*
Tükörszó kezdőszelete betűk törlésével
Feladat: S leghosszabb olyan kezdőszelete, amely legfeljebb K betű törlésével tükörszóvá tehető.

Megoldás: legyen dp[l][r] az S[l..r] tükörszóvá tételéhez szükséges minimális törlésszám:
ha S[l] = S[r], akkor dp[l+1][r-1], különben 1 + min(dp[l+1][r], dp[l][r-1]).
A kezdőszeletek a dp[0][r] értékek, ezeket hossz szerint növekvő kitöltés közben rögzítjük:
a leghosszabb r+1 hossz, amelyre dp[0][r] <= K.
A teljes N x N tábla nem fér bele a 16 MB-ba, de egy hosszhoz csak az eggyel és a kettővel
rövidebb szakaszok értékei kellenek, ezért elég három, a bal végponttal indexelt sor.
Idő: O(N^2) (N = 10 000 mellett kb. 5*10^7 lépés), memória: O(N).
*/
/*
Hint 1: || Egy rögzített szóra a minimális törlésszám klasszikus intervallum-DP: nézd a két szélső betűt, és ha nem egyeznek, az egyiket törölni kell. ||
Hint 2: || dp[l][r] = az S[l..r] tükörszóvá tételéhez szükséges törlések száma. Az összes kezdőszeletre egyszerre megkapod a választ: ezek éppen a dp[0][r] értékek. ||
Hint 3: || Hossz szerint növekvően töltve dp[l][r] csak az eggyel és kettővel rövidebb szakaszokat használja, így három, l-lel indexelt tömb elég (O(N) memória, O(N^2) idő). A válasz a legnagyobb hossz, amelyre dp[0][hossz-1] ≤ K. ||
*/

#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // beolvasás (K-ra nincs felső korlát megadva, ezért long long)
    long long K;
    string S;
    cin >> K >> S;
    int n = S.size();

    // ketto[l] = dp[l][l+hossz-3], egy[l] = dp[l][l+hossz-2], most[l] = dp[l][l+hossz-1]
    // kezdetben: 0 hosszú és 1 hosszú szakaszok, mindkettő tükörszó (0 törlés)
    vector<int> ketto(n + 1, 0), egy(n + 1, 0), most(n + 1, 0);

    int valasz = (n > 0 ? 1 : 0);   // az egybetűs kezdőszelet mindig jó
    for (int hossz = 2; hossz <= n; ++hossz) {
        for (int l = 0; l + hossz - 1 < n; ++l) {
            int r = l + hossz - 1;
            if (S[l] == S[r])
                most[l] = ketto[l + 1];                  // dp[l+1][r-1]
            else
                most[l] = 1 + min(egy[l + 1], egy[l]);   // dp[l+1][r], dp[l][r-1]
        }
        if (most[0] <= K) valasz = hossz;                // az S[0..hossz-1] kezdőszelet
        // továbblépés a következő hosszra
        swap(ketto, egy);
        swap(egy, most);
    }

    cout << valasz << '\n';
    return 0;
}
