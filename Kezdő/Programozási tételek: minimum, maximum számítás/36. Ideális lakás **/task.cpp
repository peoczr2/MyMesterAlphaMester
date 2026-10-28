/*
Megoldás lényege:
Minden lakásra kiszámoljuk az anti-értéket a megadott képlettel, és egy menetben keressük a legkisebbet. Egyenlő anti-érték esetén a legolcsóbb lakás nyer, ha az ár is egyenlő, akkor a felsorolásban korábbi lakás marad. Ezért a csere akkor történik, ha az anti-érték szigorúan kisebb, vagy ha egyenlő, de a lakás ára szigorúan kisebb; a sorszám csak így marad a legkisebb a döntetlen esetekben is. Nem kell a teljes listát tárolni, elég a legjobb értéket, árat és sorszámot megtartani. Az időigény O(N), a memóriaigény O(1).
*/
/*
Hint 1: || Nem kell a lakások listáját eltárolni: egy menetben elég az eddigi legjobb anti-értéket, árat és sorszámot megtartani. ||
Hint 2: || A döntetlent két szinten érdemes kezelni: előbb az anti-érték számít, egyenlőség esetén az ár, és csak ha az ár is egyenlő, marad a korábbi lakás. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, idealPrice, idealSize, c, d;
    cin >> n >> idealPrice >> idealSize >> c >> d;

    long long bestValue = LLONG_MAX;
    int bestPrice = 0;
    int bestIndex = 0;
    for (int i = 1; i <= n; i++) {
        int price, size;
        cin >> price >> size;

        long long dp = price - idealPrice;
        long long ds = size - idealSize;
        long long value = (long long)c * dp * dp + (long long)d * ds * ds;

        if (value < bestValue || (value == bestValue && price < bestPrice)) {
            bestValue = value;
            bestPrice = price;
            bestIndex = i;
        }
    }

    cout << bestIndex << "\n";
    return 0;
}
