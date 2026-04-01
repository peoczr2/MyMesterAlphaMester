/*
Feladat: A lehető legtöbb utazási igényt kell kielégíteni, ha egyszerre N idegenvezető áll rendelkezésre.
Ötlet: Azonos hosszúságú utakról van szó; az igényeket a kezdőnap szerint sorban nézzük, és mindig a legkorábban felszabaduló idegenvezetőt használjuk. Ha mind foglalt, az adott igényt kihagyjuk.
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