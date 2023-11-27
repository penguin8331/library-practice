#include "../template/template.hpp"

struct RMQ {
    int N;
    vector<int> dat;
    int SIZE_R;
    RMQ(int _N, vector<int> v) : N(_N) {
        SIZE_R = 1;
        while (SIZE_R < N) SIZE_R *= 2;
        dat.assign(SIZE_R * 2, inf);
        for (int i = 0; i < N; i++) {
            dat[i + SIZE_R] = v[i];
        }
        for (int i = SIZE_R - 1; i >= 0; i--) {
            dat[i] = min(dat[i * 2], dat[i * 2 + 1]);
        }
    }
    int get(int l, int r) { return get(l, r, 1, 0, SIZE_R); }
    int get(int l, int r, int k, int a, int b) {
        if (l <= a && b <= r) {
            return dat[k];
        }
        if (a == b || l >= b || r <= a) return inf;
        return min(get(l, r, k * 2, a, (a + b) / 2),
                   get(l, r, k * 2 + 1, (a + b) / 2, b));
    }
    void update(int idx, int v) {
        idx += SIZE_R;
        dat[idx] = v;
        while (idx >>= 1) {
            dat[idx] = min(dat[idx * 2], dat[idx * 2 + 1]);
        }
    }
};
int main() {
    RMQ rmq(4, {1, 3, 7, 5});
    print(rmq.dat);
    rmq.update(2, 2);
    print(rmq.dat);
    print(rmq.get(1, 3));
}