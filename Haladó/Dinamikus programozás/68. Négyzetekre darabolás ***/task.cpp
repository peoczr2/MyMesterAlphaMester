/*
Legyen dp[a][b] az a*b teglalap optimalis, vagyis legkevesebb negyzetre valo feldarabolasanak
negyszetszama. Ha a teglalap mar negyzet, akkor az ertek 1. Egyebkent az utolso vagas vagy egy
vizszintes, vagy egy fuggoleges vagas volt, igy minden lehetseges ketreszre vagas kiprobalhato:
dp[a][b] a ket resz optimumainak osszegeben minimalis. A legjobb vagas iranyat es helyet is
eltesszuk, majd rekurzivan visszafejtjuk, hany darab milyen meretu negyzet keletkezik.
*/
/*
Hint 1: || Egy optimalis darabolas utolso lepese biztosan egy egyenes vagas a teljes darabon at. ||
Hint 2: || Ha ismered a ket keletkezo teglalap optimumat, azok osszege adja az adott vagas koltseget. ||
Hint 3: || A visszaepitesnel mar nem a vagasokat kell kiirni, hanem a keletkezo negyzetek darabszamat meretenkent. ||
*/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct Decision {
    char type;
    int cut;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int a, b;
    cin >> a >> b;

    vector<vector<int>> dp(a + 1, vector<int>(b + 1, 0));
    vector<vector<Decision>> choice(a + 1, vector<Decision>(b + 1, Decision{'S', 0}));

    for (int height = 1; height <= a; ++height) {
        for (int width = 1; width <= b; ++width) {
            if (height == width) {
                dp[height][width] = 1;
                continue;
            }
            dp[height][width] = 1e9;
            for (int cut = 1; cut < height; ++cut) {
                int value = dp[cut][width] + dp[height - cut][width];
                if (value < dp[height][width]) {
                    dp[height][width] = value;
                    choice[height][width] = Decision{'H', cut};
                }
            }
            for (int cut = 1; cut < width; ++cut) {
                int value = dp[height][cut] + dp[height][width - cut];
                if (value < dp[height][width]) {
                    dp[height][width] = value;
                    choice[height][width] = Decision{'V', cut};
                }
            }
        }
    }

    vector<int> count(max(a, b) + 1, 0);
    auto collect = [&](auto&& self, int height, int width) -> void {
        if (height == width) {
            ++count[height];
            return;
        }
        Decision here = choice[height][width];
        if (here.type == 'H') {
            self(self, here.cut, width);
            self(self, height - here.cut, width);
        } else {
            self(self, height, here.cut);
            self(self, height, width - here.cut);
        }
    };
    collect(collect, a, b);

    cout << dp[a][b] << '\n';
    for (int size = 1; size <= max(a, b); ++size) {
        if (count[size] > 0) {
            cout << size << ' ' << count[size] << '\n';
        }
    }
    return 0;
}