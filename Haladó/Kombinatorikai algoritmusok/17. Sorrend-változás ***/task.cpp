/*
Megoldás lényege:
Egy sorrend akkor felel meg, ha minden csapat legfeljebb egy hellyel mozdul, vagyis a sorrend egymást nem fedő szomszédos (i, i+1) cserékből áll. Az első helyen vagy az 1-es áll (utána N-1 csapat következik), vagy a 2-es, amit az 1-es követ (utána N-2 csapat), így az N hosszú sorrendek száma f(N) = f(N-1) + f(N-2), azaz Fibonacci-szám. A sorrendeket visszalépéses bejárással írjuk ki: a legkisebb még nem elhelyezett csapat vagy helyben marad, vagy a következővel cserél. Mivel a helyben maradás a kisebb elemet teszi előre, a bejárás lexikografikus sorrendben adja a megoldásokat. A kimenet mérete O(M*N), ahol M a sorrendek száma (N<=25 esetén legfeljebb 121393), ezért a sorokat egy pufferbe gyűjtjük és egyszerre írjuk ki.
*/
/*
Hint 1: || Írd le a sorrendeket párok cseréivel: egy csapat legfeljebb egy hellyel mozdulhat, így minden csere két szomszédos csapat között történik, és ezek a cserék nem fedhetik egymást. ||
Hint 2: || Készíts rekurziót az N hosszú sorrendek számára: az első helyen vagy az 1-es áll, vagy a 2-es és utána az 1-es; így a darabszám Fibonacci-szám, amit kiírás előtt kiszámolhatsz. ||
Hint 3: || A kiíráshoz visszalépéses bejárást használj: a legkisebb még nem elhelyezett csapatot először helyben hagyva, majd a következővel cserélve próbáld ki, így a sorrend lexikografikus lesz. A sorokat pufferben gyűjtsd, és egyszerre írd ki. ||
*/
#include <bits/stdc++.h>
using namespace std;

int N;
vector<int> cur;
string out;

void gen(int pos) {
    if (pos > N) {
        for (int i = 0; i < (int)cur.size(); ++i) {
            if (i) out += ' ';
            if (cur[i] >= 10) out += char('0' + cur[i] / 10);
            out += char('0' + cur[i] % 10);
        }
        out += '\n';
        return;
    }
    cur.push_back(pos);
    gen(pos + 1);
    cur.pop_back();
    if (pos < N) {
        cur.push_back(pos + 1);
        cur.push_back(pos);
        gen(pos + 2);
        cur.pop_back();
        cur.pop_back();
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N;
    vector<unsigned long long> fib(N + 2, 0);
    fib[0] = fib[1] = 1;
    for (int i = 2; i <= N + 1; ++i) fib[i] = fib[i - 1] + fib[i - 2];
    unsigned long long total = fib[N];
    out.reserve((size_t)total * (3 * N + 1) + 32);
    out += to_string(total) + '\n';
    gen(1);
    cout << out;
    return 0;
}
