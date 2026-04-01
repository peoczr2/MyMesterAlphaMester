/*
Megoldás lényege:
Egy ember akkor tér el minden más embertől legalább egy szabadnapban, ha nincs olyan másik ember,
akinek a szabadnaphalmaza tartalmazza az övét. Vagyis azokat kell megszámolni, akiknek a halmaza
maximális a részhalmaz-rendezésben, és nincs vele azonos másik halmaz sem.

Mivel legfeljebb 61 nap van, minden halmaz egy 64 bites maszkba kódolható. Ezután két ember között
az A részhalmaza B-nek kérdés egyetlen bitművelettel eldönthető: (A & B) == A. Az összes pár vizsgálata
N<=5000 mellett bőven belefér.
*/
/*
Hint 1: || A feltétel tagadása: van valaki más, akinek minden te szabadnapod szintén szabadnapja. ||
Hint 2: || Legfeljebb 61 nap esetén a szabadnaphalmaz kényelmesen elfér egy 64 bites maszkon. ||
Hint 3: || Egy maszk részhalmaza a másiknak pontosan akkor, ha az AND visszaadja az első maszkot. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<unsigned long long> masks(n, 0);
    for (int i = 0; i < n; ++i) {
        int count;
        cin >> count;
        for (int j = 0; j < count; ++j) {
            int day;
            cin >> day;
            masks[i] |= 1ULL << (day - 1);
        }
    }

    int answer = 0;
    for (int i = 0; i < n; ++i) {
        bool good = true;
        for (int j = 0; j < n; ++j) {
            if (i == j) {
                continue;
            }
            if ((masks[i] & masks[j]) == masks[i]) {
                good = false;
                break;
            }
        }
        answer += good;
    }

    cout << answer << '\n';
    return 0;
}