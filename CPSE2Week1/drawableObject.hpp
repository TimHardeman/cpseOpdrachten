#ifndef DRAWABLEOBJECT_HPP
#define DRAWABLEOBJECT_HPP

#include <SFML/Graphics.hpp>
#include <iostream>

class drawableObject{
public:
	virtual void draw( sf::RenderWindow & window ) = 0;
	virtual sf::FloatRect getBounds() const = 0;
	virtual void move( sf::RenderWindow & window ){}
};

#endif

