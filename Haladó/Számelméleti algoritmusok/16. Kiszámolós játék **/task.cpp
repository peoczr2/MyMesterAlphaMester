/*
Megoldás lényege: a gyerekeket egy vektorban tároljuk, és az aktuális kezdőpozícióból számolva minden kiesésnél
a K-adik élő gyereket vesszük ki. A kiesett gyerek helyére a következő gyerek kerül, ezért a következő számolás
ugyanarról az indexről indul, és a következő kiesett index mindig (idx + K - 1) mod méret. Az utolsó megmaradt
gyerek sorszáma a végeredmény. A törlések miatt az időigény O(N^2), ami N <= 10 000 mellett bőven belefér.
*/
/*
Hint 1: || Ez a klasszikus Josephus-szimuláció: mindig az aktuális körben a K-adik még bent lévő gyereket kell kivenni. ||
Hint 2: || Tarts egy vektort az életben maradtakról, és az idx indexet a kiesett elem helyén hagyva a következő kiesőt az `(idx + K - 1) mod méret` képlettel számold. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int k, n;
    cin >> k >> n;
    vector<int> children(n);
    iota(children.begin(), children.end(), 1);
    vector<int> eliminated;
    int idx = 0;
    while (children.size() > 1) {
        idx = (idx + k - 1) % (int)children.size();
        eliminated.push_back(children[idx]);
        children.erase(children.begin() + idx);
    }
    for (int i = 0; i < (int)eliminated.size(); ++i) {
        if (i) cout << ' ';
        cout << eliminated[i];
    }
    cout << '\n' << children[0] << '\n';
    return 0;
}
