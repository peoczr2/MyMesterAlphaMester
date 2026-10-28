/*
Megoldás lényege:
Csúszóablakot (kétmutatós bejárást) használunk a sorokon. Az ablak jobb szélét egyesével léptetjük, és fajtánként
számoljuk, hány sor esik az ablakba. Azt is nyilvántartjuk, hány fajta ért el már legalább K darabot. Ha minden
fajta teljesül, az ablak érvényes: rögzítjük a hosszát, majd a bal szélről kivesszük a sorokat, amíg az ablak
érvényes marad. Így minden sor legfeljebb kétszer kerül feldolgozásra, az időigény O(M + N), ahol M a sorok száma.
*/
/*
Hint 1: || A legrövidebb olyan szakaszt keressük, amelyben minden fajtából legalább K sor van. Ilyen szakaszokra jól működik a csúszóablak. ||
Hint 2: || Tarts fajtánként számlálót az ablakban, és külön azt is, hány fajta ért már el K darabot. Ha ez a szám N, az ablak érvényes. ||
Hint 3: || A jobb szélt léptesd előre, és amíg az ablak érvényes, rögzítsd a hosszát, majd a bal szélről vedd ki a sort. Ha a kivett sor fajtája K alá esik, a teljesülő fajták száma csökken. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int m, n, k; // a sorok száma, a szőlőfajták száma, fajtánkénti minimum
    cin >> m >> n >> k;

    vector<int> variety(m);
    for (int i = 0; i < m; i++)
        cin >> variety[i];

    vector<int> cnt(n + 1, 0); // fajtánként az ablakban lévő sorok száma
    int enough = 0;            // hány fajta van az ablakban legalább K darabbal
    int best = 0;              // a legrövidebb érvényes szakasz hossza, 0 ha nincs
    int left = 0;
    for (int right = 0; right < m; right++) {
        if (++cnt[variety[right]] == k)
            enough++;

        while (enough == n) {
            int len = right - left + 1;
            if (best == 0 || len < best)
                best = len;

            if (cnt[variety[left]] == k)
                enough--;
            cnt[variety[left]]--;
            left++;
        }
    }

    cout << best << '\n';
    return 0;
}
