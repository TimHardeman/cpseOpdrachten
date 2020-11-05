#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "ostream"
#include "string"
#include "set.hpp"

TEST_CASE("type string, size 1 and 3"){
	std::ostringstream output;
	
	set<std::string, 1> stringSize1;
	stringSize1.add("Een");
	stringSize1.add("Twee");
	stringSize1.add("Drie");
	stringSize1.add("Vier");
	output << stringSize1;
	
	REQUIRE(output.str() == "Een \n");
	
	output.str("");
	set<std::string, 3> stringSize3;
	stringSize3.add("Een");
	stringSize3.add("Twee");
	stringSize3.add("Drie");
	stringSize3.add("Vier");
	output << stringSize3;
	
	REQUIRE(output.str() == "Een Twee Drie \n");
	

	output.str("");
	stringSize3.remove("Drie");
	stringSize3.add("Twee");
	output << stringSize3;
	
	REQUIRE(output.str() == "Een Twee \n");
	REQUIRE(stringSize3.contains("Een"));
	REQUIRE(! stringSize3.contains("Drie"));
}

TEST_CASE("type float, size 2 and 4"){
	std::ostringstream output;
	
	set<float, 2> floatSize2;
	floatSize2.add(1.1);
	floatSize2.add(2.2);
	floatSize2.add(3.3);
	floatSize2.add(4.4);
	floatSize2.add(5.5);
	output << floatSize2;
	
	REQUIRE(output.str() == "1.1 2.2 \n");
	
	output.str("");
	set<float, 4> floatSize4;
	floatSize4.add(1.1);
	floatSize4.add(2.2);
	floatSize4.add(3.3);
	floatSize4.add(4.4);
	floatSize4.add(5.5);
	output << floatSize4;
	
	REQUIRE(output.str() == "1.1 2.2 3.3 4.4 \n");
	
	output.str("");
	floatSize4.remove(3.3);
	floatSize4.add(2.2);
	output << floatSize4;
	
	REQUIRE(output.str() == "1.1 2.2 4.4 \n");
	REQUIRE(floatSize4.contains(1.1));
	REQUIRE(! floatSize4.contains(3.3));
}