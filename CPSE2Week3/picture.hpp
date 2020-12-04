#ifndef PICTURE_HPP
#define PICTURE_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include "screen_object.hpp"

class picture : public screen_object{
private:
	sf::Sprite Sprite;
	std::string File;
	sf::Vector2f scale;
	sf::Vector2f currentOffset;
public:
	picture(sf::Vector2f position, std::string File, sf::Vector2f scale):
		screen_object{position},
		File{File},
		scale{scale}
		{}
		
	void draw( sf::RenderWindow & window ) override {
		sf::Image Image;
		sf::Texture Texture;
		Sprite.setPosition(position);
		Sprite.setScale(scale);
		Image.loadFromFile(File);
		Texture.loadFromImage(Image);
		Sprite.setTexture(Texture);
		window.draw(Sprite);
	}
	
	sf::FloatRect getBounds() const override {
		return Sprite.getGlobalBounds();
	}
	
	void setOffset(sf::Vector2f mouse) override {
		currentOffset = position - mouse;
	}
	
	void move(sf::Vector2f newPosition) override {
		position = newPosition + currentOffset;
	}
	
	void writeToFile(std::ofstream& file) override {
		file << '(' << position.x << ',' << position.y << ')';
		file << ' ' << "PICTURE" << ' ';
		file << File << ' ';
		file << '(' << scale.x << ',' << scale.y << ')' << '\n';
	}
		
};

#endif