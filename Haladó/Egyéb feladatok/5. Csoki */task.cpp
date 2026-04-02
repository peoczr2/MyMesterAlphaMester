/*
Az [L, R] dobozszakasz akkor jo, ha az osszes csoki szama oszthato N-nel. Pozitiv ertekek miatt
az oszthato osszegu jo szakaszok kozul azt keressuk, amelynek a csokiszama minimalis.

Legyen pref[i] az elso i doboz osszege. Ekkor az [L, R] szakasz osszege pref[R] - pref[L-1], es
pontosan akkor oszthato N-nel, ha a ket prefix maradeka azonos. Mivel a prefixosszegek szigoruan
nonek, ugyanahhoz a maradekhoz a legkisebb kulonbseg mindig ket egymas utani elofordulas kozott
jon ki. Ezert minden maradekhoz eleg az utolso elofordulast tarolni.
*/
/*
Hint 1: || Egy részösszeg akkor osztható N-nel, ha a két határoló prefixösszeg ugyanazt a maradékot adja N-nel osztva. ||
Hint 2: || Pozitív dobozértékeknél a prefixösszegek nőnek, ezért ugyanahhoz a maradékhoz a legkisebb különbséget az egymást követő előfordulások adják. ||
Hint 3: || Minden maradékhoz elég az utolsó indexet és prefixösszeget megjegyezni. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long n;
    int m;
    cin >> n >> m;

    unordered_map<long long, int> lastIndex;
    unordered_map<long long, long long> lastPrefix;
    lastIndex.reserve((size_t)m * 2 + 10);
    lastPrefix.reserve((size_t)m * 2 + 10);

    long long prefix = 0;
    lastIndex[0] = 0;
    lastPrefix[0] = 0;

    long long bestSum = (1LL << 62);
    int bestL = -1;
    int bestR = -1;

    for (int i = 1; i <= m; ++i) {
        long long x;
        cin >> x;
        prefix += x;
        long long residue = prefix % n;

        auto it = lastIndex.find(residue);
        if (it != lastIndex.end()) {
            long long currentSum = prefix - lastPrefix[residue];
            if (currentSum < bestSum) {
                bestSum = currentSum;
                bestL = it->second + 1;
                bestR = i;
            }
        }

        lastIndex[residue] = i;
        lastPrefix[residue] = prefix;
    }

    if (bestL == -1) {
        cout << 0 << '\n';
    } else {
        cout << bestL << ' ' << bestR << '\n';
    }
    return 0;
}