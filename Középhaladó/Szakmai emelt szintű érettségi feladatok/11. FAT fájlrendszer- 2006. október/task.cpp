/*
Megoldás lényege:
Egy fájl mindig egész számú clusterben foglal helyet, ezért a méretét a clusterméretre felfelé kell kerekíteni. A cluster mérete bájtban N · 1024, így egy fájl clusterszáma (méret + cluster - 1) / cluster egész osztással kapható meg. Az összes fájl clusterszámát összeadjuk, majd szorozzuk N-nel, így a végeredmény kilobájtban lesz. Az időigény O(M), mert minden fájl egyszer szerepel.
*/
/*
Hint 1: || A fájl nem a pontos méretével foglal helyet, hanem a teljes clusterekkel: nem a bájtokat, hanem a lefoglalt clusterek számát kell összegezni. ||
Hint 2: || Egy cluster bájtban N * 1024. Egy fájl clusterszáma felfelé kerekített osztás: (méret + cluster - 1) / cluster. Az összes clusterszám szorozva N-nel adja a kilobájtos eredményt. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    long long n, m;
    cin >> n >> m;
    long long cluster = n * 1024;
    long long clusterek = 0;
    for (long long i = 0; i < m; i++) {
        string nev;
        long long meret;
        cin >> nev >> meret;
        clusterek += (meret + cluster - 1) / cluster;
    }
    cout << clusterek * n << endl;
    return 0;
}
