#include <algorithm>
#include <vector>
#include <fstream>
#include <iostream>
#include <map>
#include "commands.hpp"
#include "hwlib.hpp"
#include "interface.hpp"

int main(){
	
	
	// playWithInterface starts a game with a graphical interface, playWithoutInterface starts a game in the console
	// Currently a game with interface is started first, after which a game without is started for testing purposes.
	// Normally you would start only 1 of the 2.
	playWithInterface();
	playWithoutInterface();
}


