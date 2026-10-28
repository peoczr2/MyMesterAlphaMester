/*
Megoldás lényege:
Mindenki pontosan egy másiknak továbbítja a hírt, így minden tanulóból pontosan egy él indul. Ez egy függvénygráf: a hír útja vagy körbe ér, vagy egy fa-ágon végződik.
Egy tanuló pontosan akkor kapja vissza a saját hírét, ha a csúcsa egy körön van.
A körön nem lévő csúcsokat úgy szedjük le, hogy a bejövő fokszámmal 0 csúcsokat töröljük, és a törléssel a rákövetkező csúcs bejövő fokszámát csökkentjük. Ha az is 0 lesz, azt is töröljük.
A megmaradt csúcsok pontosan a körök csúcsai, ezeket növekvő sorrendben írjuk ki.
Időigény: O(N), ami N ≤ 100000 esetén gyors.
*/
/*
Hint 1: || Minden tanulóhoz pontosan egy kimenő él tartozik, így a hír útja vagy visszatér a kiindulásig, vagy egy már korábban érintett tanulónál körbe fut. Melyik tanulók vannak körben? ||
Hint 2: || Számold ki minden tanulóra, hányan továbbítanak neki hírt (bejövő fok). A bejövő fok 0 csúcs nem lehet körben, ezért eltávolíthatod, és ezzel a rákövetkező csúcs bejövő fokát is csökkentheted. ||
Hint 3: || Ha a törlés után egy csúcs bejövő foka 0 lett, azt is törölheted, sorba állítással, mint egy szélességi bejárásnál. A végén a meg nem törölt tanulók pontosan azok, akik visszakapják a saját hírüket. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> to(n + 1), indeg(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        cin >> to[i];
        indeg[to[i]]++;
    }

    // A bejövő fok 0 csúcsok nem lehetnek körön, ezeket töröljük
    queue<int> q;
    for (int i = 1; i <= n; i++)
        if (indeg[i] == 0)
            q.push(i);

    vector<bool> removed(n + 1, false);
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        removed[v] = true;
        if (--indeg[to[v]] == 0)
            q.push(to[v]);
    }

    vector<int> ans;
    for (int i = 1; i <= n; i++)
        if (!removed[i])
            ans.push_back(i);

    cout << ans.size() << "\n";
    for (size_t i = 0; i < ans.size(); i++) {
        if (i)
            cout << ' ';
        cout << ans[i];
    }
    cout << "\n";
    return 0;
}
