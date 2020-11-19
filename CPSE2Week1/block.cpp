#include "block.hpp"

block::block( sf::Vector2f position1, sf::Vector2f position2 ) :
	position1{ position1 },
	position2{ position2 }
{}

void block::draw( sf::RenderWindow & window ){
	Block.setPosition(position1);
	Block.setSize(position2);
	Block.setFillColor(sf::Color::Green);
	window.draw(Block);
}

void block::move( sf::Vector2f delta ){
	position1 += delta;
}

void block::jump( sf::Vector2f target ){
	position1 = target;
}

void block::jump( sf::Vector2i target ){
	jump( sf::Vector2f( 
		static_cast< float >( target.x ), 
		static_cast< float >( target.y )
	));
}

sf::FloatRect block::getBounds() const {
	return Block.getGlobalBounds();
}
