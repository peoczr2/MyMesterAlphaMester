/*
Megoldási ötlet:
Az olcsó, 1 energiás törlések miatt a végső megoldás mindig három részre bontható:
1. az első kódból eldobunk egy prefixet olcsón, és a második kód elejére szükség esetén betűket szúrunk be;
2. utána következik egy valódi középső blokk, ahol már csak a szokásos edit-distance műveletek élnek
    2-es beszúrási és törlési árral, illetve a körkörös ábécetávolság szerinti átalakítási árral;
3. végül az első kód megmaradt suffixét olcsón eldobjuk, és a második kód végére még beszúrjuk a hiányzó betűket.

Fontos, hogy a középső blokk elejét és végét is valódi összepárosítás horgonyozza le. Ha a blokk elején vagy
végén csak beszúrás vagy törlés állna, azt olcsóbban át lehetne tolni az első vagy a harmadik részbe. Emiatt
elég azt vezetni, hogy egy középső blokkot milyen minimális áron tudunk felépíteni úgy, hogy az s[i-1] és t[j-1]
betűk össze vannak párosítva, tehát a blokk itt biztosan "értelmesen" végződik.

Legyen dp[j] az a legkisebb költség az aktuális i sorban, amellyel valamely középső blokk s[...i) és t[...j)
prefixei között már felépült. Ebből a blokkból az aktuális (i,j) helyen egy parositas érték képződik:
- vagy egy korábbi blokkot folytatunk, és az új két betűt egymásnak feleltetjük meg;
- vagy belülről törlések/beszúrások után jutunk ide;
- vagy itt indul a középső blokk, ekkor a korábbi ár egyszerűen (i-1) + 2*(j-1).

Ha egy blokk s[i-1] és t[j-1] párral végződik, akkor azonnal teljes megoldást kapunk: a hátralévő m-i darab
betű olcsó suffix-törlés, a hátralévő n-j darab betű pedig 2-es áru beszúrás. Így minden cellában frissíthető
a válasz. Az időigény O(M*N), a memóriaigény O(N).
*/
/*
Hint 1: || Az optimális megoldásban a középső "drága" rész két végét mindig egy-egy valódi betűpár rögzíti. ||
Hint 2: || Ha a középső blokk elején csak törlés vagy beszúrás állna, azt át lehetne tolni az olcsó prefix/suffix részbe. ||
Hint 3: || Érdemes azt tárolni, hogy egy középső blokk minimális költsége mennyi, ha az aktuális két betű biztosan össze van párosítva. ||
Hint 4: || Egy lezárt középső blokk után a maradék költség már közvetlenül kiszámolható: olcsó suffix-törlés plusz 2-es áru suffix-beszúrás. ||
*/

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int atalakitasi_ar(char bal, char jobb) {
    int kulonbseg = abs(bal - jobb);
    return min(kulonbseg, 26 - kulonbseg);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int m, n;
    string s, t;
    cin >> m >> s >> n >> t;

    const int VEGTELEN = 1'000'000'000;

    vector<int> elozo(n + 1, VEGTELEN);
    int valasz = m + 2 * n;

    for (int i = 1; i <= m; ++i) {
        vector<int> aktualis(n + 1, VEGTELEN);

        for (int j = 1; j <= n; ++j) {
            int ar = atalakitasi_ar(s[i - 1], t[j - 1]);

            int parositas = min(elozo[j - 1], (i - 1) + 2 * (j - 1)) + ar;
            aktualis[j] = min({
                parositas,
                elozo[j] + 2,
                aktualis[j - 1] + 2
            });

            valasz = min(valasz, parositas + (m - i) + 2 * (n - j));
        }

        swap(elozo, aktualis);
    }

    cout << valasz << '\n';
    return 0;
}