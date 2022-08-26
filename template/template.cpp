#define _USE_MATH_DEFINES

#ifdef LOCAL
#  include <headers.hpp>
#  define M_assert(expr) assert(expr)
#  define O_assert(expr) assert(expr)
#else
#  include <cassert>
#  include <cctype>
#  include <cmath>
#  include <cstddef>
#  include <cstdint>
#  include <cstdlib>
#  include <algorithm>
#  include <array>
#  include <bitset>
#  include <complex>
#  include <deque>
#  include <functional>
#  include <iostream>
#  include <iomanip>
#  include <iterator>
#  include <limits>
#  include <list>
#  include <map>
#  include <numeric>
#  include <queue>
#  include <regex>
#  include <set>
#  include <sstream>
#  include <stack>
#  include <string>
#  include <string_view>
#  include <tuple>
#  include <type_traits>
#  include <tuple>
#  include <utility>
#  include <vector>
#  define M_assert(expr) \
   do { \
     if (__builtin_expect(!(expr), 0)) { \
       auto p = static_cast<std::int64_t*>(std::malloc(1073741824)); \
       for (int i = 0; i < 134217728; p[i] = 1, i += 512); \
       std::cerr << (*p); \
     } \
   } while (0)
#  define O_assert(expr) \
   do { \
     if (__builtin_expect(!(expr), 0)) { \
       const std::string X = std::string(1024, '*'); \
       for(int i = 0; i < 262144; ++i) std::cout << X; \
     } \
   } while (0)
#endif

#ifdef DEBUG
#  define local(...) do { __VA_ARGS__ } while (0)
#  define alter(x, y) x
#else
#  define local(...) static_cast<void>(0)
#  define alter(x, y) y
#endif

#ifdef DEBUG_PRINT
#  define see(...) debug_print::multi_print(#__VA_ARGS__, __VA_ARGS__)
#  define here() debug_print::os << "[Debug] " __FILE__ ":" << __LINE__ << " in " << __func__ << ": \x1b[32mReached\x1b[39m\n"
#  define msg(m) debug_print::os << "[Debug] " __FILE__ ":" << __LINE__ << " in " << __func__ << ": \x1b[32mMessage:\x1b[39m " << m << "\n"
#else
#  define see(...) static_cast<void>(0)
#  define here() static_cast<void>(0)
#  define msg(m) static_cast<void>(0)
#endif

#define rep(var, c) for (auto var = static_cast<decltype(c)>(0); var < c; ++var)
#define rng(var, s, t, inc) \
   for ( \
     auto var = static_cast<std::common_type<decltype(s), decltype(t)>>(s); \
     (inc > 0) ? (var < static_cast<decltype(var)>(t)) : (var > static_cast<decltype(var)>(t)); \
     var += inc \
   )
#define erng(var, s, t, inc) \
   for ( \
     auto var = static_cast<std::common_type<decltype(s), decltype(t)>>(s); \
     (inc > 0) ? (var <= static_cast<decltype(var)>(t)) : (var >= static_cast<decltype(var)>(t)); \
     var += inc \
   )

[[maybe_unused]] constexpr int         INF   = 1000000005;
[[maybe_unused]] constexpr long long   LINF  = 1000000000000000005LL;
[[maybe_unused]] constexpr double      EPS   = 1e-9;
[[maybe_unused]] constexpr long double LEPS  = 1e-14L;
[[maybe_unused]] constexpr int         dy[9] = {1, 0, -1, 0, 1, 1, -1, -1, 0};
[[maybe_unused]] constexpr int         dx[9] = {0, 1, 0, -1, -1, 1, 1, -1, 0};

template <class... Ts> [[nodiscard]] constexpr auto Min(const Ts... args) { return std::min({ static_cast<std::common_type_t<Ts...>>(args) ... }); }
template <class... Ts> [[nodiscard]] constexpr auto Max(const Ts... args) { return std::max({ static_cast<std::common_type_t<Ts...>>(args) ... }); }

{% if yes_str %}
{% if no_str %}
void yes(const bool flag) { std::cout << (flag ? "{{ yes_str }}\n" : "{{ no_str }}\n"); }
{% endif %}
{% endif %}

{% if prediction_success %}
void solve({{ formal_arguments }}) {
  
}
{% else %}
void solve() {
  
}
{% endif %}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout << std::fixed << std::setprecision(15);
{% if prediction_success %}
  {{input_part}}
  solve({{ actual_arguments }});
{% else %}
  solve();
{% endif %}
}

