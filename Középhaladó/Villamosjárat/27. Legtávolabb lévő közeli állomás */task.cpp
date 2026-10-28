/*
Megoldás lényege:
Az induló állomástól mért távolság az előzőtől mért távolságok folyamatos összegzésével adódik, ez az állomások sorszámával szigorúan nő. Ezért a K méternél közelebbi állomások közül a legtávolabbit az a utolsó állomás adja, amelynek távolsága még kisebb K-nál. Az induló állomás (0 méter) mindig K-nál közelebb van, ezért ez az alapértelmezett válasz. Az időigény O(N).
*/
/*
Hint 1: || Az induló állomástól mért távolság az előző állomásoktól mért távolságok összege; ezt egyetlen ciklusban számold ki, és közben olvasd be az adatokat. ||
Hint 2: || Mivel a távolságok növekvő sorrendben jönnek, nem kell keresgélni: minden K-nál közelebbi állomásnál írd felül a korábbi jelöltet. Ha egyik állomás sem felel meg, a válasz az induló állomás. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    long long k;
    cin >> n >> k;

    long long pos = 0;      // az induló állomástól mért távolság
    int ansIdx = 0;         // az induló állomás sorszáma
    long long ansDist = 0;
    for (int i = 1; i <= n; i++) {
        long long t;
        int arr, dep;
        cin >> t >> arr >> dep;
        pos += t;
        if (pos < k) {
            ansIdx = i;
            ansDist = pos;
        }
    }

    cout << ansIdx << ' ' << ansDist << '\n';
    return 0;
}
