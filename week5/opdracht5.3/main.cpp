#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "ostream"
#include "string"
#include "set.hpp"

TEST_CASE("float max"){
	set<float, 5> floatSize5;
	floatSize5.add(1.1);
	floatSize5.add(5.5);
	floatSize5.add(4.4);
	floatSize5.add(2.2);
	floatSize5.add(3.3);

	REQUIRE(floatSize5.max() == 5.5);
}

TEST_CASE("string max"){
	set<std::string, 5> stringSize5;
	stringSize5.add("C++");
	stringSize5.add("Java");
	stringSize5.add("Python");
	stringSize5.add("Assembly");
	stringSize5.add("Pascal");

	REQUIRE(stringSize5.max() == "Python");
}