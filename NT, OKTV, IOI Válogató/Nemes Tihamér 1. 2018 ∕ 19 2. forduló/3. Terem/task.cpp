/*
Megoldás lényege:
Az első részfeladatban egy a×b (a≥b) téglalapba a legnagyobb négyzet oldala b, így a/b darab b×b lap kerül le, a maradék (a mod b)×b téglalapon ugyanígy folytatunk; ez az euklideszi algoritmus osztási lépése, a hányadosok összege adja a lapok számát. A második részfeladatban az egyforma négyzetek oldala csak az a és b közös osztója lehet, a legkevesebb lap a legnagyobb közös osztóval (g) kapható, így a darabszám (a/g)·(b/g). Mindkét rész időigénye O(log(max(a, b))), mert az euklideszi lépések száma logaritmikus.
*/
/*
Hint 1: || Az első részfeladat lépéseit a téglalap két oldalának viszonyából érdemes felírni: a rövidebb oldallal egyező négyzet mindig levágható, és ami marad, az kisebb téglalap. ||
Hint 2: || Ha a ≥ b, akkor a/b darab b×b négyzet fér el, a maradék (a mod b) × b téglalapon ugyanígy folytatható, a lépések számát a hányadosok összege adja. ||
Hint 3: || Az egyforma négyzetek oldala osztja mindkét oldalt, így a legnagyobb ilyen oldal a két szám legnagyobb közös osztója, a darabszám pedig (a/g)·(b/g). ||
*/
#include <bits/stdc++.h>
using namespace std;

static long long greedy(long long a, long long b) {
    long long cnt = 0;
    while (a && b) {
        if (a < b) swap(a, b);
        cnt += a / b;
        a %= b;
    }
    return cnt;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long a, b;
    cin >> a >> b;
    long long g = std::gcd(a, b);
    cout << greedy(a, b) << '\n' << (a / g) * (b / g) << '\n';
    return 0;
}