/*
Megoldás lényege:
Egy helységben akkor fordult elő mindenféle madár, ha a helység sorának minden eleme nullától különböző, vagyis minden fajból látták legalább egy egyedét. Soronként olvasunk, és minden sorra eldöntjük, hogy van-e benne nulla. Ha találunk olyan sort, amelyben nincs nulla, a válasz 1, különben 0. A bejárás O(M·N) időben fut, a memóriaigény O(1).
*/
/*
Hint 1: || Egy helységet akkor kell jónak tekintened, ha a sorában minden darabszám nullától különböző. Elég a sorokat egyenként végignézni. ||
Hint 2: || Soronként tarts egy logikai jelzőt, amely kezdetben igaz. Az első nulla elemnél állítsd hamisra, a sor végén pedig nézd meg, maradt-e igaz; ha igen, a válasz 1. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int M, N;
    cin >> M >> N;

    bool van = false;
    for (int i = 0; i < M; ++i) {
        bool mindenfele = true;
        for (int j = 0; j < N; ++j) {
            int e;
            cin >> e;
            if (e == 0) mindenfele = false;
        }
        if (mindenfele) van = true;
    }

    cout << (van ? 1 : 0) << '\n';
    return 0;
}
