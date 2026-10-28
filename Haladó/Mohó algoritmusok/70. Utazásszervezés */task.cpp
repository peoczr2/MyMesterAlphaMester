/*
Megoldás lényege: Minden út azonos M hosszú, ezért az igények kezdőnap szerint sorban dolgozhatók fel, és egy igény akkor fogadható el, ha a kezdőnapon kevesebb mint N idegenvezető van lekötve. A lekötött idegenvezetők szabadulási napját egy prioritási sorban tartjuk, az igény előtt pedig kivesszük a már szabadultakat. Mivel minden út azonos hosszú, a kezdőnap szerinti sorrend egyben a befejezés szerinti sorrend is, így a mohó elfogadás optimális (az intervallumok k-gépes ütemezésének klasszikus esete). Az időigény O(C log N).
*/
/*
Hint 1: || Egy út az indulási naptól M napig tart, tehát egy idegenvezető ennyi ideig foglalt. ||
Hint 2: || A legkorábban felszabaduló idegenvezető nyit új helyet a következő igénynek. ||
Hint 3: || Ha egyik sem szabad, akkor az igény már nem fér be. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int guides, season, len, c;
    cin >> guides >> season >> len >> c;
    vector<int> req(c);
    for (int i = 0; i < c; ++i) cin >> req[i];

    priority_queue<int, vector<int>, greater<int>> pq;
    int ans = 0;
    for (int s : req) {
        while (!pq.empty() && pq.top() < s) pq.pop();
        if ((int)pq.size() < guides) {
            pq.push(s + len - 1);
            ++ans;
        }
    }

    cout << ans << '\n';
    return 0;
}