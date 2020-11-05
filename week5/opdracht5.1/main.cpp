#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "ostream"
#include "string"
#include "set.hpp"

TEST_CASE("add"){
	set collection;
	collection.add(5);
	std::ostringstream output;
	output << collection;

	REQUIRE(output.str() == "5 \n");
	collection.add(6);
	output.str("");
	output << collection;
	REQUIRE(output.str() == "5 6 \n");
}

TEST_CASE("add same number multiple times"){
	set collection;
	collection.add(5);
	collection.add(5);
	std::ostringstream output;
	output << collection;
	
	REQUIRE(output.str() == "5 \n");
}

TEST_CASE("add more than 10 numbers"){
	set collection;
	collection.add(1);
	collection.add(2);
	collection.add(3);
	collection.add(4);
	collection.add(5);
	collection.add(6);
	collection.add(7);
	collection.add(8);
	collection.add(9);
	collection.add(10);
	collection.add(11);
	collection.add(12);
	
	std::ostringstream output;
	output << collection;
	
	REQUIRE(output.str() == "1 2 3 4 5 6 7 8 9 10 \n");
}

TEST_CASE("add and remove"){
	set collection;
	collection.add(5);
	collection.remove(5);
	std::ostringstream output;
	output << collection;
	REQUIRE(output.str() == "\n");
}

TEST_CASE("add 2, remove 1"){
	set collection;
	collection.add(5);
	collection.add(6);
	collection.remove(5);
	std::ostringstream output;
	output << collection;
	REQUIRE(output.str() == "6 \n");
}

TEST_CASE("contains"){
	set collection;
	collection.add(5);
	REQUIRE(collection.contains(5));
	REQUIRE(! collection.contains(6));
}

TEST_CASE("contains after remove"){
	set collection;
	collection.add(5);
	collection.remove(5);
	REQUIRE(! collection.contains(5));
}