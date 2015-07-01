//============================================================================
// Name        : Framework.cpp
// Author      : ckielwein
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <unistd.h>

#include "core/Collectionstest.h"
#include "core/Operator_test.h"
#include "ConnectionTests.h"

int main() {

	ConnectionTests::TestConnect();
	ConnectionTests::TestStream();
	TestConnections();
	Collections_test::TestMap();
	Collections_test::TestChain();
	Collections_test::TestFilter();

	return 0;
}
