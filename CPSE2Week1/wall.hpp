#ifndef WALL_HPP
#define WALL_HPP

#include <SFML/Graphics.hpp>
#include "drawableObject.hpp"

class wall : public drawableObject{
private:
	sf::RectangleShape Wall;
	sf::Vector2f position1;
	sf::Vector2f position2;
	

public:

	wall( sf::Vector2f position1, sf::Vector2f position2 );
	
	void draw( sf::RenderWindow & window ) override;

	void move( sf::Vector2f delta );
	
	sf::FloatRect getBounds() const;
	
};

#endif