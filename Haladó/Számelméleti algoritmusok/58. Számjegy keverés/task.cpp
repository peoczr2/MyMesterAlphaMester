/*
 * A legkevesebb műveletet azzal érjük el, ha minden lépésben a számjegyek
 * legkisebb érvényes permutációját használjuk. Így a válasz a kezdő számjegyek
 * legkisebb nem vezető nullás permutációja.
 
Hint 1: || Minden lépésben szabadon átrendezheted a számjegyeket, ezért azt kell átgondolni, melyik permutációból a legjobb levonni 1-et. ||
Hint 2: || Érdemes a számjegyek rendezett alakjából kiindulni, és azt vizsgálni, hogyan változik a multihalmaz egy kivonás után. ||
*/

#include "../common.hpp"

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;
    sort(s.begin(), s.end());
    if (s[0] == '0') {
        int pos = 0;
        while (pos < (int)s.size() && s[pos] == '0') ++pos;
        swap(s[0], s[pos]);
        sort(s.begin() + 1, s.end());
    }
    cout << s << '\n';
    return 0;
}
