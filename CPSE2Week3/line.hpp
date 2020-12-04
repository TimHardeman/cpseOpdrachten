#ifndef LINE_HPP
#define LINE_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include "screen_object.hpp"

class line : public screen_object{
private:
	sf::RectangleShape bounds;
	sf::Color Color;
	sf::Vector2f Size;
	sf::Vector2f currentOffset;
public:
	line(sf::Vector2f position, sf::Color Color, sf::Vector2f Size):
		screen_object{position},
		Color{Color},
		Size{Size}
		{}
	
	void draw( sf::RenderWindow & window ) override {
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
	sf::FloatRect getBounds() const override {
		return bounds.getGlobalBounds();
	}
	
	void setOffset(sf::Vector2f mouse) override {
		currentOffset = position - mouse;
	}
	
	void move(sf::Vector2f newPosition) override {
		sf::Vector2f dif = position - newPosition;
		position -= dif - currentOffset;
	}
	
	void writeToFile(std::ofstream& file) override {
		std::string writeColor = "";
		
		const struct { const char * name; sf::Color color; } colors[]{
			{ "yellow", sf::Color::Yellow },
			{ "red",    sf::Color::Red },
			{ "blue", sf::Color::Blue },
			{ "green", sf::Color::Green }
		};
		
		for( auto const & color : colors ){
			if( color.color == Color ){ 
				writeColor = color.name;
				break;
			}
		}
		
		file << '(' << position.x << ',' << position.y << ')';
		file << ' ' << "LINE" << ' ';
		file << writeColor << ' ';
		file << '(' << Size.x << ',' << Size.y << ')' << '\n';
	}
		
};

#endif