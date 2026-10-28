/*
Megoldás lényege:
Két kódszám ugyanazt a zárat nyitja, ha hosszuk egyforma, és a szomszédos jegyek különbsége 10-es maradékban megegyezik. A tízszög csúcsai körben követik egymást, így a forgatás (a csúcsok eltolása) ezt a különbségsorozatot nem változtatja meg, a tükrözés pedig nem megengedett. Ezért minden kódszámot a szomszédos jegyek (mod 10) különbségsorozatával jellemzünk, és két kódszám akkor ekvivalens, ha hosszuk és ez a sorozatuk megegyezik. A 0-val kezdődő ekvivalens kódszámot a helyes kód különbségeiből kapjuk: 0-tól kezdve, mindig 10-zel osztott maradékkal összegezünk. Az ismétlődő jegyek kereséséhez próbálkozásonként egy 10 elemű logikai tömb elegendő. Az időigény O(N·L), ahol L ≤ 10 a kódszám hossza.
*/
/*
Hint 1: || Egy kódszám alakzatát a szomszédos jegyek különbsége (mod 10) adja meg, és ez a forgatás során nem változik. Két kódszám így akkor ekvivalens, ha hosszuk azonos és a különbségsorozatuk egyezik. ||
Hint 2: || A 0-val kezdődő kódszámhoz a helyes kód különbségeit 0-tól kezdve, a következő jegyet mindig (előző jegy + különbség) mod 10 módon számold ki. ||
Hint 3: || Az első ismétlődő jegy megkereséséhez minden próbálkozásnál végigmehetsz a jegyeken egy 10 elemű logikai tömbbel: az első olyan sorszám lesz a válasz, ahol egy jegy másodszor is előfordul. ||
*/
#include <bits/stdc++.h>
using namespace std;

// A kódszám különbségsorozata: a szomszédos jegyek különbsége mod 10.
vector<int> kulonbseg(const string& s) {
    vector<int> d;
    for (size_t i = 1; i < s.size(); i++)
        d.push_back(((s[i] - s[i - 1]) % 10 + 10) % 10);
    return d;
}

bool ekvivalens(const string& a, const string& b) {
    return a.size() == b.size() && kulonbseg(a) == kulonbseg(b);
}

bool ismetlodik(const string& s) {
    bool lat[10] = {false};
    for (char c : s) {
        int j = c - '0';
        if (lat[j]) return true;
        lat[j] = true;
    }
    return false;
}

int main() {
    string helyes;
    int n;
    cin >> helyes >> n;
    vector<string> p(n);
    for (auto& s : p) cin >> s;

    // 1. részfeladat: a pontosan helyes kódszámot használt próbálkozások sorszámai
    cout << "#\n";
    vector<int> pontos;
    for (int i = 0; i < n; i++)
        if (p[i] == helyes) pontos.push_back(i + 1);
    if (pontos.empty()) {
        cout << "nem\n";
    } else {
        for (size_t i = 0; i < pontos.size(); i++) {
            if (i) cout << " ";
            cout << pontos[i];
        }
        cout << "\n";
    }

    // 2. részfeladat: az első ismétlődő jegyet tartalmazó próbálkozás
    cout << "#\n";
    int elso = -1;
    for (int i = 0; i < n && elso == -1; i++)
        if (ismetlodik(p[i])) elso = i + 1;
    if (elso == -1) cout << "nem\n";
    else cout << elso << "\n";

    // 3. részfeladat: a helyes kódszámmal ekvivalens, 0-val kezdődő kódszám
    cout << "#\n";
    string nulla = "0";
    int cur = 0;
    for (int d : kulonbseg(helyes)) {
        cur = (cur + d) % 10;
        nulla += char('0' + cur);
    }
    cout << nulla << "\n";

    // 4. részfeladat: minden próbálkozás eredménye
    cout << "#\n";
    for (const auto& s : p) {
        if (s.size() != helyes.size())
            cout << "hibas hossz\n";
        else if (ekvivalens(s, helyes))
            cout << "siker\n";
        else
            cout << "hibas kodszam\n";
    }
    return 0;
}
