#include "TicTacToe.hpp"

class TicTacToeTerminal{
private:
	moveCommand listOfCommands[9];
	char listOfMoves[9] = {0};
	
	void printMoves(){
		std::cout << '\n';
		std::cout << "	 " << listOfMoves[0] << " | " << listOfMoves[1] << " | " << listOfMoves[2] <<'\n';
		std::cout << "	" << 	   "___|_" << "_" << "_|___"      <<'\n';
		std::cout << "	 " << listOfMoves[3] << " | " << listOfMoves[4] << " | " << listOfMoves[5] <<'\n';
		std::cout << "	" <<       "___|_" << "_" << "_|___"	  <<'\n';
		std::cout << "	 " << listOfMoves[6] << " | " << listOfMoves[7] << " | " << listOfMoves[8] <<'\n';
		std::cout << "	" <<       "   | " << " " << " | "        <<'\n';
		std::cout << '\n';
	}
public:
	void play(){
		std::fill_n(listOfMoves, 9, ' ');
		
		int move;
		for(int i = 0; i < 9; i++){
			printMoves();
			std::cout << "Enter a move (1 to 9) or enter 0 to undo the last move: ";
			std::cin >> move;
			if(!std::cin >> move){
				std::cout << "Invalid input, please enter a move (1 to 9) or enter 0 to undo the last move" << '\n';
				std::cin.clear();
				std::cin.ignore(1000, '\n');
				i--;
			}
			else if(! (move >= 1 && move <= 9) || listOfMoves[move - 1] != ' '){
				std::cout << "Invalid move!" << '\n';
				i--;
			}
			else if(move == 0){
				i-=2;
				if(-1 > i){ i = -1; }
				executeMoves(listOfCommands, listOfMoves, i+1);
			}
			else{
				listOfCommands[i] = moveCommand(move);
				executeMoves(listOfCommands, listOfMoves, i + 1);
				
				bool win = checkwin(listOfMoves);
				if(win){
					int player = 0;
					if(i%2){
						player = 2;
					}
					else{
						player = 1;
					}
					printMoves();
					std::cout << "player " << player << " has won!" << '\n';
					return;
				}
			}
		}
		printMoves();
		std::cout << "Tie!" << '\n';
	}
};


