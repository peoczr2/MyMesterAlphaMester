/*
Megoldás lényege:
Egy megállónál a várakozás az indulási és az érkezési idő különbsége, de ez csak akkor értelmes, ha a villamos ténylegesen megállt, vagyis az érkezési idő kisebb az indulásinál. Azok a megállók, ahol nem állt meg, kimaradnak akkor is, ha a nulla várakozás kisebb K-nál. Egy bejárásban gyűjtjük a feltételnek megfelelő sorszámokat növekvő sorrendben, majd kiírjuk a darabszámot, utána a sorszámokat egy sorban. Az időigény O(N).
*/
/*
Hint 1: || Egy megállón a várakozás az indulási és az érkezési idő különbsége, de csak akkor, ha az érkezési idő kisebb az indulásinál, mert különben a villamos nem állt meg. ||
Hint 2: || Egy menetben olvasd be a megállókat, és a sorszámot tedd egy vektorba, ha megálltak és a várakozás kisebb K-nál. A végén írd ki a vektor méretét, majd az elemeit. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;

    vector<int> ids;
    for (int i = 1; i <= n; i++) {
        int dist, arr, dep;
        cin >> dist >> arr >> dep;
        if (arr < dep && dep - arr < k) {
            ids.push_back(i);
        }
    }

    cout << ids.size();
    for (int id : ids) {
        cout << ' ' << id;
    }
    cout << '\n';
    return 0;
}
