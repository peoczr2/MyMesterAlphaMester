/*
Megoldás lényege:
A villamos várakozási ideje az útközbeni megállókban töltött idő összege, és egy megállóban ez az indulási és az érkezési idő különbsége (Indi - Erki). Egyetlen bejárásban összegezzük ezeket az értékeket, a végállomás várakozása nem számít bele. A példában a megállónkénti várakozások 4, 0, 2, 10 és 0, összegük 16, ami a helyes kimenet. Időigény O(N).
*/
/*
Hint 1: || Egy megállóban a várakozás az indulási és az érkezési idő különbsége. A kérdés ezeknek az összege. ||
Hint 2: || Egyetlen bejárásban összegezz, és az utolsó sort, a végállomást ne számold bele, így az útközbeni megállók várakozását kapod. Az eredmény egyetlen szám. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    long long osszes = 0;
    for (int i = 0; i < n; i++) {
        long long tav, erk, ind;
        cin >> tav >> erk >> ind;
        if (i < n - 1) {
            osszes += ind - erk;
        }
    }
    cout << osszes << '\n';
    return 0;
}
