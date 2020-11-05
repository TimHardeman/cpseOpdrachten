#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "ostream"
#include "string"
#include "set.hpp"

TEST_CASE("char array max"){
	set<std::array<char, 3>, 5> charArraySize5;
	charArraySize5.add({'a', 'b', 'c'});
	charArraySize5.add({'b', 'c', '8'});
	charArraySize5.add({'z', '3', '5'});
	charArraySize5.add({'3', 'f', 'h'});
	charArraySize5.add({'n', 'p', 'r'});
	charArraySize5.add({'z', 'z', 'z'});
	
	std::array<char, 3> max = {'z', '3', '5'};

	REQUIRE(charArraySize5.max() == max);
	
	charArraySize5.remove({'3', 'f', 'h'});
	REQUIRE(! charArraySize5.contains({'3', 'f', 'h'}));
	REQUIRE(charArraySize5.contains({'n', 'p', 'r'}));
	
	std::ostringstream output;
	output << charArraySize5;
	REQUIRE(output.str() == "{a, b, c} {b, c, 8} {z, 3, 5} {n, p, r} \n");
}
