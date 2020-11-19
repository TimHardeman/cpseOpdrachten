#include <iostream>
#include <functional>
#include <SFML/Graphics.hpp>
#include "ball.hpp"
#include "wall.hpp"
#include "block.hpp"

class action {
private:
	std::function< bool() > condition;
	std::function< void() > work;
public:
	action(
	   std::function< bool() > condition, 
	   std::function< void() > work
	) : condition( condition ), 
		work( work ) 
	{}

	action(
		sf::Keyboard::Key key,
		std::function< void() > work
	) :
		condition(
			[ key ]()->bool { return sf::Keyboard::isKeyPressed( key ); }
		),
		work(work)
	{}

	action(
		sf::Mouse::Button button,
		std::function< void() > work
	) :
		condition(
			[ button ]()->bool { return sf::Mouse::isButtonPressed( button ); }
		),
		work(work)
	{}
	
	action(
		bool x,
		std::function< void() > work
	) :
		condition(
			[ x ]()->bool { return x; }
		),
		work(work)
	{}

	void operator()(){
		if( condition() ){
			work();
		}
	}
};

int main( int argc, char *argv[] ){
	std::cout << "Starting application 01-05 array of actions\n";

	sf::RenderWindow window{ sf::VideoMode{ 640, 480 }, "SFML window" };
	ball my_ball{ sf::Vector2f{ 360.0, 241.0 } };
	wall wall1{ sf::Vector2f{0, 0}, sf::Vector2f{640, 25} };
	wall wall2{ sf::Vector2f{0, 25}, sf::Vector2f{25, 480} };
	wall wall3{ sf::Vector2f{0, 455}, sf::Vector2f{640, 480} };
	wall wall4{ sf::Vector2f{615, 25}, sf::Vector2f{640, 480} };
	block Block{ sf::Vector2f{0, 0}, sf::Vector2f{100, 100} };
	my_ball.addObject(wall1);
	my_ball.addObject(wall2);
	my_ball.addObject(wall3);
	my_ball.addObject(wall4);
	my_ball.addObject(Block);

	action actions[] = {
		action( true,  				 [&](){ my_ball.move(window);}),
		action( sf::Keyboard::Left,  [&](){ Block.move( sf::Vector2f( -10.0,  0.0 )); }),
		action( sf::Keyboard::Right, [&](){ Block.move( sf::Vector2f( +10.0,  0.0 )); }),
		action( sf::Keyboard::Up,    [&](){ Block.move( sf::Vector2f(  0.0, -10.0 )); }),
		action( sf::Keyboard::Down,  [&](){ Block.move( sf::Vector2f(  0.0, +10.0 )); }),
		action( sf::Mouse::Left,     [&](){ Block.jump( sf::Mouse::getPosition( window )); })
	};

	while (window.isOpen()) {
		
		for( auto & action : actions ){
			action();
		}

		window.clear();
		my_ball.draw( window );
		wall1.draw( window );
		wall2.draw( window );
		wall3.draw( window );
		wall4.draw( window );	
		Block.draw( window );
		window.display();

		sf::sleep( sf::milliseconds( 20 ));

        sf::Event event;		
	    while( window.pollEvent(event) ){
			if( event.type == sf::Event::Closed ){
				window.close();
			}
		}	
	}

	std::cout << "Terminating application\n";
	return 0;
}

