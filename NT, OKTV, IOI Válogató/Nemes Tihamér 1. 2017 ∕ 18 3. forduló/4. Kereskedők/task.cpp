/*
Megoldás lényege:
Mindkét kereskedő gyümölcseit egy-egy std::set-be tesszük: így az ismétlődések egyszer szerepelnek, a halmaz pedig ábécé szerint rendezett marad.
A kérdés a szimmetrikus különbség: az a gyümölcs kell, amely csak az egyik halmazban szerepel. Ezt úgy kapjuk meg, hogy mindkét halmaz elemein végigmegyünk, és a másik halmazban nem szereplőket egy harmadik halmazba tesszük.
A harmadik halmaz bejárása már a kívánt sorrendet adja, a darabszám pedig a halmaz mérete.
Az időigény O((N + M) · log(N + M)) összehasonlítás, ami N, M ≤ 1000 esetén bőven belefér.
*/
/*
Hint 1: || Egy gyümölcs akkor kerül a kimenetbe, ha csak az egyik kereskedőnél kapható. Mivel a bemenetben egy név többször is előfordulhat, az ismétléseket ki kell szűrni. ||
Hint 2: || Tárold mindkét kereskedő neveit egy-egy std::set-ben, és a count() függvénnyel nézd meg, szerepel-e a másik halmazban. A csak az egyikben szereplő neveket írd egy harmadik halmazba, és ennek méretét, elemeit írd ki. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    set<string> elso, masodik, eredmeny;
    for (int i = 0; i < n; ++i) {
        string s;
        cin >> s;
        elso.insert(s);
    }

    int m;
    cin >> m;
    for (int i = 0; i < m; ++i) {
        string s;
        cin >> s;
        masodik.insert(s);
    }

    for (const string& s : elso) {
        if (!masodik.count(s)) eredmeny.insert(s);
    }
    for (const string& s : masodik) {
        if (!elso.count(s)) eredmeny.insert(s);
    }

    cout << eredmeny.size() << '\n';
    for (const string& s : eredmeny) cout << s << '\n';
    return 0;
}