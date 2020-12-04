#include <iostream>
#include <fstream>
#include <functional>
#include <SFML/Graphics.hpp>
#include <vector>
#include "screen_object.hpp"
#include "circle.hpp"
#include "rectangle.hpp"
#include "line.hpp"
#include "picture.hpp"
#include "exceptions.hpp"
#include "operators.hpp"

// Reads a line in the given file, returning the object defined in that line.
screen_object * screen_object_read( std::ifstream & input ){
	sf::Vector2f position;
	std::string name;
	std::string file;
	sf::Color color;
	sf::Vector2f size;
	float radius;
	input >> position >> name;

	if( name == "CIRCLE" ){
		input >> color >> radius;
		return new circle(position, color, radius);

	} else if( name == "RECTANGLE" ){
		input >> color >> size;
		return new rectangle(position, color, size);
	  
	} else if( name == "LINE" ){
		input >> color >> size;
		return new line(position, color, size);

	} else if( name == "PICTURE" ){
		input >> file;
		input >> size;
	return new picture(position, file, size);

	} else if( name == "" ){
      throw end_of_file();
	}

	throw unknown_shape( name );
}


int main( int argc, char *argv[] ){
	
	std::vector<screen_object*> screen_objects;
	
	std::ifstream input( "objects.txt" );
	bool endReached = false;
	try {
		for(;;){
			screen_objects.push_back( screen_object_read( input ));
		}
	} catch ( const end_of_file & ){
		endReached = true;
	} catch ( std::exception & problem ){
		std::cout << problem.what() << '\n';
	}
	
	if(endReached){
		sf::RenderWindow window{ sf::VideoMode{ 640, 480 }, "SFML window" };
		screen_object* selectedObject; // Holds the currently selected object, if there is one.
		bool selected = false; // Flag to indicate if an object has been selected, so you can only select 1 object at a time.
		while (window.isOpen()) {
			  
			window.clear();
			for(unsigned int i = 0; i < screen_objects.size(); i++){
				screen_objects[i]->draw(window);
			}
			window.display();
			  
			if(sf::Mouse::isButtonPressed( sf::Mouse::Left )){
				if(selected){
					sf::Vector2i mouse = sf::Mouse::getPosition( window );
					sf::Vector2f floatMouse = sf::Vector2f(mouse);
					selectedObject->move(floatMouse);	
					selectedObject->draw(window);
				}
				else{
					sf::Vector2i mouse = sf::Mouse::getPosition( window );
					sf::Vector2f floatMouse = sf::Vector2f(mouse);
					for(unsigned i = 0; i < screen_objects.size(); i++){
						sf::FloatRect bounds = screen_objects[i]->getBounds();
						if(bounds.contains(floatMouse)){
							selectedObject = screen_objects[i];
							screen_objects[i]->setOffset(floatMouse);
							selected = true;
						}
					}
				}
			}
			else{
				selected = false;
			}	  

			sf::Event event;		
			while( window.pollEvent(event) ){
				if( event.type == sf::Event::Closed ){
					window.close();
				}
			}	
		}
		std::ofstream file;
		file.open("objects.txt");
		for(unsigned int i = 0; i < screen_objects.size(); i++){
				screen_objects[i]->writeToFile(file);
		}
		file.close();
	}
	else{
		std::cout << "1 or more errors have been detected in the given file, the window will not be run." << '\n';
	}
}

