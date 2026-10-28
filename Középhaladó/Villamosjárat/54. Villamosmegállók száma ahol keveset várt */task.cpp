/*
Megoldás lényege:
Egy megállónál a várakozás az indulási és az érkezési idő különbsége, a villamos pedig akkor állt meg, ha ez a különbség pozitív. A feltétel tehát két részből áll: a várakozás pozitív és kisebb K-nál. A megállókat egyszer, sorban olvassuk be, és a számlálót növeljük, ha a feltétel teljesül. A 0. állomás nincs a bemenetben, a végállomás (N.) pedig nem számít bele, ezért az N-edik megállót nem számoljuk. Az időigény O(N).
*/
/*
Hint 1: || A várakozási idő az indulási idő mínusz az érkezési idő. Két feltételt kell egyszerre teljesíteni: a különbség legyen pozitív, vagyis a villamos álljon meg, és legyen K-nál kisebb. ||
Hint 2: || Az első sorban az N és a K érkezik, utána a megállók. Minden sorra számold ki a várakozást, és csak az 1-től N-1-ig tartó sorszámú megállókat számold a feltétel szerint. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;

    int count = 0;
    for (int i = 1; i <= n; i++) {
        int dist, arr, dep;
        cin >> dist >> arr >> dep;
        int wait = dep - arr;
        if (i < n && wait > 0 && wait < k) {
            count++;
        }
    }

    cout << count << '\n';
    return 0;
}
