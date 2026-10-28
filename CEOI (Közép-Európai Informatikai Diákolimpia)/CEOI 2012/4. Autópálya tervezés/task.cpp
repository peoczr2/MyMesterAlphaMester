/*
Megoldás lényege:
Az isOnLine(x,y,z) pontosan akkor ad 1-et, ha a három város ugyanarra az autópályára esik. Az első öt város között biztosan van három, amely egy autópályán van, mert az öt pont közül valamelyik osztályba legalább három jut; ezt próbálgatással megtaláljuk. Egy ilyen hármas egyik városát (a) horgonynak tekintjük: az isOnLine(a,z,w) kérdés egyszerre dönti el két város tartozását, és csak akkor 1, ha z és w is a horgony autópályáján van. Ha 0 jön, a két város közül legalább az egyik a másik autópályán van; ekkor egy újabb kérdéssel (isOnLine(a,b,z), ahol b szintén a horgony autópályáján van) eldől, melyik. Így nagyjából N/2 kérdés elég: a hármas két tagja (a, b) adja az egyik autópálya két pontját, a másik autópályán pedig a két talált város.
*/
/*
Hint 1: || Az isOnLine(x,y,z) akkor és csak akkor 1, ha a három város ugyanarra az autópályára esik. Egy rögzített, már ismert autópályán lévő várossal párokat is le lehet ellenőrizni: ha a pár mindkét tagja ugyanazon az autópályán van, a kérdés 1-et ad. ||
Hint 2: || Az első öt város között az egyik autópályán legalább három város van, ezért próbáld ki az öt város hármasait, amíg az isOnLine 1-et nem ad. ||
Hint 3: || Ha egy pár kérdésére 0 a válasz, a két város közül legalább az egyik a másik autópályán van. Ezt egyetlen város vizsgálatával, a talált hármas két tagjával együtt el lehet dönteni, és így minden 0-s párból egy új pontot kapunk. ||
*/
#include "office.h"
#include <vector>
using namespace std;

int main() {
    long n = GetN();

    // 1. Három, egy autópályán lévő város keresése az első öt között.
    long a = 0, b = 0, c = 0;
    long m = n < 5 ? n : 5;
    for (long i = 1; i <= m && a == 0; i++)
        for (long j = i + 1; j <= m && a == 0; j++)
            for (long k = j + 1; k <= m && a == 0; k++)
                if (isOnLine(i, j, k) == 1) {
                    a = i;
                    b = j;
                    c = k;
                }

    // 2. A többi városok párokban: isOnLine(a,z,w)=1 esetén z és w az a autópályáján van.
    vector<long> rest;
    for (long x = 1; x <= n; x++)
        if (x != a && x != b && x != c)
            rest.push_back(x);

    vector<long> other;   // a másik autópályán lévő városok
    size_t i = 0;
    while (other.size() < 2 && i + 1 < rest.size()) {
        long z = rest[i], w = rest[i + 1];
        i += 2;
        if (isOnLine(a, z, w) == 1)
            continue;                       // mindkettő az a autópályáján van
        // legalább az egyik a másik autópályán van: z-t megvizsgáljuk
        if (isOnLine(a, b, z) == 0)
            other.push_back(z);
        else
            other.push_back(w);
    }
    if (other.size() < 2 && i < rest.size()) {
        if (isOnLine(a, b, rest[i]) == 0)
            other.push_back(rest[i]);
    }

    Answer(a, b, other[0], other[1]);
    return 0;
}
