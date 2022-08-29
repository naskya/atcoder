// https://gist.github.com/naskya/1e5e5cd269cfe16a76988378a60e2ca3
// last update: 2022-08-03

#ifndef DEBUG_PRINT_HPP
#define DEBUG_PRINT_HPP

#define INCLUDED(n) ((defined _GLIBCXX_##n) || (defined _LIBCPP_##n))

#if __cplusplus < 201703L
#  warning Please use C++17 (or later version).
#endif
#if !INCLUDED(ALGORITHM)
#  warning Please include <algorithm> before including debug_print.hpp.
#endif
#if !INCLUDED(CCTYPE)
#  warning Please include <cctype> before including debug_print.hpp.
#endif
#if !INCLUDED(IOSTREAM)
#  warning Please include <iostream> before including debug_print.hpp.
#endif
#if !INCLUDED(ITERATOR)
#  warning Please include <iterator> before including debug_print.hpp.
#endif
#if !INCLUDED(STRING_VIEW)
#  warning Please include <string_view> before including debug_print.hpp.
#endif
#if !INCLUDED(TYPE_TRAITS)
#  warning Please include <type_traits> before including debug_print.hpp.
#endif

namespace debug_print {
  std::ostream& os = std::cerr;

  namespace color {
    template <bool> constexpr std::string_view gray;
    template <bool> constexpr std::string_view cyan;
    template <bool> constexpr std::string_view reset;

    template <> constexpr std::string_view gray<true>  = "\x1b[36m";
    template <> constexpr std::string_view cyan<true>  = "\x1b[90m";
    template <> constexpr std::string_view reset<true> = "\x1b[0m";

    template <> constexpr std::string_view gray<false>  = "";
    template <> constexpr std::string_view cyan<false>  = "";
    template <> constexpr std::string_view reset<false> = "";
  }

  template <class Tp> auto has_cbegin(int)     -> decltype(std::cbegin(std::declval<Tp>()), std::true_type {});
  template <class Tp> auto has_cbegin(...)     -> std::false_type;
  template <class Tp> auto has_value_type(int) -> decltype(std::declval<typename Tp::value_type>(), std::true_type {});
  template <class Tp> auto has_value_type(...) -> std::false_type;

  template <class Tp>[[maybe_unused]] constexpr bool is_iterable_container_v = decltype(has_cbegin<Tp>(int {}))::value;
  template <class Tp>[[maybe_unused]] constexpr bool is_container_v          = decltype(has_value_type<Tp>(int {}))::value
                                                                               || is_iterable_container_v<Tp>;

  template <>        [[maybe_unused]] constexpr bool is_iterable_container_v<std::string_view> = false;
  template <>        [[maybe_unused]] constexpr bool is_container_v<std::string_view>          = false;
#if INCLUDED(STRING)
  template <>        [[maybe_unused]] constexpr bool is_iterable_container_v<std::string>      = false;
  template <>        [[maybe_unused]] constexpr bool is_container_v<std::string>               = false;
#endif

  template <class Tp, class... Ts> struct first_element { using type = Tp; };
  template <class... Ts> using first_t = typename first_element<Ts...>::type;

  template <class Tp, std::enable_if_t<!decltype(has_value_type<Tp>(int {}))::value, std::nullptr_t> = nullptr>
    auto check_elem(int) -> decltype(*std::cbegin(std::declval<Tp>()));
  template <class Tp, std::enable_if_t<decltype(has_value_type<Tp>(int {}))::value, std::nullptr_t> = nullptr>
    auto check_elem(int) -> typename Tp::value_type;
  template <class Tp>
    auto check_elem(...) -> void;

  template <class Tp> using elem_t = decltype(check_elem<Tp>(int {}));

  template <class Tp> [[maybe_unused]] constexpr bool is_multidim_container_v = is_container_v<Tp>
                                                                                && is_container_v<elem_t<Tp>>;

  template <bool, class Tp> std::enable_if_t<!is_container_v<Tp>> out(const Tp&);
  template <bool> void out(const char&);
  template <bool> void out(const char*);
  template <bool> void out(const std::string_view&);

#if INCLUDED(STRING)
  template <bool> void out(const std::string&);
#endif

#ifdef __SIZEOF_INT128__
  template <bool> void out(const __int128&);
  template <bool> void out(const unsigned __int128&);
#endif

  template <bool, class Tp1, class Tp2> void out(const std::pair<Tp1, Tp2>&);

#if INCLUDED(TUPLE)
  template <bool, class... Ts> void out(const std::tuple<Ts...>&);
#endif

#if INCLUDED(STACK)
  template <bool, class... Ts> void out(std::stack<Ts...>);
#endif

#if INCLUDED(QUEUE)
  template <bool, class... Ts> void out(std::queue<Ts...>);
  template <bool, class... Ts> void out(std::priority_queue<Ts...>);
#endif

  template <bool, class C> std::enable_if_t<is_iterable_container_v<C>> out(const C&);

  template <bool, class Tp> std::enable_if_t<!is_container_v<Tp>> out(const Tp& arg) {
    os << arg;
  }

  template <bool UseColor> void out(const char& arg) {
    os << color::gray<UseColor> << '\'' << color::reset<UseColor>
       << arg
       << color::gray<UseColor> << '\'' << color::reset<UseColor>;
  }

  template <bool UseColor> void out(const char* arg) {
    os << color::gray<UseColor> << '\"' << color::reset<UseColor>
       << arg
       << color::gray<UseColor> << '\"' << color::reset<UseColor>;
  }

  template <bool UseColor> void out(const std::string_view& arg) {
    os << color::gray<UseColor> << '\"' << color::reset<UseColor>
       << arg
       << color::gray<UseColor> << '\"' << color::reset<UseColor>;
  }

#if INCLUDED(STRING)
  template <bool UseColor> void out(const std::string& arg) {
    os << color::gray<UseColor> << '\"' << color::reset<UseColor>
       << arg
       << color::gray<UseColor> << '\"' << color::reset<UseColor>;
  }
#endif

#ifdef __SIZEOF_INT128__
  template <bool> void out(const __int128& arg) {
    int sign = (arg < 0) ? (-1) : 1;
    if (sign == -1)
      os << '-';
    __int128 base = sign;
    while (sign * arg >= sign * base * 10)
      base *= 10;
    while (base) {
      os << static_cast<char>('0' + (arg / base % 10));
      base /= 10;
    }
  }

  template <bool> void out(const unsigned __int128& arg) {
    unsigned __int128 base = 1;
    while (arg >= base * 10)
      base *= 10;
    while (base) {
      os << static_cast<char>('0' + (arg / base % 10));
      base /= 10;
    }
  }
#endif

  template <bool UseColor, class Tp1, class Tp2> void out(const std::pair<Tp1, Tp2>& arg) {
    os << color::gray<UseColor> << '(' << color::reset<UseColor>;
    out<UseColor>(arg.first);
    os << color::gray<UseColor> << ", " << color::reset<UseColor>;
    out<UseColor>(arg.second);
    os << color::gray<UseColor> << ')' << color::reset<UseColor>;
  }

#if INCLUDED(TUPLE)
  template <bool UseColor, class T, std::size_t... Is> void print_tuple(const T& arg, std::index_sequence<Is...>) {
    static_cast<void>(((os << color::gray<UseColor> << (Is == 0 ? "" : ", ") << color::reset<UseColor>
                       , out<UseColor>(std::get<Is>(arg))), ...));
  }

  template <bool UseColor, class... Ts> void out(const std::tuple<Ts...>& arg) {
    os << color::gray<UseColor> << '(' << color::reset<UseColor>;
    print_tuple<UseColor>(arg, std::make_index_sequence<sizeof...(Ts)>());
    os << color::gray<UseColor> << ')' << color::reset<UseColor>;
  }
#endif

#if INCLUDED(STACK)
  template <bool UseColor, class... Ts> void out(std::stack<Ts...> arg) {
    if (arg.empty()) {
      os << color::gray<UseColor> << '<' << color::reset<UseColor>
         << "empty stack"
         << color::gray<UseColor> << '>' << color::reset<UseColor>
         << '\n';
      return;
    }
    os << color::gray<UseColor> << "[ " << color::reset<UseColor>;
    while (!arg.empty()) {
      out<UseColor>(arg.top());
      os << ' ';
      arg.pop();
    }
    os << color::gray<UseColor> << ']' << color::reset<UseColor>;
  }
#endif

#if INCLUDED(QUEUE)
  template <bool UseColor, class... Ts> void out(std::queue<Ts...> arg) {
    if (arg.empty()) {
      os << color::gray<UseColor> << '<' << color::reset<UseColor>
         << "empty queue"
         << color::gray<UseColor> << '>' << color::reset<UseColor>
         << '\n';
      return;
    }
    os << color::gray<UseColor> << "[ " << color::reset<UseColor>;
    while (!arg.empty()) {
      out<UseColor>(arg.front());
      os << ' ';
      arg.pop();
    }
    os << color::gray<UseColor> << ']' << color::reset<UseColor>;
  }
  template <bool UseColor, class... Ts> void out(std::priority_queue<Ts...> arg) {
    if (arg.empty()) {
      os << color::gray<UseColor> << '<' << color::reset<UseColor>
         << "empty priority_queue"
         << color::gray<UseColor> << '>' << color::reset<UseColor>
         << '\n';
      return;
    }
    os << color::gray<UseColor> << "[ " << color::reset<UseColor>;
    while (!arg.empty()) {
      out<UseColor>(arg.top());
      os << ' ';
      arg.pop();
    }
    os << color::gray<UseColor> << ']' << color::reset<UseColor>;
  }
#endif

  template <bool UseColor, class Container>
  std::enable_if_t<is_iterable_container_v<Container>> out(const Container& arg) {
    os << color::gray<UseColor> << "[ " << color::reset<UseColor>;
    std::for_each(std::cbegin(arg), std::cend(arg), [](const elem_t<Container>& elem) {
      out<UseColor>(elem);
      os << ' ';
    });
    os << color::gray<UseColor> << ']' << color::reset<UseColor>;
  }

  template <bool UseColor, bool Indent, std::size_t IndentWidth, class Tp> std::enable_if_t<!is_multidim_container_v<Tp>>
  print(std::string_view name, const Tp& arg) {
    for (std::size_t i = 0; i < Indent * IndentWidth; ++i)
      os << ' ';
    os << color::cyan<UseColor> << name << ": " << color::reset<UseColor>;
    out<UseColor>(arg);
    if constexpr (is_container_v<Tp>)
      os << '\n';
  }

  template <bool UseColor, bool Indent, std::size_t IndentWidth, class Tp> std::enable_if_t<is_multidim_container_v<Tp>>
  print(std::string_view name, const Tp& arg) {
    for (std::size_t i = 0; i < (Indent * IndentWidth); ++i)
      os << ' ';
    os << color::cyan<UseColor> << name << ": " << color::reset<UseColor>;
    if (std::distance(std::cbegin(arg), std::cend(arg)) == 0) {
      os << color::gray<UseColor> << '<' << color::reset<UseColor>
         << "empty multidimensional container"
         << color::gray<UseColor> << '>' << color::reset<UseColor>
         << '\n';
      return;
    }
    std::for_each(std::cbegin(arg), std::cend(arg),
      [&name, is_first_elem = true](const elem_t<Tp>& elem) mutable {
        if (is_first_elem)
          is_first_elem = false;
        else
          for (std::size_t i = 0; i < name.length() + IndentWidth + 2; ++i)
            os << ' ';
        out<UseColor>(elem);
        os << '\n';
    });
  }

  template <bool UseColor, bool Indent, std::size_t IndentWidth, class Tp, class... Ts>
  void multi_print_impl(std::string_view names, const Tp& arg, const Ts&... args) {
    if constexpr (sizeof...(Ts) == 0) {
      names.remove_suffix(
        std::distance(
          names.crbegin(),
          std::find_if_not(names.crbegin(), names.crend(),
                           [](const char c) { return std::isspace(c); })
        )
      );
      print<UseColor, Indent, IndentWidth>(names, arg);
      if constexpr (!is_container_v<Tp>)
        os << '\n';
    } else {
      std::size_t comma_pos = 0;

      for (std::size_t i = 0, paren_depth = 0, inside_quote = false; i < names.length(); ++i) {
        if (!inside_quote && paren_depth == 0 && i > 0 && names[i - 1] != '\'' && names[i] == ',') {
          comma_pos = i;
          break;
        }
        if (names[i] == '\"' || names[i] == '\'') {
          if (i > 0 && names[i - 1] == '\\') continue;
          inside_quote ^= true;
        }
        if (!inside_quote && names[i] == '(' && (i == 0 || names[i - 1] != '\''))
          ++paren_depth;
        if (!inside_quote && names[i] == ')' && (i == 0 || names[i - 1] != '\''))
          --paren_depth;
      }

      const std::size_t first_varname_length = comma_pos - std::distance(
        names.crend() - comma_pos,
        std::find_if_not(
          names.crend() - comma_pos, names.crend(),
          [](const char c) { return std::isspace(c); }
        )
      );
      print<UseColor, Indent, IndentWidth>(names.substr(0, first_varname_length), arg);

      const std::size_t next_varname_begins_at = std::distance(
        names.cbegin(),
        std::find_if_not(
          names.cbegin() + comma_pos + 1, names.cend(),
          [](const char c) { return std::isspace(c); }
        )
      );
      names.remove_prefix(next_varname_begins_at);

      if constexpr (!is_container_v<Tp>) {
        if constexpr (is_container_v<first_t<Ts...>>) {
          os << '\n';
          multi_print_impl<UseColor, true, IndentWidth>(names, args...);
        } else {
          os << color::gray<UseColor> << " | " << color::reset<UseColor>;
          multi_print_impl<UseColor, false, IndentWidth>(names, args...);
        }
      } else {
        multi_print_impl<UseColor, true, IndentWidth>(names, args...);
      }
    }
  }

  template <bool UseColor = false, std::size_t IndentWidth = 0, class... Ts>
  void multi_print(std::string_view names, const Ts&... args) {
    multi_print_impl<UseColor, false, IndentWidth>(names, args...);
  }
}  // namespace debug_print

#undef INCLUDED

#endif  // DEBUG_PRINT_HPP

