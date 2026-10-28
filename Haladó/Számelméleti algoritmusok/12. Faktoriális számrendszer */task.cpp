/*
Megoldás lényege:
Tízesből faktoriálisba úgy váltunk, hogy a számot egymás után 2-vel, 3-mal, 4-gyel,
... osztjuk, és a maradékok adják a számjegyeket; a jobb szélső számjegy alapja 2,
a tőle balra lévőé 3, és így tovább. Fordítva a jobbról k-adik (nullától számolt)
számjegy súlya (k+1)!, ezért a számjegyeket jobbról balra haladva a futó faktoriálist
lépésenként növelve, a számjegyet súlyozva összegezzük. Mindkét irány a számjegyek
számával arányos időt igényel, ami a feladat méreteinél elhanyagolható.
*/
/*
Hint 1: || Tízesből faktoriálisba úgy tudsz váltani, hogy sorban osztasz 2-vel, 3-mal, 4-gyel és a maradékokat gyűjtöd. ||
Hint 2: || Visszafelé haladj jobbról balra, és minden lépésben szorozd a futó faktoriálist eggyel nagyobb számmal; így a számjegyek súlya 1!, 2!, 3!, ... lesz. ||
*/

#include "../common.hpp"

static string to_factorial(int64 x) {
    if (x == 0) return "0";
    string digits;
    for (int base = 2; x > 0; ++base) {
        digits.push_back(char('0' + (x % base)));
        x /= base;
    }
    while (digits.size() > 1 && digits.back() == '0') digits.pop_back();
    reverse(digits.begin(), digits.end());
    return digits;
}

static int64 from_factorial(const string& s) {
    int64 value = 0;
    int64 fact = 1;
    for (int k = 0; k < (int)s.size(); ++k) {
        char c = s[s.size() - 1 - k];
        fact *= (k + 1);
        value += (c - '0') * fact;
    }
    return value;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int64 a;
    string b;
    cin >> a >> b;
    cout << to_factorial(a) << '\n';
    cout << from_factorial(b) << '\n';
    return 0;
}
