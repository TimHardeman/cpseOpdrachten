#ifndef SCREEN_OBJECT_HPP
#define SCREEN_OBJECT_HPP

#include <SFML/Graphics.hpp>
#include <iostream>

class screen_object{
protected:
	// The pixels (x and y) where the object will be drawn, in floats.
	sf::Vector2f position;
public:
	screen_object(sf::Vector2f position):
		position{position}
		{}
		
	// Implements drawing the object on the given window.
	virtual void draw( sf::RenderWindow & window ) = 0;
	
	// Implements getting the global bounds of the object and returning them.
	virtual sf::FloatRect getBounds() const = 0;
	
	// Sets the offset to the mouse when the object is first selected,
	// so that the mouse can grab and move the object from that point.
	virtual void setOffset(sf::Vector2f offset) = 0;
	
	// Implements moving the object to given position.
	virtual void move(sf::Vector2f newPosition) = 0;
	
	// Implements writing the object to the given file.
	virtual void writeToFile(std::ofstream& file) = 0;
};

#endif

