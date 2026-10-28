/*
Megoldás lényege:
A legnagyobb korong a döntő. Ha a kezdő- és a célállásban is ugyanazon a tornyon van, nem kell mozgatni, és a kisebb korongokra ugyanezt a problémát oldjuk meg eggyel kisebb méretre. Ha nem, akkor a legnagyobb korongot vagy közvetlenül a-ból b-be visszük (ehhez a kisebbeket a harmadik c toronyra kell gyűjteni), vagy a-ból c-n át b-be (ekkor a kisebbek először b-n, majd a-n gyülekeznek). Mindkét esetben a kisebb korongokat egy rekurzív eljárással gyűjtjük meg egy adott toronyra, a célállás részét pedig ugyanígy gyűjtjük, majd a lépéssorozat megfordítjuk, mert minden lépés visszafelé is érvényes. A kettő közül a rövidebb sorozatot írjuk ki, így a lépésszám minimális, mindig kisebb 2^N-nél, az időigény O(2^N), ami N <= 16 esetén bőven belefér.
*/
/*
Hint 1: || Vizsgáld meg a legnagyobb korongot. Ha a kezdő- és a célállásban is ugyanazon a tornyon van, nem kell mozgatni, és a többi korongra ugyanezt a problémát oldhatod meg eggyel kisebb méretre. Ha nem, a legnagyobb korong kétféleképpen juthat el a céltoronyba: egyszer, vagy kétszer mozogva. ||
Hint 2: || A legnagyobb korong mozgatásakor a két érintett toronyon nem lehet kisebb korong, ezért a kisebbeket a harmadik toronyra kell gyűjtened. Erre írj rekurzív eljárást: az első m korongot egy X toronyra gyűjti. Ha az m-edik korong már X-en van, csak a többit gyűjtsd X-re; ha nincs, a többit a harmadik toronyra gyűjtsd, az m-edik korongot átrakod X-re, majd a többit X-re gyűjtöd. ||
Hint 3: || A célállást ugyanígy gyűjtsd össze, majd a kapott lépéssorozatot fordítsd meg: minden lépés visszafelé is érvényes, ezért a céltorony felé vezető részt a célállásból kapott lépések fordított sorrendjében, a két torony felcserélésével írd ki. Végül a két változat közül a rövidebbet add vissza. ||
*/
#include <bits/stdc++.h>
using namespace std;

// A 1..m méretű korongokat az X toronyra gyűjti. st[k] a k-as korong tornyát tárolja (1..3).
void gather(vector<int>& st, int m, int X, vector<pair<int, int>>& moves) {
    if (m == 0) return;
    int p = st[m];
    if (p == X) {
        gather(st, m - 1, X, moves);
        return;
    }
    int r = 6 - p - X;  // a harmadik torony
    gather(st, m - 1, r, moves);
    moves.push_back({p, X});
    st[m] = X;
    gather(st, m - 1, X, moves);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Minden torony sorát 0 zárja; a sorokban a korongok mérete szerepel.
    vector<pair<int, int>> start, goal;  // (korong mérete, torony)
    for (int t = 1; t <= 3; ++t) {
        int v;
        while (cin >> v && v != 0) start.push_back({v, t});
    }
    for (int t = 1; t <= 3; ++t) {
        int v;
        while (cin >> v && v != 0) goal.push_back({v, t});
    }

    int n = 0;
    for (auto& p : start) n = max(n, p.first);
    vector<int> cur(n + 1, 1), tg(n + 1, 1);
    for (auto& p : start) cur[p.first] = p.second;
    for (auto& p : goal) tg[p.first] = p.second;

    vector<pair<int, int>> moves;
    for (int m = n; m >= 1; --m) {
        int a = cur[m], b = tg[m];
        if (a == b) continue;
        int c = 6 - a - b;

        // 1. változat: a legnagyobb korong egyszer, közvetlenül a -> b.
        vector<pair<int, int>> opt1;
        {
            vector<int> s = cur;
            gather(s, m - 1, c, opt1);
            opt1.push_back({a, b});
            vector<int> t = tg;
            vector<pair<int, int>> back;
            gather(t, m - 1, c, back);
            for (int i = (int)back.size() - 1; i >= 0; --i)
                opt1.push_back({back[i].second, back[i].first});
        }

        // 2. változat: a legnagyobb korong kétszer, a -> c -> b.
        vector<pair<int, int>> opt2;
        {
            vector<int> s = cur;
            gather(s, m - 1, b, opt2);
            opt2.push_back({a, c});
            gather(s, m - 1, a, opt2);
            opt2.push_back({c, b});
            vector<int> t = tg;
            vector<pair<int, int>> back;
            gather(t, m - 1, a, back);
            for (int i = (int)back.size() - 1; i >= 0; --i)
                opt2.push_back({back[i].second, back[i].first});
        }

        moves = opt1.size() <= opt2.size() ? opt1 : opt2;
        break;  // a kisebb korongok ekkor már a célállásban vannak
    }

    string out = to_string(moves.size()) + "\n";
    for (auto& mv : moves) {
        out += to_string(mv.first);
        out += ' ';
        out += to_string(mv.second);
        out += '\n';
    }
    cout << out;
    return 0;
}
