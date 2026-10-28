/*
Megoldás lényege:
Mindkét racionális számot "p/q" alakú törtté írjuk: p = A·C + B, q = C. Az összeg számlálója p1·q2 + p2·q1, nevezője q1·q2; a szorzat számlálója p1·p2, nevezője szintén q1·q2. Mindkét eredményt maradékos osztással bontjuk: a hányados az egész rész, a maradék a törtrész számlálója, a nevező pedig a törtrészé. Ha a maradék nem nulla, a törtrészt a legnagyobb közös osztójával egyszerűsítjük; ha nulla, a nevezőt úgy írjuk ki, ahogy van, ahogy a minta is mutatja. A művelet állandó idejű.
*/
/*
Hint 1: || Írd át mindkét számot törtté: az egész rész szorozva a nevezővel, plusz a számláló adja az új számlálót, a nevező pedig marad. Utána az összeadást és a szorzást a törtekre megszokott szabállyal végezd el. ||
Hint 2: || Az eredmény számlálóját a nevezővel osztva kapod az egész részt (a hányados) és a törtrész számlálóját (a maradék). Egyszerűsítéshez a maradékot és a nevezőt oszd a legnagyobb közös osztójukkal, de ha a maradék 0, a nevezőt hagyd érintetlenül. ||
*/
#include <bits/stdc++.h>
using namespace std;

// Egy p/den törtet ír ki: egész rész, törtrész számlálója, nevezője.
void printMixed(long long num, long long den) {
    long long whole = num / den;
    long long rem = num % den;
    if (rem == 0) {
        cout << whole << " 0 " << den << '\n';
    } else {
        long long g = gcd(rem, den);
        cout << whole << ' ' << rem / g << ' ' << den / g << '\n';
    }
}

int main() {
    long long a1, b1, c1, a2, b2, c2;
    cin >> a1 >> b1 >> c1;
    cin >> a2 >> b2 >> c2;

    long long p1 = a1 * c1 + b1, q1 = c1;
    long long p2 = a2 * c2 + b2, q2 = c2;

    printMixed(p1 * q2 + p2 * q1, q1 * q2);
    printMixed(p1 * p2, q1 * q2);
    return 0;
}
