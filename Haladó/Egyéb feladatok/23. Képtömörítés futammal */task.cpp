/*
Megoldás:
Sorfolytonosan beolvassuk a képet, és minden sorban balról jobbra végigmegyünk. Egy futam
mindig egy maximális, azonos betűkből álló összefüggő szakasz. Az aktuális futam hosszát növeljük,
amíg ugyanaz a betű jön, különben kiírjuk az előző futamot és újat indítunk.

Minden képpontot pontosan egyszer nézünk meg, ezért az algoritmus O(N*M) idejű és O(M)
memóriát használ az aktuális sor tárolására.
*/
/*
Hint 1: || Egy sor tömörítéséhez elég azt figyelni, mikor változik meg a karakter. ||
Hint 2: || A futam hossza és színe csak a soron belüli szomszédos elemek összehasonlításától függ. ||
*/

#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    cout << n << ' ' << m << '\n';

    vector<char> row(m);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> row[j];
        }

        int length = 1;
        for (int j = 1; j <= m; ++j) {
            if (j < m && row[j] == row[j - 1]) {
                ++length;
            } else {
                if (j != length) {
                    cout << ' ';
                }
                cout << length << ' ' << row[j - 1];
                length = 1;
            }
        }
        cout << '\n';
    }

    return 0;
}