#include "ball.hpp"
#include "hwlib.hpp"

ball::ball( sf::Vector2f position, float size ) :
	position{ position },
	size{ size }
{}

void ball::draw( sf::RenderWindow & window ){
	Circle.setRadius(size);
	Circle.setPosition(position);
	Circle.setFillColor(sf::Color::Red);
	
	window.draw(Circle);
}

sf::FloatRect ball::getBounds() const {
	return Circle.getGlobalBounds();
}

void ball::move( sf::RenderWindow & window ){
	sf::Vector2f speedCopy = speed;
	
	while(speedCopy.x != 0 || speedCopy.y != 0){
		if(speedCopy.x > 0){
			position.x++;
			speedCopy.x--;
			draw( window );
			if(collision()){
				speed.x *= -1;
				position.x--;
			}
		}
		else if(speedCopy.x < 0){
			position.x--;
			speedCopy.x++;
			draw( window );
			if(collision()){
				speed.x *= -1;
				position.x++;
			}
		}
		
		if(speedCopy.y > 0){
			position.y++;
			speedCopy.y--;
			draw( window );
			if(collision()){
				speed.y *= -1;
				position.y--;
			}
		}
		
		else if(speedCopy.y < 0){
			position.y--;
			speedCopy.y++;
			draw( window );
			if(collision()){
				speed.y *= -1;
				position.y++;
			}
		}
	} 
}

bool ball::collision(){
	for(unsigned int i = 0; i < collidableObjects.size(); i++){
		sf::FloatRect bounds = collidableObjects[i]->getBounds();
		if(bounds.intersects(Circle.getGlobalBounds())){
			return true;
		}
	}
	return false;
}

void ball::addObject(const drawableObject & object){
	collidableObjects.push_back(& object);
}
