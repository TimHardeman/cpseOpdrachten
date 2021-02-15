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

void printMoves(char listOfMoves[9]){
	std::cout << '\n';
	std::cout << "	 " << listOfMoves[0] << " | " << listOfMoves[1] << " | " << listOfMoves[2] <<'\n';
	std::cout << "	" << 	   "___|_" << "_" << "_|___"      <<'\n';
	std::cout << "	 " << listOfMoves[3] << " | " << listOfMoves[4] << " | " << listOfMoves[5] <<'\n';
	std::cout << "	" <<       "___|_" << "_" << "_|___"	  <<'\n';
	std::cout << "	 " << listOfMoves[6] << " | " << listOfMoves[7] << " | " << listOfMoves[8] <<'\n';
	std::cout << "	" <<       "   | " << " " << " | "        <<'\n';
	std::cout << '\n';
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

void playWithoutInterface(){
	
	moveCommand listOfCommands[9];
	
	char listOfMoves[9] = {0};
	std::fill_n(listOfMoves, 9, ' ');
	printMoves(listOfMoves);
	
	int move;
	for(int i = 0; i < 9; i++){
		std::cout << "Enter a move (1 to 9) or enter 0 to undo the last move: ";
		std::cin >> move;
		if(!std::cin >> move){
			std::cout << "Invalid input, please enter a move (1 to 9) or enter 0 to undo the last move" << '\n';
			std::cin.clear();
			std::cin.ignore(1000, '\n');
		}
		else if(move == 0){
			i-=2;
			if(-1 > i){ i = -1; }
			executeMoves(listOfCommands, listOfMoves, i+1);
			printMoves(listOfMoves);
		}
		else if(! (move >= 1 && move <= 9) || listOfMoves[move - 1] != ' '){
			std::cout << "Invalid move!" << '\n';
			i--;
		}
		else{
			listOfCommands[i] = moveCommand(move);
			executeMoves(listOfCommands, listOfMoves, i + 1);
			printMoves(listOfMoves);
			bool win = checkwin(listOfMoves);
			if(win){
				int player = 0;
				if(i%2){
					player = 2;
				}
				else{
					player = 1;
				}
				std::cout << "player " << player << " has won!" << '\n';
				return;
			}
		}
	}
	std::cout << "Tie!" << '\n';
}
