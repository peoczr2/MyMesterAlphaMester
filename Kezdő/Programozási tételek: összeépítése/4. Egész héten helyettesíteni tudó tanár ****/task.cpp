/*
Megoldás lényege:
A T tanár óráit (nap, óra) időpontokként gyűjtjük. Egy S tanár akkor helyettesítheti T-t egész héten, ha ezeken az
időpontokon nincs órája. Elsőbbséget élvez az a helyettes, aki minden olyan napon tanít, amelyen T is tanít, mert így
nem kell behívni a szabad napján. A tanárok foglalt időpontjait és tanítási napjait halmazban tároljuk, így az ellenőrzések
gyorsak. A tanárokat sorszám szerint növekvően járjuk be, így az első találat már a legkisebb sorszámú. Ha nincs ilyen
tanár, a feltétel nélkül szabad legkisebb sorszámút írjuk ki, és -1-et, ha egyik sem szabad. Az időigény O(N * O_T * log O).
*/
/*
Hint 1: || Két feltételt kell kezelni: a helyettes minden T-óráján legyen szabad, és lehetőleg minden olyan napon tanítson, amelyen T tanít. ||
Hint 2: || Minden tanárhoz tárolj egy halmazt a foglalt (nap, óra) párokról és egy halmazt a tanítási napokról; így a szabadság és a napok ellenőrzése gyors. ||
Hint 3: || Sorszám szerint haladj végig a tanárokon (T-t kihagyva), és az első olyan tanárt jegyezd fel, aki szabad T óráin és tanít T minden napján. Ha ilyen nincs, a feltétel nélkül szabad legkisebb sorszámút kell kiírni. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int lessons, teachers, subjects, t;
    cin >> lessons >> teachers >> subjects >> t;

    // busy[tanár] = a tanár által tartott (nap, óra) időpontok
    // workDays[tanár] = azok a napok, amelyeken a tanárnak van órája
    vector<set<pair<int, int>>> busy(teachers + 1);
    vector<set<int>> workDays(teachers + 1);
    for (int i = 0; i < lessons; i++) {
        int teacher, subject, day, hour;
        cin >> teacher >> subject >> day >> hour;
        busy[teacher].insert({day, hour});
        workDays[teacher].insert(day);
    }

    int firstFree = -1; // legkisebb sorszámú, T óráin szabad tanár
    int firstBest = -1; // legkisebb sorszámú, T óráin szabad és T minden napján tanító tanár
    for (int s = 1; s <= teachers; s++) {
        if (s == t) continue;

        bool free = true;
        for (const auto& slot : busy[t]) {
            if (busy[s].count(slot)) {
                free = false;
                break;
            }
        }
        if (!free) continue;

        if (firstFree == -1) firstFree = s;
        // T minden tanítási napján S is tanít: nem kell behívni a szabad napján
        if (includes(workDays[s].begin(), workDays[s].end(), workDays[t].begin(), workDays[t].end())) {
            firstBest = s;
            break;
        }
    }

    int answer = (firstBest != -1) ? firstBest : firstFree;
    cout << answer << '\n';
    return 0;
}
