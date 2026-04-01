/*
 * A Fano-síkra épített konstrukció: 7 bázisprímre vesszük a 7 vonalat, és minden
 * vonalhoz több különböző tagprímmel ellátott számot rendelünk. Két szám bármely
 * két vonala metszi egymást, de 51 számban nincs közös bázisprím.
 
Hint 1: || Nem egyetlen optimális számot kell találni, hanem bármilyen jó konstrukció megfelel. ||
Hint 2: || Érdemes közös prímosztós szerkezetben gondolkodni: úgy válassz prímszorzatokat, hogy bármely két szám metssze egymást, de egy túl nagy részhalmaznak már ne legyen közös príme. ||
Hint 3: || A konkrét megoldás egy kis, kézzel felépíthető rendszeren alapul; a cél az, hogy a szükséges metszések megmaradjanak, de a túl sok elem már egyenlő legyen a teljes családdal. ||
*/

#include "../common.hpp"

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int64> base = {2, 3, 5, 7, 11, 13, 17};
    vector<vector<int>> lines = {
        {0,1,2}, {0,3,4}, {0,5,6},
        {1,3,5}, {1,4,6}, {2,3,6}, {2,4,5}
    };
    auto primes = sieve_primes(800);
    vector<int64> tags;
    for (int p : primes) if (p > 17) tags.push_back(p);
    vector<int64> ans;
    int tag_id = 0;
    for (int rep = 0; rep < 14 && (int)ans.size() < n; ++rep) {
        for (auto& line : lines) {
            int64 val = 1;
            for (int idx : line) val *= base[idx];
            val *= tags[tag_id++];
            ans.push_back(val);
            if ((int)ans.size() == n) break;
        }
    }
    while ((int)ans.size() < n) {
        int64 val = base[0] * base[1] * base[2] * tags[tag_id++];
        ans.push_back(val);
    }
    for (auto x : ans) cout << x << '\n';
    return 0;
}
