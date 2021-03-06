#include <bits/stdc++.h>
using namespace std;
#define i64 int64_t
#define all(a) a.begin(),a.end()
#define rep(n) for(int i = 0; i < (n); i++)

constexpr int maxn = 1 << 20;
i64 hilbertorder(int x, int y) {
  i64 rx, ry, d = 0;
  for (i64 s=maxn>>1; s; s>>=1) {
    rx = (x & s)>0, ry = (y & s)>0;
    d += s * s * ((rx * 3) ^ ry);
    if (ry) continue;
    if (rx) {
      x = maxn-1 - x;
      y = maxn-1 - y;
    }
    swap(x, y);
  }
  return d;
}

struct Mo {
private:
  int q = 0;
  vector<int> l, r;
public:
  void insert(int l_, int r_) {
    q++;
    l.emplace_back(l_);
    r.emplace_back(r_);
  }

  // F1~F5: lambda関数
  template<typename F1, typename F2, typename F3, typename F4, typename F5>
  void execute(F1 &&add_l, F2 &&add_r, F3 &&del_l, F4 &&del_r, F5 &&solve) {
    vector<int> qi(q);
    iota(all(qi), 0);
    vector<i64> eval(q);
    rep (q) eval[i] = hilbertorder(l[i], r[i]);
    sort(all(qi), [&](int i, int j) {
      return eval[i] < eval[j];
    });
    int nl = 0, nr = 0;
    for (int i: qi) {
      while (nl > l[i]) add_l(--nl);
      while (nr < r[i]) add_r(nr++);
      while (nl < l[i]) del_l(nl++);
      while (nr > r[i]) del_r(--nr);
      solve(i);
    }
  }
};