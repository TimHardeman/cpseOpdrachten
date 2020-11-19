#include "wall.hpp"

wall::wall( sf::Vector2f position1, sf::Vector2f position2 ) :
	position1{ position1 },
	position2{ position2 }
{}

void wall::draw( sf::RenderWindow & window ){
	Wall.setPosition(position1);
	Wall.setSize(position2);
	Wall.setFillColor(sf::Color::Blue);
	window.draw(Wall);
}

void wall::move( sf::Vector2f delta ){
	position1 += delta;
	position2 += delta;
}

sf::FloatRect wall::getBounds() const {
	return Wall.getGlobalBounds();
}
