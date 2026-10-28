/*
Megoldás lényege:
A kérdés csak arra vonatkozik, hány jármű haladt át az egyes megfigyelési helyeken, ezért az időpontokat nem kell feldolgozni. Minden helyhez tartunk egy számlálót: minden adatsornál a megfelelő hely számlálóját eggyel növeljük. A végén az 1-től M-ig tartó helyeket egy menetben bejárjuk, és a legnagyobb számlálót keressük; szigorú összehasonlítással a kisebb sorszámú hely marad. Az időigény O(N + M), a memóriaigény O(M).
*/
/*
Hint 1: || A kérdés csak az egyes helyeken áthaladó járművek számát kéri, az időpont ehhez nem kell. ||
Hint 2: || Tarts számlálót minden megfigyelési helyhez, minden adatsornál a hely számlálóját növeld eggyel, majd az 1-től M-ig tartó helyeket bejárva keresd a legnagyobb számlálót. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int m, n;
    cin >> m >> n;

    vector<int> count(m + 1, 0);
    for (int i = 0; i < n; i++) {
        int station, hour, minute;
        cin >> station >> hour >> minute;
        count[station]++;
    }

    int bestStation = 1;
    int bestCount = -1;
    for (int s = 1; s <= m; s++) {
        if (count[s] > bestCount) {
            bestCount = count[s];
            bestStation = s;
        }
    }

    cout << bestStation << " " << bestCount << "\n";
    return 0;
}
