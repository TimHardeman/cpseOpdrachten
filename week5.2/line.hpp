#ifndef LINE_HPP
#define LINE_HPP

#include <SFML/Graphics.hpp>

class line{
private:
	sf::RectangleShape bounds;
	sf::Vector2f position;
	sf::Color Color;
	sf::Vector2f Size;
	sf::Vector2f currentOffset;
public:
	line(sf::Vector2f position, sf::Color Color, sf::Vector2f Size):
		position{position},
		Color{Color},
		Size{Size}
		{}
	
	void draw( sf::RenderWindow & window ){
		sf::VertexArray vertices(sf::Lines, 2);
		vertices[0].position = position; 
		vertices[0].color = Color;
		vertices[1].position.x = position.x + Size.x;
		vertices[1].position.y = position.y + Size.y;
		vertices[1].color = Color;
		window.draw(vertices);
		bounds.setPosition(position);
		bounds.setSize(Size);
	}
};

#endif
