#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include "screen_object.hpp"

class circle : public screen_object{
private:
	sf::CircleShape Circle;
	sf::Color Color;
	float radius;
	sf::Vector2f currentOffset;
public:
	circle(sf::Vector2f position, sf::Color Color, float radius):
		screen_object{position},
		Color{Color},
		radius{radius}
		{}
		
	void draw( sf::RenderWindow & window ) override {
		Circle.setPosition(position);
		Circle.setFillColor(Color);
		Circle.setRadius(radius);
		window.draw(Circle);
	}
	
	sf::FloatRect getBounds() const override {
		return Circle.getGlobalBounds();
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
