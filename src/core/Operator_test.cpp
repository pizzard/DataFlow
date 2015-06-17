/*
 * Operator_test.cpp
 *
 *  Created on: 23.02.2015
 *      Author: Caspar
 */

#include "Operator_test.h"
#include "Operator.h"

#include <cassert>
#include <type_traits>

#include "master_traits.h"

int foo(int i) {
	return i;
}

template<class T, class B>
struct bar {
	T operator()(B&& b) {
		return T(b);
	}
};

struct IntGiver {
	int operator()() {
		return 1;
	}
};

void TestConnections() {
	auto op1 = [](int i) -> int {return i+1;};
	auto op2 = [](int i) -> int {return i+2;};
	auto voidop = [](int i) -> void {return;};

	op2(op1(1));

	static_assert(std::is_same<utils::function_traits<decltype(op1)>::result_type, int>::value,"lambda was declares with int result");
	static_assert(std::is_same<utils::function_traits<decltype(&foo)>::result_type, int>::value,"function was declares with int result");
	static_assert(std::is_same<utils::function_traits<bar<int, int>>::result_type, int>::value,"functor was declares with int result");

	auto connection = Connect(op1, op2);

	assert(connection(1) == 4);

	static_assert(
			std::is_same<
			utils::function_traits<decltype(connection)>::result_type
			, int>::value,"connection was declares with int result");

	auto connection2 = Connect(voidop, connection);
	static_assert(
			std::is_same<
			utils::function_traits<decltype(connection2)>::result_type
			, int>::value,"connection was declares with void result from voidop");

}
