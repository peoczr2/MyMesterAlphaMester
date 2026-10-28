/*
Megoldás lényege: az intervallum-aritmetika szabályait alkalmazzuk: a művelet eredményének alsó és felső határát az X és Y megfelelő határaiból számoljuk. Összeadásnál az alsó határok összege adja az eredmény alsó, a felső határok összege a felső határát; kivonásnál az alsó határ X alsó határa mínusz Y felső határa, a felső határ X felső határa mínusz Y alsó határa. Mivel a számok pozitívak, szorzásnál a megfelelő határok szorzata adja az új határokat. Minden törtet a két nevező szorzatával számolunk, majd a számláló és nevező legnagyobb közös osztójával egyszerűsítünk; a műveletek száma állandó, így az időigény O(1).
*/
/*
Hint 1: || A határok törtek, ezért mindhárom műveletnél két külön törtet kell kiszámolni: az eredmény alsó és felső határát. ||
Hint 2: || Összeadásnál az alsó határok összege és a felső határok összege adja az új határokat; szorzásnál a megfelelő határok szorzata; kivonásnál az eredmény alsó határa X alsó határa mínusz Y felső határa, a felső határa X felső határa mínusz Y alsó határa. ||
Hint 3: || Két tört összeadásánál a/b + c/d = (a * d + c * b) / (b * d); a kapott törtet a számláló és a nevező legnagyobb közös osztójával egyszerűsítsd, a 0 pedig 0/1 alakban jelenjen meg. ||
*/
#include <bits/stdc++.h>
using namespace std;

struct Tort {
    long long sz, nev;
};

Tort egyszerusit(long long sz, long long nev) {
    long long g = std::gcd(sz, nev);
    return {sz / g, nev / g};
}

int main() {
    long long xa, xb, xc, xd;  // X alsó határa xa/xb, felső határa xc/xd
    long long ya, yb, yc, yd;  // Y alsó határa ya/yb, felső határa yc/yd
    cin >> xa >> xb >> xc >> xd;
    cin >> ya >> yb >> yc >> yd;

    Tort osszAlso = egyszerusit(xa * yb + ya * xb, xb * yb);
    Tort osszFelso = egyszerusit(xc * yd + yc * xd, xd * yd);
    Tort kulAlso = egyszerusit(xa * yd - yc * xb, xb * yd);
    Tort kulFelso = egyszerusit(xc * yb - ya * xd, xd * yb);
    Tort szorAlso = egyszerusit(xa * ya, xb * yb);
    Tort szorFelso = egyszerusit(xc * yc, xd * yd);

    cout << osszAlso.sz << " " << osszAlso.nev << " " << osszFelso.sz << " " << osszFelso.nev << "\n";
    cout << kulAlso.sz << " " << kulAlso.nev << " " << kulFelso.sz << " " << kulFelso.nev << "\n";
    cout << szorAlso.sz << " " << szorAlso.nev << " " << szorFelso.sz << " " << szorFelso.nev << "\n";
    return 0;
}
