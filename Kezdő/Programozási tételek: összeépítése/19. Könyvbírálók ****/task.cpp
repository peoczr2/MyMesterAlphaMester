/*
Megoldás lényege:
Egy könyv két olvasása nem eshet egyszerre, ezért az i. könyv elolvasása legalább A_i + B_i időt igényel. A fontos könyvek (az első K) sorrendi feltétele miatt ezek olvasása láncba fűződik, így az első K könyv A_i + B_i összegeinek összege alsó korlát. Mindkét bíráló összes munkaideje is alsó korlát (ΣA és ΣB), és egyetlen könyv két olvasása is legalább A_j + B_j időt vesz igénybe. A négy alsó korlát maximuma elérhető: a nem fontos könyvek a fontos láncban keletkező szabad időkbe illeszthetők, ezért a válasz e négy érték maximuma. A megoldás egyetlen menetben kiszámolja az értékeket, az időigény O(N).
*/
/*
Hint 1: || Egy könyvet a két bíráló nem olvashat egyszerre, ezért egy könyv két olvasása összesen legalább A_i + B_i időt igényel. ||
Hint 2: || A fontos könyvek sorrendi feltétele miatt az első K könyv olvasása egymás után következik. Gondold végig, miért nem lehet ennek összideje kisebb az A_i + B_i összegek összegénél. ||
Hint 3: || További alsó korlát mindkét bíráló összes munkaideje (ΣA, ΣB), és a legnagyobb egyedi A_i + B_i. A válasz e négy érték maximuma. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    vector<long long> a(n), b(n);
    for (int i = 0; i < n; i++) cin >> a[i] >> b[i];

    long long sumA = 0, sumB = 0, lanc = 0, legnagyobb = 0;
    for (int i = 0; i < n; i++) {
        sumA += a[i];
        sumB += b[i];
        legnagyobb = max(legnagyobb, a[i] + b[i]);
        if (i < k) lanc += a[i] + b[i];
    }

    cout << max({sumA, sumB, lanc, legnagyobb}) << "\n";
    return 0;
}
