/*
Megoldás lényege:
Mindkét időpontot másodpercekben számoljuk az első hét első napjának 0:00:00 pillanatától, így a két időpont távolsága egyszerű abszolút különbség lesz. A távolságot hét, nap, óra, perc és másodperc szerint váltjuk vissza, a távolság hete és napja 0-tól számozódik, ahogy a mintában. A második időpont a későbbi időpont plusz ugyanez a távolság, amit már az eredeti, 1-től induló számozással írunk ki. A váltások fix egységekkel (604800, 86400, 3600 és 60 másodperc) dolgoznak, így a visszaváltás egyértelmű és minden bemenetre helyes. Az időigény O(1), mert csak néhány aritmetikai művelet történik.
*/
/*
Hint 1: || Az időpontokat érdemes egyetlen számmá, másodperccé alakítani, mert így a távolság egy kivonás és egy abszolútérték. ||
Hint 2: || Visszaváltáskor maradékos osztással bontsd a másodpercszámot: először a hét (604 800 másodperc), majd a nap (86 400), az óra (3600), a perc (60), a maradék a másodperc; a második időpontnál a hét és a nap számozása 1-től induljon. ||
*/
#include <bits/stdc++.h>
using namespace std;

static const long long SEC_DAY = 24LL * 60 * 60;
static const long long SEC_WEEK = 7LL * SEC_DAY;

static long long toSeconds(int w, int d, int h, int m, int s) {
    return 1LL * (w - 1) * SEC_WEEK + 1LL * (d - 1) * SEC_DAY + 1LL * h * 3600 + 1LL * m * 60 + s;
}

static void fromSeconds(long long x) {
    long long w = x / SEC_WEEK;
    x %= SEC_WEEK;
    long long d = x / SEC_DAY;
    x %= SEC_DAY;
    long long h = x / 3600;
    x %= 3600;
    long long m = x / 60;
    long long s = x % 60;
    cout << (w + 1) << ' ' << (d + 1) << ' ' << h << ' ' << m << ' ' << s << '\n';
}

static void fromDuration(long long x) {
    long long w = x / SEC_WEEK;
    x %= SEC_WEEK;
    long long d = x / SEC_DAY;
    x %= SEC_DAY;
    long long h = x / 3600;
    x %= 3600;
    long long m = x / 60;
    long long s = x % 60;
    cout << w << ' ' << d << ' ' << h << ' ' << m << ' ' << s << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int w1, d1, h1, m1, s1;
    int w2, d2, h2, m2, s2;
    cin >> w1 >> d1 >> h1 >> m1 >> s1;
    cin >> w2 >> d2 >> h2 >> m2 >> s2;

    long long a = toSeconds(w1, d1, h1, m1, s1);
    long long b = toSeconds(w2, d2, h2, m2, s2);
    long long diff = llabs(a - b);

    fromDuration(diff);

    long long later = max(a, b);
    fromSeconds(later + diff);
    return 0;
}