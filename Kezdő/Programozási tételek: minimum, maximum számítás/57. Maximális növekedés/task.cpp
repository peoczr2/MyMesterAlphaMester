/*
Megoldás lényege:
Rögzített a kezdőnapra a végnap csak addig lehet, amíg K[a] még a szakasz minimuma, vagyis a következő nála kisebb eladású napig (azt nem beleértve). Ezen a tartományon belül a legjobb b a legnagyobb eladású nap (döntetlennél a legkisebb sorszámú), mert így K[b] egyben a [a..b] szakasz maximuma is. A tartomány maximumát jobbról balra haladva, veremmel számoljuk: a verembe kerülő napok tartományai egymás után lefedik a [a+1 .. következő kisebb - 1] részt, így a maximumokat összevonhatjuk. Minden a-ra kiszámoljuk a K[b] - K[a] különbséget, és az első (legkisebb a-jú) legnagyobbat tartjuk meg. Minden nap legfeljebb egyszer kerül a verembe és ki belőle, így az időigény O(N).
*/
/*
Hint 1: || Rögzíts egy a kezdőnapot. Meddig terjedhet a b végnap úgy, hogy K[a] még biztosan a szakasz minimuma legyen? ||
Hint 2: || A rögzített a-hoz tartozó legjobb b az adott tartomány legnagyobb eladású napja. Jobbról balra haladva a "következő kisebb elem" veremmel ezek a maximumok is nyilvántarthatók. ||
Hint 3: || Az összes a-ra kiszámolt különbség közül a legnagyobbat keresd, döntetlennél a kisebb a-t tartsd meg. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> k(n + 1);
    for (int i = 1; i <= n; i++) cin >> k[i];

    // mx[i]: az [i, következő kisebb - 1] tartomány maximumának (legkisebb) indexe
    vector<int> mx(n + 1);
    vector<int> st;  // a következő kisebb elemek láncát tartalmazza
    for (int a = n; a >= 1; a--) {
        int best = a;
        while (!st.empty() && k[st.back()] >= k[a]) {
            int j = mx[st.back()];
            if (k[j] > k[best]) best = j;  // egyenlőnél a korábbi (kisebb indexű) marad
            st.pop_back();
        }
        mx[a] = best;
        st.push_back(a);
    }

    int ansA = 1, ansB = 1, bestDiff = -1;
    for (int a = 1; a <= n; a++) {
        int diff = k[mx[a]] - k[a];
        if (diff > bestDiff) {
            bestDiff = diff;
            ansA = a;
            ansB = mx[a];
        }
    }
    cout << ansA << " " << ansB << "\n";
    return 0;
}
