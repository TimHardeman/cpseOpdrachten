#ifndef TICTACTOECOMMANDS_HPP
#define TICTACTOECOMMANDS_HPP

#include <vector>
using namespace std;

class moveCommand{
public:
	int square;
public:
	moveCommand(){}
	moveCommand(int square):
	square{ square }
	{}
	
	virtual void execute(char listOfMoves[9], int turn){
		if(turn % 2){
			listOfMoves[square - 1] = 'O';
		}
		else{
			listOfMoves[square - 1] = 'X';
		}
	}
};

void executeMoves(moveCommand listOfCommands[9], char listOfMoves[9], int size){
	std::fill_n(listOfMoves, 9, ' ');
	for(int i = 0; i < size; i++){
		listOfCommands[i].execute(listOfMoves, i);
	}
}

bool checkwin(char listOfMoves[9]){
	for(int i = 0; i < 3; i++){
		if(listOfMoves[i] != ' '){
			if(listOfMoves[i] == listOfMoves[i + 3] && listOfMoves[i] == listOfMoves[i+6]){
				return true;
			}
		}
		
		if(listOfMoves[i * 3] != ' '){
			if(listOfMoves[i * 3] == listOfMoves[(i * 3) + 1] && listOfMoves[i * 3] == listOfMoves[(i * 3) + 2]){
				return true;
			}
		}
	}
	
	if(listOfMoves[4] != ' '){
		if(listOfMoves[0] == listOfMoves[4] && listOfMoves[0] == listOfMoves[8]){
			return true;
		}
		if(listOfMoves[2] == listOfMoves[4] && listOfMoves[2] == listOfMoves[6]){
			return true;
		}
	}
	
	return false;
	
}

#endif