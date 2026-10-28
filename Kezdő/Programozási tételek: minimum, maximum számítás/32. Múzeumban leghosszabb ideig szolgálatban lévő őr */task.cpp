/*
Megoldás lényege:
Egy őr szolgálati napjainak száma a két határnap között zárt intervallumot alkot, mert az első és az utolsó nap is szolgálati nap volt. Ez U − E + 1 napot jelent. Az őröket egyenként beolvassuk, minden őrnél kiszámoljuk a napok számát, és az eddigi legnagyobb értéket tartjuk nyilván. Az időigény O(N), a memóriaigény O(1).
*/
/*
Hint 1: || Figyelj arra, hogy mindkét határnap szolgálati nap volt, ezért a napok száma nem a két sorszám különbsége, hanem ennél eggyel több. ||
Hint 2: || Minden őrre számold ki a napok számát, és menet közben tartsd nyilván az eddigi legnagyobb értéket; a végén ezt írd ki. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int days, guards;
    cin >> days >> guards;

    int maxDays = 0;
    for (int i = 0; i < guards; i++) {
        int first, last;
        cin >> first >> last;
        maxDays = max(maxDays, last - first + 1);
    }

    cout << maxDays << "\n";
    return 0;
}
