#include <SFML/Graphics.hpp>
#include "line.hpp"
#include "rectangle.hpp"
#include "text.hpp"
#include "TicTacToe.hpp"


class TicTacToeInterface{
private:
	moveCommand listOfCommands[9];
	char listOfMoves[9];
	
	int waitForInput(sf::RenderWindow & window){
	
		window.clear();
		
		line line1(sf::Vector2f(200, 100), sf::Color::White, sf::Vector2f(0, 300));
		line line2(sf::Vector2f(300, 100), sf::Color::White, sf::Vector2f(0, 300));
		line line3(sf::Vector2f(100, 200), sf::Color::White, sf::Vector2f(300, 0));
		line line4(sf::Vector2f(100, 300), sf::Color::White, sf::Vector2f(300, 0));
		
		rectangle rectangle1(sf::Vector2f(100, 100), sf::Color::Black, sf::Vector2f(100, 100));
		rectangle rectangle2(sf::Vector2f(200, 100), sf::Color::Black, sf::Vector2f(100, 100));
		rectangle rectangle3(sf::Vector2f(300, 100), sf::Color::Black, sf::Vector2f(100, 100));
		rectangle rectangle4(sf::Vector2f(100, 200), sf::Color::Black, sf::Vector2f(100, 100));
		rectangle rectangle5(sf::Vector2f(200, 200), sf::Color::Black, sf::Vector2f(100, 100));
		rectangle rectangle6(sf::Vector2f(300, 200), sf::Color::Black, sf::Vector2f(100, 100));
		rectangle rectangle7(sf::Vector2f(100, 300), sf::Color::Black, sf::Vector2f(100, 100));
		rectangle rectangle8(sf::Vector2f(200, 300), sf::Color::Black, sf::Vector2f(100, 100));
		rectangle rectangle9(sf::Vector2f(300, 300), sf::Color::Black, sf::Vector2f(100, 100));
		
		rectangle undoButton(sf::Vector2f(400, 50), sf::Color::White, sf::Vector2f(75, 50));
		text undoText(sf::Vector2f(415, 60), 20, sf::Color::Black, "arial.ttf", "undo");
		
		std::vector<text*> moves;
		std::vector<sf::Vector2f> textLocations = 
		{sf::Vector2f(130, 120), sf::Vector2f(230, 120), sf::Vector2f(330, 120), sf::Vector2f(130, 220) , 
		sf::Vector2f(230, 220), sf::Vector2f(330, 220), sf::Vector2f(130, 320), sf::Vector2f(230, 320), sf::Vector2f(330, 320)};
		
		
		for(unsigned int i = 0; i < 9; i++){
			std::string newText(1, listOfMoves[i]);
			moves.push_back(new text(textLocations[i], 50, sf::Color::White, "arial.ttf", newText));
		}
			
		rectangle1.draw(window);
		rectangle2.draw(window);
		rectangle3.draw(window);
		rectangle4.draw(window);
		rectangle5.draw(window);
		rectangle6.draw(window);
		rectangle7.draw(window);
		rectangle8.draw(window);
		rectangle9.draw(window);
		
		undoButton.draw(window);
		undoText.draw(window);
		
		line1.draw(window);
		line2.draw(window);
		line3.draw(window);
		line4.draw(window);
		
		for(unsigned int i = 0; i < moves.size(); i++){
			moves[i]->draw(window);
		}
		
		bool pressed = false;
		bool lock = true;
		
		sf::Vector2i mouse;
		sf::Vector2f floatMouse;
		
		while(window.isOpen()){
			window.display();
			
			if(sf::Mouse::isButtonPressed( sf::Mouse::Left)){
				if(! lock){

					mouse = sf::Mouse::getPosition( window );
					floatMouse = sf::Vector2f(mouse);

					pressed = true;
					lock = true;
				}
				else{
					pressed = false;
				}
			}
			else{
				lock = false;
			}
			
			if(pressed){
				if(undoButton.getBounds().contains(floatMouse)){
					return 0;
				}
				else if( rectangle1.getBounds().contains(floatMouse) && listOfMoves[0] == ' '){
					return 1;
				}
				else if( rectangle2.getBounds().contains(floatMouse) && listOfMoves[1] == ' '){
					return 2;
				}
				else if( rectangle3.getBounds().contains(floatMouse) && listOfMoves[2] == ' '){
					return 3;
				}
				else if( rectangle4.getBounds().contains(floatMouse) && listOfMoves[3] == ' '){
					return 4;
				}
				else if( rectangle5.getBounds().contains(floatMouse) && listOfMoves[4] == ' '){
					return 5;
				}
				else if( rectangle6.getBounds().contains(floatMouse) && listOfMoves[5] == ' '){
					return 6;
				}
				else if( rectangle7.getBounds().contains(floatMouse) && listOfMoves[6] == ' '){
					return 7;
				}
				else if( rectangle8.getBounds().contains(floatMouse) && listOfMoves[7] == ' '){
					return 8;
				}
				else if( rectangle9.getBounds().contains(floatMouse) && listOfMoves[8] == ' '){
					return 9;
				}
			}
			
			sf::Event event;
			while( window.pollEvent(event) ){
				if( event.type == sf::Event::Closed ){
					window.close();
				}
			}
		}
		return -1;
	}

public:
	void play(){
		sf::RenderWindow window{ sf::VideoMode{ 500, 500 }, "SFML window" };

		std::fill_n(listOfMoves, 9, ' ');
		
		int move;
		for(int i = 0; i < 9; i++){
			move = waitForInput(window);
			if(move == -1){
				break;
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
					std::cout << "player " << player << " has won!" << '\n';
					return;
				}
			}
		}
		std::cout << "Tie!" << '\n';
	}	
};
	
