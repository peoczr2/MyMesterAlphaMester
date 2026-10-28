/*
Megoldás lényege:
Az utat két szakaszra bontjuk: az első Y kilométer Nyuszi házáig, a maradék X - Y kilométer Malackáig tart. Minden megtett kilométeren egy csupor mézet eszik Micimackó, ha van még nála. Az első szakasz után a meglévő K csupor maradéka max(0, K - Y), ehhez jön Nyuszitól N csupor. A második szakaszon ugyanígy fogy a méz, az eredmény nem lehet negatív, ezért a végén max(0, ...). Az időigény állandó.
*/
/*
Hint 1: || Az utat két részre bontsd: az első Y kilométer Nyuszi házáig tart, a maradék X - Y kilométer Malackáig. Mindkét szakaszon minden kilométer egy csuporba kerül, de csak akkor, ha van még méz. ||
Hint 2: || Az első szakasz után a mézből K - Y marad (de legalább 0), ehhez jön Nyuszitól N. A második szakaszon ebből X - Y csuprot kell levonni, de nem mehet a méz negatívba, ezért a végén 0 és a szám közül a nagyobbat írd ki. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int y, x;  // Nyuszi távolsága, Malacka távolsága
    cin >> y >> x;
    int k, n;  // Micimackó otthoni mézkészlete, Nyuszitól kapott méz
    cin >> k >> n;

    // Az első Y kilométeren megeszi az otthoni mézet, ha van
    int mez = max(0, k - y);
    // Nyuszinál N csupor mézet kap
    mez += n;
    // A maradék (X - Y) kilométeren ugyanígy fogy a méz
    mez = max(0, mez - (x - y));

    cout << mez << '\n';
    return 0;
}
