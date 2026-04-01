#include <bits/stdc++.h>
using namespace std;

/*
    A nagyobb négyzetekkel való mohó lefedés a téglalap kisebbik oldalának
    egymás utáni levágása, vagyis a klasszikus euklideszi algoritmus számlált
    változata. Az azonos méretű négyzetekhez a legnagyobb közös osztó oldalú
    négyzetek adnak minimumot.
*/

static long long greedy(long long a, long long b) {
    long long cnt = 0;
    while (a && b) {
        if (a < b) swap(a, b);
        cnt += a / b;
        a %= b;
    }
    return cnt;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long a, b;
    cin >> a >> b;
    long long g = std::gcd(a, b);
    cout << greedy(a, b) << '\n' << (a / g) * (b / g) << '\n';
    return 0;
}