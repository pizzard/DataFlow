/*
 * traits.h
 *
 *  Created on: 23.02.2015
 *      Author: Caspar
 */

#ifndef CORE_TRAITS_H_
#define CORE_TRAITS_H_

#include <type_traits>
#include <functional>

// is_callable trait from talesofcpp.fusionfenix.com
namespace detail {
  template <typename T>
  using always_void = void;

  template <typename Expr, typename Enable = void>
  struct is_callable_impl
    : std::false_type
  {};

  template <typename F, typename ...Args>
  struct is_callable_impl<F(Args...), always_void<std::result_of<F(Args...)>>>
    : std::true_type
  {};
}

template <typename Expr>
struct is_callable
{
	typedef typename detail::is_callable_impl<Expr> value;
};


//has_connect trait to check if a parameter has a connect member method
template<typename> struct Void { typedef void type; };
template <class T, class P, class Sfinae_default = void>
struct has_connect: std::false_type {};

template <class T, class P>
struct has_connect<T, P, typename Void<
	decltype(std::declval<T&>().connect((std::declval<P&>())))>
	::type>
	: std::true_type {};

template <class T, class P, class Sfinae_default = void>
struct has_signal_connect: std::false_type {};

template <class T, class P>
struct has_signal_connect<T, P, typename Void<
	typename std::enable_if<
	std::is_same<decltype(std::declval<T&>().connect((std::declval<P&>()))), boost::signals2::connection>::value
	>::type>::type>
	: std::true_type {};
//
//template <class T, class P>
//constexpr auto has_connect(T&& t, P&& p) -> decltype(std::declval<T&>().connect(p), bool()) {
//  return true;
//}
//
//// Used as fallback when SFINAE culls the template method
//template <class T, class P, class Sfinae_default = void>
//constexpr bool has_connect(T&& t, P&& p) { return false; }

#endif /* CORE_TRAITS_H_ */
