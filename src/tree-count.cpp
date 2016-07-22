#include <cstring>
#include <iostream>

#define rep_(i, from, to) for(int i = (from); i <= (to); i ++)

const int MOD = 65521;

long long N;
int K;

long long coeffs[][50] = {
        {},
        {},
        {3, 65520},
        {5, 65518, 3,     65516, 1},
        {7, 65520, 65496, 31,    65469, 65437, 300,   65437, 65469, 31,    65496, 65520, 7,     65520},
        {8, 5,     65489, 40,    364,   63172, 62845, 2793,  7304,  50170, 14272, 13974, 32712, 27590, 63226, 30516, 31431, 62449, 44809, 2992, 62529, 20712, 3072, 34090, 35005, 2295, 37931, 32809, 51547, 51249, 15351, 58217, 62728, 2676, 2349, 65157, 65481, 32, 65516, 65513, 1}
};

long long initials[][50] = {
        {},
        {},
        {0, 1},
        {0, 0, 3, 16, 75},
        {0, 0, 0, 16, 125, 864,  5635,  35840, 29517, 48795, 64376, 52310, 4486,  28336},
        {0, 0, 0, 0,  125, 1296, 12005, 38927, 26915, 65410, 9167,  63054, 58705, 18773, 9079, 38064, 46824, 48121, 50048, 47533, 30210, 24390, 51276, 45393, 357, 44927, 15398, 15923, 31582, 56586, 25233, 41258, 21255, 21563, 16387, 39423, 26418, 10008, 6962, 42377, 50881}
};

int ns[] = {0, 0, 2, 5, 14, 41};

struct mat {
    long long x[50][50];

    mat() {
        memset(x, 0, sizeof(x));
    }
};

mat operator*(const mat &A, const mat &B) {
    mat X;
    rep_(i, 1, ns[K])
        rep_(j, 1, ns[K])
            rep_(k, 1, ns[K]) {
                X.x[i][k] += A.x[i][j] * B.x[j][k];
                X.x[i][k] %= MOD;
            }
    return X;
}

inline mat make_id() {
    mat X;
    rep_(i, 1, ns[K]) X.x[i][i] = 1;
    return X;
}

inline mat make_one() {
    mat X;
    rep_(i, 1, ns[K]) X.x[ns[K]][i] = coeffs[K][ns[K] - i];
    rep_(i, 1, ns[K] - 1) X.x[i][i + 1] = 1;
    return X;
}

inline mat mat_pow(const mat &A, long long M) {
    mat Ans = make_id(), Cur = A;
    for (; M; M >>= 1) {
        if (M & 1) Ans = Ans * Cur;
        Cur = Cur * Cur;
    }
    return Ans;
}

inline long long get_answer() {
    mat x = mat_pow(make_one(), N - 1);

    long long Mu = 0;
    rep_(i, 1, ns[K])
        Mu = (Mu + x.x[1][i] * initials[K][i - 1]) % MOD;

    return Mu;
}

int main() {
    std::cin >> K >> N;
    if(K == 1) std::cout << 1;
    else std::cout << get_answer();
    std::cout << std::endl;
    return 0;
}
