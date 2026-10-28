/*
Megoldás lényege:
Ha az első számjegy d, akkor minden további számjegy d plusz a kód addigi jeleinek összege, vagyis a kódból egy p_i prefixösszeg-sorozat állítható elő, és az i. számjegy d + p_i. Így az összes lehetséges szám csak d értékében tér el. A d-re az a feltétel, hogy minden számjegy 0 és 9 közé essen, és d ne legyen 0, mert akkor a szám nem N+1 jegyű. A legkisebb d = max(1, −min p), a legnagyobb d = min(9, 9 − max p), és mivel a számjegyek d-vel együtt nőnek, ezekből adódik a legkisebb, illetve a legnagyobb szám. Az időigény O(N).
*/
/*
Hint 1: || Az első számjegy határozza meg az egész számot: a többi számjegy mindig az elsőhöz képest tolódik a kód jelei szerint. Érdemes ezért először a jelekből kiszámolni, mennyivel tér el minden pozíció az elsőtől. ||
Hint 2: || Az első számjegy egy szabad paraméter, amelynek értékét úgy kell megválasztani, hogy minden számjegy 0 és 9 között maradjon, és az első számjegy ne legyen 0. A legkisebb szám a legkisebb, a legnagyobb a legnagyobb megengedett első számjegyből adódik. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    string kod;
    cin >> n >> kod;

    // p[i]: az i. számjegy eltérése az első számjegytől
    vector<int> p(n + 1, 0);
    for (int i = 0; i < n; i++)
        p[i + 1] = p[i] + (kod[i] == '+' ? 1 : -1);

    int minP = *min_element(p.begin(), p.end());
    int maxP = *max_element(p.begin(), p.end());

    // az első számjegy megengedett legkisebb és legnagyobb értéke (N+1 jegyű szám: nem lehet 0)
    int legkisebbElso = max(1, -minP);
    int legnagyobbElso = min(9, 9 - maxP);

    string kisebb, nagyobb;
    for (int i = 0; i <= n; i++) {
        kisebb += char('0' + legkisebbElso + p[i]);
        nagyobb += char('0' + legnagyobbElso + p[i]);
    }
    cout << kisebb << "\n" << nagyobb << "\n";
    return 0;
}
