/*
 * ConnectionTests.cpp
 *
 *  Created on: 04.03.2015
 *      Author: Caspar
 */

#include "ConnectionTests.h"

#include <boost/signals2/signal.hpp>
#include <iostream>

#include "core/Buffer.h"
#include "core/Operator.h"

ConnectionTests::ConnectionTests() {
	// TODO Auto-generated constructor stub

}

template<class T, class B>
struct bar
{
	T operator()(B&& b) { return T(b); }
};

int foo() { return 77; }

void ConnectionTests::TestConnect() {
	// Test Connection of Lambdas
	auto op1 = [](int i) -> int { return i+1; };
	auto op2 = [](int i) -> void { std::cout << "Lambda print: " << i << "\n";};

	auto connection = Connect(op1, op2);
	connection(2);

	auto connectionl = Connect([](int i) { return i+77; }, op2);
	connectionl(1);

	// Test Buffer
	//auto connection2 = Connect(CopyBuffer<int>(1), Connect(op1, op2));
	//connection2();

	// Test Operator
	auto give = [](void) ->int { return 1; };

	auto connection3 = Connect(give, op1);

	Operator test_printer2;
	Connect(Connect(connection3, [](int i) -> int { return i+1; }), test_printer2.in);
	Operator test_printer;

	Connect(give, test_printer.in);
	test_printer.Trigger();

	Operator test_printer3;
	Connect([](void) ->int { return 4; }, test_printer3.in);
	test_printer3.Trigger();

	// Test Boost Signal
	boost::signals2::signal<int()> sig;
	Connect(sig, give);
	int i = *(sig());
	std::cout << "signal: " << i << "\n";

}

void ConnectionTests::TestStream() {

	auto give = [](void) ->int { return 77; };
	auto op1 = [](int i) -> int { return i+1; };
	Operator test_printer;
	Operator test_printer2;
	Operator test_printer3;

	auto connection = give >> op1;
	auto connection2 = Connect(give, op1);

	static_assert(std::is_same<decltype(connection), decltype(connection2)>::value, "");

	Connect(give, test_printer.in);
	test_printer.Trigger();

	[](void) -> int{ return 88; } >> test_printer2.in;
	test_printer2.Trigger();

	// connection2 >> test_printer3.in;
	 //[](void){ return 77; } >> op1 >> test_printer3.in;

//	test_printer2.Trigger();

	[](){ return 77; } >> [](int i){ return i+99; } >> test_printer3.in;
	test_printer3.Trigger();


}

ConnectionTests::~ConnectionTests() {
	// TODO Auto-generated destructor stub
}

