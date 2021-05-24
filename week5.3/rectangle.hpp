#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include <SFML/Graphics.hpp>
#include <iostream>

class rectangle{
private:
	sf::RectangleShape Rectangle;
	sf::Vector2f position;
	sf::Color Color;
	sf::Vector2f Size;
	sf::Vector2f currentOffset;
public:
	rectangle(sf::Vector2f position, sf::Color Color, sf::Vector2f Size):
		position{position},
		Color{Color},
		Size{Size}
		{}
		
	void draw( sf::RenderWindow & window ){
		Rectangle.setPosition(position);
		Rectangle.setFillColor(Color);
		Rectangle.setSize(Size);
		window.draw(Rectangle);
	}
	sf::FloatRect getBounds() const {
		return Rectangle.getGlobalBounds();
	}
	
};

#endif