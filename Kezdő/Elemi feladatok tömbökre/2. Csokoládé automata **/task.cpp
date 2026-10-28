/*
Megoldás lényege:
Mivel legfeljebb három érmét használhatunk, és a cél a minimális érmeszám, elég sorban megnézni az egy, a két és a három érmés fizetési lehetőségeket. Az első találat már a legkevesebb érmével fizet, ezért azonnal kiírható. A két- és háromérmés kombinációkat i < j < k indexekkel kell bejárni, hogy ugyanazt az érmét ne használjuk kétszer. Az N ≤ 100 miatt a háromszoros ciklus kb. 161 700 kombinációt jelent, ami az időkorláton belül van. Ha egyik lehetőség sem adja ki az árat, a kimenet „NEM LEHET”.
*/
/*
Hint 1: || Próbáld sorban az egy érmés, a két érmés, végül a három érmés lehetőségeket: az első találat már a minimális érmeszámmal fizet. ||
Hint 2: || A kombinációkat három egymásba ágyazott ciklussal válaszd ki úgy, hogy i < j < k legyen, így ugyanazt az érmét nem használod kétszer. Ha egyik sem találat, a kimenet NEM LEHET ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int ar, n;
    cin >> ar >> n;
    vector<int> e(n);
    for (int &x : e) cin >> x;

    // 1 érme
    for (int i = 0; i < n; i++) {
        if (e[i] == ar) {
            cout << e[i] << "\n";
            return 0;
        }
    }

    // 2 érme
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (e[i] + e[j] == ar) {
                cout << e[i] << " " << e[j] << "\n";
                return 0;
            }
        }
    }

    // 3 érme
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            for (int k = j + 1; k < n; k++) {
                if (e[i] + e[j] + e[k] == ar) {
                    cout << e[i] << " " << e[j] << " " << e[k] << "\n";
                    return 0;
                }
            }
        }
    }

    cout << "NEM LEHET\n";
    return 0;
}
