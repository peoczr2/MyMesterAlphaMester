/*
Megoldás lényege:
Minden F egy ágat jelöl, és egy ág mélysége a körülötte nyitott zárójelek száma.
A d mélységű ág tömege a törzs tömegének 2^(-d)-szerese, ezért a legtávolabbi
ágak tömegét 1-nek véve a törzs tömege 2^H, ahol H a legnagyobb mélység, a fa
magassága pedig H+1. A fa összes tömege így Σ darab(d) * 2^(H-d), amit Horner-
sémával, T = 2T + darab(d) lépésekkel kapunk meg. Mivel H akár tízezres nagyságú
is lehet, a számokat 10^9-es alapú tömbben tároljuk, és egyszerre 29 bit-lépést
végzünk. Az időigény a bemenet hosszával és a nagy számok méretével arányos.
*/
/*
Hint 1: || Minden F egy ág, és az ág mélységét a nyitó zárójelek száma adja, így a mélységek egyetlen bejárással megszámolhatók. ||
Hint 2: || A törzs tömege 2^H, ahol H a legnagyobb mélység, mert a mélység növekedésével a tömeg minden lépésben felére csökken. ||
Hint 3: || A fa tömege a mélységenkénti darabszámok összege: Σ darab(d) * 2^(H-d), ezt Horner-sémával érdemes kiszámolni. ||
*/
#include <bits/stdc++.h>
using namespace std;

// Nagy egész szám: 10^9-es alapú számjegyek, a legkisebb helyiértéktől kezdve.
using Big = vector<uint32_t>;
const uint64_t BASE = 1000000000ULL;

// x = x * m + add, ahol m = 2^k (k <= 29) és add tetszőleges 64 bites érték.
void mulAdd(Big& x, uint64_t m, uint64_t add) {
    uint64_t carry = add;
    for (auto& limb : x) {
        uint64_t cur = (uint64_t)limb * m + carry;
        limb = (uint32_t)(cur % BASE);
        carry = cur / BASE;
    }
    while (carry) {
        x.push_back((uint32_t)(carry % BASE));
        carry /= BASE;
    }
}

void printBig(const Big& x) {
    if (x.empty()) {
        cout << 0;
        return;
    }
    cout << x.back();
    for (int i = (int)x.size() - 2; i >= 0; --i) {
        cout << setw(9) << setfill('0') << x[i];
    }
    cout << setfill(' ');
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;

    // cnt[d]: hány F van d mélyen (a mélység a nyitott zárójelek száma)
    vector<long long> cnt;
    int depth = 0;
    for (char c : s) {
        if (c == '#') break;
        if (c == '(') {
            ++depth;
        } else if (c == ')') {
            --depth;
        } else if (c == 'F') {
            if ((int)cnt.size() <= depth) cnt.resize(depth + 1, 0);
            ++cnt[depth];
        }
    }
    int H = (int)cnt.size() - 1;

    // A törzs tömege 2^H
    Big trunk = {1};
    for (int i = 0; i < H; i += 29) {
        int k = min(29, H - i);
        mulAdd(trunk, 1ULL << k, 0);
    }

    // A fa tömege: Horner-séma, blokkonként 29 mélységgel: T = T * 2^k + blokk
    Big total;
    for (int d = 0; d <= H; d += 29) {
        int k = min(29, H + 1 - d);
        uint64_t block = 0;
        for (int j = 0; j < k; ++j) {
            block += (uint64_t)cnt[d + j] << (k - 1 - j);
        }
        mulAdd(total, 1ULL << k, block);
    }

    cout << H + 1 << '\n';
    printBig(trunk);
    cout << '\n';
    printBig(total);
    cout << '\n';
    return 0;
}
