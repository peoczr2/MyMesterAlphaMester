#include <bits/stdc++.h>
using namespace std;

/*
    A nagymutató 6 fokot fordul percenként, a kismutató pedig óránként 30-at
    és percenként 0.5 fokot. A két mutató kisebb bezárt szögét kell kiírni.
*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int ora, perc;
    cin >> ora >> perc;

    int oramutato2 = 60 * (ora % 12) + perc;
    int percmutato2 = 12 * perc;
    int kulonbseg2 = abs(oramutato2 - percmutato2);
    int eredmeny2 = min(kulonbseg2, 720 - kulonbseg2);

    cout << eredmeny2 / 2 << '\n';
    return 0;
}