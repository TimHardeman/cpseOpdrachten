#ifndef BLOCK_HPP
#define BLOCK_HPP

#include <SFML/Graphics.hpp>
#include "drawableObject.hpp"

class block : public drawableObject{
private:
	sf::RectangleShape Block;
	sf::Vector2f position1;
	sf::Vector2f position2;

public:
	block( sf::Vector2f position1, sf::Vector2f position2 );
	
	void draw( sf::RenderWindow & window ) override;

	void move( sf::Vector2f delta );

	void jump( sf::Vector2f target );
	void jump( sf::Vector2i target );
	
	sf::FloatRect getBounds() const;
	
};

#endif