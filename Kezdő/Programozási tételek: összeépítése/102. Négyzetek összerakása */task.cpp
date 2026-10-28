/*
Megoldás lényege:
Mindig a még ki nem rakott egységnégyzetekből kirakható legnagyobb négyzetet vesszük. Ha r egységnégyzet maradt, a legnagyobb k egész, amelyre k*k <= r, és ezt a k-t kiírjuk, majd r-ből levonjuk k*k-t. Ezt addig ismételjük, amíg a maradék el nem fogy. A kiírt oldalhosszak nem nőnek: a k-val kirakott négyzet után a maradék legfeljebb 2k lesz, így a következő négyzet oldala sem lehet nagyobb k-nál. Mivel a maradék minden lépésben nagyjából négyzetgyökre csökken, a lépések száma nagyon kicsi, a futási idő elhanyagolható.
*/
/*
Hint 1: || Mindig a még ki nem rakott egységnégyzetekből a lehető legnagyobb négyzetet kell kirakni, és ezt addig ismételni, amíg el nem fogy a maradék. ||
Hint 2: || Egy r maradéknál keresd a legnagyobb olyan k egészet, amelyre k*k <= r. Érdemes gyökvonással becsülni, majd egész számokkal igazítani k értékét, mert a lebegőpontos gyök kerekítési hibát okozhat. ||
*/
#include <bits/stdc++.h>
using namespace std;

long long legnagyobbOldal(long long r) {
    long long k = (long long)sqrtl((long double)r);
    while (k * k > r) --k;
    while ((k + 1) * (k + 1) <= r) ++k;
    return k;
}

int main() {
    long long n;
    cin >> n;

    bool elso = true;
    while (n > 0) {
        long long k = legnagyobbOldal(n);
        if (!elso) cout << ' ';
        cout << k;
        elso = false;
        n -= k * k;
    }
    cout << '\n';
    return 0;
}
