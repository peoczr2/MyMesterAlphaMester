/*
Minden településhez egy prímhalmazt rendelünk: a szám ezen alapprímek szorzata, szorozva egy egyedi címke-prímmel,
így a számok biztosan különböznek. Bármely két halmaz metszi egymást, mert N >= 6 esetén projektív sík egyeneseit
használjuk (N = 6-7: a Fano-sík 7 egyenese, N >= 8: a PG(2,3) 13 egyenese, ciklikusan ismételve), N <= 5 esetén
pedig egy teljes gráf csúcsai kapják a hozzájuk tartozó élek prímjeit. Egy alapprím legfeljebb N/2 számban szerepel
(N <= 5-nél 2, N = 6-7-nél 3, N >= 8-nál 4*floor(N/13)+min(4, N mod 13)), ezért bármely több mint felét véve a közös
osztó 1. Az idő O(N), az értékek legfeljebb kb. 8*10^8.
*/
/*
Hint 1: || Nem kell optimális számot adni, bármely megfelelő konstrukció jó. Gondolj arra, hogy bármely két számnak legyen közös prímtényezője, de egyetlen prím se szerepeljen a települések több mint felénél. ||
Hint 2: || Projektív síkban bármely két egyenesnek pontosan egy közös pontja van, és minden pont ugyanannyi egyenesen van. Ha minden település egy egyenes pontjainak prímjeit szorozza össze, a feltétel teljesül; kis síkok: Fano-sík (7 egyenes, 3 pont) vagy PG(2,3) (13 egyenes, 4 pont). ||
Hint 3: || Kis N-re (N <= 5) egy teljes gráf éleit használhatod: minden település a hozzá illeszkedő élek prímjeinek szorzatát kapja. Nagyobb N-re az egyeneseket körbe-körbe ismételd, és minden településhez rendelj egy saját, az alapprímektől különböző címke-prímet, hogy a számok különbözőek legyenek. ||
*/

#include "../common.hpp"

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    // A címke-prímek a 13. prímtől (43) indulnak, így nem ütköznek az alapprímekkel.
    const vector<int> primes = sieve_primes(800);
    const int tag_offset = 13;

    // sets[i]: az i. településhez tartozó alapprímek indexei (az alapprím: primes[idx])
    vector<vector<int>> sets(n);
    if (n <= 5) {
        // Teljes gráf K_n: a csúcsok a települések, az élek az alapprímek.
        int e = 0;
        for (int a = 0; a < n; ++a) {
            for (int b = a + 1; b < n; ++b) {
                sets[a].push_back(e);
                sets[b].push_back(e);
                ++e;
            }
        }
    } else if (n <= 7) {
        // Fano-sík: a {i, i+1, i+3} (mod 7) egyenesek.
        for (int i = 0; i < n; ++i) {
            sets[i] = {i, (i + 1) % 7, (i + 3) % 7};
        }
    } else {
        // PG(2,3): a {j, j+1, j+3, j+9} (mod 13) egyenesek, ciklikusan ismételve.
        for (int i = 0; i < n; ++i) {
            int j = i % 13;
            sets[i] = {j, (j + 1) % 13, (j + 3) % 13, (j + 9) % 13};
        }
    }

    for (int i = 0; i < n; ++i) {
        int64 value = primes[tag_offset + i];
        for (int idx : sets[i]) value *= primes[idx];
        cout << value << '\n';
    }
    return 0;
}
