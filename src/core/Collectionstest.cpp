/*
 * Collectionstest.cpp
 *
 *  Created on: 16.06.2015
 *      Author: Caspar
 */

#include "Collectionstest.h"

#include "functional.h"
#include "Operator.h"
Collections_test::Collections_test() {
	// TODO Auto-generated constructor stub

}

Collections_test::~Collections_test() {
	// TODO Auto-generated destructor stub
}

struct VectorPrint
{
	InputPort<std::vector<int>> in;

	void Trigger() {
		std::cout << "VectorPrint: " ;
		for(int i : in())
			std::cout << i << "\n";
	}
};

void Collections_test::TestMap() {
	auto op = map([](int i) -> int { return i+1; });
	auto op2 = map([](int i) -> int { return i+1; });

	auto give = [](void) ->std::vector<int> {return std::vector<int>({0,0,1,1}); };
	auto test = Connect(give, op2); //ToDo doesn't build, why? complains about overloaded method, I don't see the overloading

	auto val = test();
	assert(val.size() == 4);
	assert(val[0] == 1);
	assert(val[3] == 2);

	auto test_2 = give >> op2;
	val = test_2();
	assert(val.size() == 4);
	assert(val[0] == 1);
	assert(val[3] == 2);
}

void Collections_test::TestFilter() {
}

void Collections_test::TestFold() {
}

void Collections_test::TestChain() {
	auto give = [](void) ->std::vector<int> {return std::vector<int>({0,0,1,1}); };
	VectorPrint test_print;

	give >> map([](int i) { return i+1; })
		 >> test_print.in;

	test_print.Trigger();
}
