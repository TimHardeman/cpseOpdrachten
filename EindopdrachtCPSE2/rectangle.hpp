#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include "screen_object.hpp"

class rectangle : public screen_object{
private:
	sf::RectangleShape Rectangle;
	sf::Color Color;
	sf::Vector2f Size;
	sf::Vector2f currentOffset;
public:
	rectangle(sf::Vector2f position, sf::Color Color, sf::Vector2f Size):
		screen_object{position},
		Color{Color},
		Size{Size}
		{}
		
	void draw( sf::RenderWindow & window ) override {
		Rectangle.setPosition(position);
		Rectangle.setFillColor(Color);
		Rectangle.setSize(Size);
		window.draw(Rectangle);
	}
	
	sf::FloatRect getBounds() const override {
		return Rectangle.getGlobalBounds();
	}
	
	void setOffset(sf::Vector2f mouse) override {
		currentOffset = position - mouse;
	}
	
	void move(sf::Vector2f newPosition) override {
		position = newPosition + currentOffset;
	}
	
	sf::Color returnColor() override{
		return Color;
	}
	
	void changeColor(sf::Color newColor){
		Color = newColor;
	}
		
};

#endif