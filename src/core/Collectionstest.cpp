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

void Collections_test::TestMap() {
	auto op = map([](int i) -> int { return i+1; });
	auto op2 = map([](int i) -> int { return i+1; });

	auto give = [](void) ->std::vector<int> {return std::vector<int>({0,0,1,1}); };
	//Connect(give, op2); //ToDo doesn't build, why? complains about overloaded method, I don't see the overloading

	op(give()); // sanity check

}

void Collections_test::TestReduce() {
}

void Collections_test::TestFold() {
}

void Collections_test::TestChain() {
}
