/*
Megoldás lényege:
Minden naphoz az őt megelőző K nap (önmagát is beleértve) legmelegebb értékét csúszóablak-maximumként számoljuk.
Egy deque-ben az indexeket tároljuk úgy, hogy a hozzájuk tartozó hőmérsékletek csökkenő sorrendben legyenek: új nap érkezésekor hátulról kidobjuk azokat, amelyek nem melegebbek az újnál, majd elölről kidobjuk azokat, amelyek már kiestek a K hosszú ablakból.
Az elöl álló index hőmérséklete adja a választ, így minden index legfeljebb egyszer kerül be és ki a deque-ből.
Az időigény O(N), a memóriaigény O(N).
*/
/*
Hint 1: || Ha minden naphoz külön visszanéznél K napot, az N * K lépés (akár 10^9) túl sok lenne. Az ablak minden lépésben csak egy elemmel tolódik, ezért elég az ablakba került új elemmel frissíteni a maximumot. ||
Hint 2: || Tarts egy deque-et indexekkel, amelyekhez tartozó hőmérsékletek csökkenő sorrendben vannak. Új nap érkezésekor hátulról dobd ki azokat, amelyek nem melegebbek az újnál; elölről pedig azokat, amelyek indexe már nem esik a K napos ablakba. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;
    vector<int> h(n);
    for (int &x : h) cin >> x;

    deque<int> dq; // indexek, a hozzájuk tartozó hőmérsékletek csökkenőek
    for (int i = 0; i < n; i++) {
        while (!dq.empty() && h[dq.back()] <= h[i]) dq.pop_back();
        dq.push_back(i);
        while (dq.front() <= i - k) dq.pop_front();
        cout << h[dq.front()] << '\n';
    }
    return 0;
}
