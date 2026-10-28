/*
Megoldás lényege: a pontokat lefedő, tengelyekkel párhuzamos oldalú téglalap szélessége az x-koordináták maximuma és minimuma közötti különbség, magassága ugyanez az y-koordinátákra. Bármely lefedő téglalap tartalmazza a pontok x- és y-tartományát, így ez a téglalap a legkisebb, a területe (maxX - minX) * (maxY - minY). A beolvasás közben egyetlen menetben nyilvántartjuk a minimumokat és maximumokat, ezért az idő O(N), a memóriaigény O(1). A területre 64 bites egész kell, bár a legnagyobb érték csak kb. 4 * 10^8.
*/
/*
Hint 1: || A téglalap oldalai függetlenek egymástól: a szélesség csak az x-koordinátáktól, a magasság csak az y-koordinátáktól függ. ||
Hint 2: || Egyetlen beolvasási ciklusban tartsd nyilván az x és y koordináták legkisebb és legnagyobb értékét, majd a területet a négy szám különbségéből számold ki. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    long long minX = LLONG_MAX, maxX = LLONG_MIN;
    long long minY = LLONG_MAX, maxY = LLONG_MIN;

    for (int i = 0; i < n; i++) {
        long long x, y;
        cin >> x >> y;
        minX = min(minX, x);
        maxX = max(maxX, x);
        minY = min(minY, y);
        maxY = max(maxY, y);
    }

    long long area = (maxX - minX) * (maxY - minY);
    cout << area << '\n';
    return 0;
}
