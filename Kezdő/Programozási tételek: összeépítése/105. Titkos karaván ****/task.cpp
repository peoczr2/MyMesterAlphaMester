/*
Megoldás lényege:
Ha a karaván d-edik napon indul, az i-edik oázisban (i >= 2) az éjszakája d + T_i, ahol T_i a 2. és az i-edik oázis közötti utak idejének összege, plusz az ezt megelőző oázisokban töltött éjszakák száma (i-2). Így nem kell minden indulási napot külön szimulálni: a T_i eltolások egyszer kiszámolhatók. Minden foglalt S napra az S - T_i indulási nap ütközést okozna ebben az oázisban, ezért ezeket a napokat egy logikai tömbben megjelöljük. A válasz az első (1-től induló) nem megjelölt nap. Mivel az indulási nap legfeljebb 100000 lehet, a tömb mérete ennek megfelelően elég, és a futási idő a bemenet méretével arányos.
*/
/*
Hint 1: || Ha a karaván d-edik napon indul, a j-edik oázisbeli éjszakája d-hez képest mindig ugyanannyival később van. Nem kell minden indulási napot külön szimulálni, elég az oázisonkénti eltolást kiszámolni. ||
Hint 2: || Az eltolás a 2. oázistól a j-edik oázisig tartó utak idejének összege, plusz az előtte lévő 2. és (j-1). oázisban töltött éjszakák száma. Egy foglalt S napból így visszaszámolható, melyik indulási napon lenne ütközés ebben az oázisban. ||
Hint 3: || Jelöld egy logikai tömbben a tiltott indulási napokat, majd az első olyan napot keresd 1-től, amely nincs megjelölve. A tömb mérete legyen elég nagy a legfeljebb 100000-es foglalt napokhoz. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    const int MAXNAP = 100000;

    int n;
    cin >> n;

    vector<long long> ido(n + 1, 0);
    for (int i = 2; i <= n; ++i) cin >> ido[i];

    vector<char> tiltott(MAXNAP + 2, 0);   // tiltott[d]: a d-edik napon induló karaván ütközne
    long long eltolas = 0;                  // az i-edik oázis éjszakája: d + eltolas
    for (int i = 2; i <= n; ++i) {
        eltolas += ido[i] + (i > 2 ? 1 : 0);

        int k;
        cin >> k;
        for (int j = 0; j < k; ++j) {
            long long s;
            cin >> s;
            long long d = s - eltolas;
            if (d >= 1 && d <= MAXNAP) tiltott[d] = 1;
        }
    }

    long long d = 1;
    while (d <= MAXNAP && tiltott[d]) ++d;
    cout << d << '\n';
    return 0;
}
