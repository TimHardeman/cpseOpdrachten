#ifndef _BALL_HPP
#define _BALL_HPP

#include <SFML/Graphics.hpp>
#include "drawableObject.hpp"
#include <vector>

class ball : public drawableObject {
public:
	ball( sf::Vector2f position, float size = 30.0 );

	void draw( sf::RenderWindow & window ) override;
	
	sf::FloatRect getBounds() const override;

	void move( sf::RenderWindow & window );

	bool collision();
	
	void addObject(const drawableObject & object);

private:
	sf::CircleShape Circle;
	sf::Vector2f position;
	float size;
	std::vector<const drawableObject*> collidableObjects;
	sf::Vector2f speed = {+3.0, +3.0};
};

#endif
