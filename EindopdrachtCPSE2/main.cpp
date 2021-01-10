#include <iostream>
#include <fstream>
#include <functional>
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "screen_object.hpp"
#include "circle.hpp"
#include "rectangle.hpp"
#include "picture.hpp"


int main( int argc, char *argv[] ){
	
	std::vector<std::shared_ptr<screen_object>> colors; // Holds the selectable colors
	std::vector<std::shared_ptr<screen_object>> actions; // Holds the selectable actions
	std::vector<std::shared_ptr<screen_object>> newObjects; // Holds the objects that can be clicked to create new objects
	std::vector<std::shared_ptr<screen_object>> screen_objects; // Holds the objects that are created, which can be manipulated with the left mouse button.
	
	std::shared_ptr<screen_object> red = std::make_shared<circle>(circle(sf::Vector2f{10, 10}, sf::Color::Red, 10));
	std::shared_ptr<screen_object> blue = std::make_shared<circle>(circle(sf::Vector2f{10, 40}, sf::Color::Blue, 10));
	std::shared_ptr<screen_object> green = std::make_shared<circle>(circle(sf::Vector2f{10, 70}, sf::Color::Green, 10));
	std::shared_ptr<screen_object> yellow = std::make_shared<circle>(circle(sf::Vector2f{10, 100}, sf::Color::Yellow, 10));
	std::shared_ptr<screen_object> white = std::make_shared<circle>(circle(sf::Vector2f{10, 130}, sf::Color::White, 10));
	
	colors.push_back(red);
	colors.push_back(blue);
	colors.push_back(green);
	colors.push_back(yellow);
	colors.push_back(white);
	
	std::shared_ptr<screen_object> moveAction = std::make_shared<picture>(picture(sf::Vector2f{40, 70}, "select.jpg", sf::Vector2f{0.088, 0.088}));
	std::shared_ptr<screen_object> deleteAction = std::make_shared<picture>(picture(sf::Vector2f{40, 100}, "delete.jpg", sf::Vector2f{0.088, 0.088}));
	std::shared_ptr<screen_object> pushBackAction = std::make_shared<picture>(picture(sf::Vector2f{40, 130}, "pushBack.jpg", sf::Vector2f{0.088, 0.088}));
	
	actions.push_back(moveAction);
	actions.push_back(deleteAction);
	actions.push_back(pushBackAction);
	
	std::shared_ptr<screen_object> newCircle = std::make_shared<circle>(circle(sf::Vector2f{40, 10}, sf::Color::White, 10));
	std::shared_ptr<screen_object> newRectangle = std::make_shared<rectangle>(rectangle(sf::Vector2f{40, 40}, sf::Color::White, sf::Vector2f{20, 20}));
	
	newObjects.push_back(newCircle);
	newObjects.push_back(newRectangle);
	
	sf::RenderWindow window{ sf::VideoMode{ 640, 480 }, "SFML window" };
	sf::Color lastClickedColor = sf::Color::White; // Holds the last clicked color
	bool lastClickedWasColor = false; // Flag to indicate if the last clicked object was a color, defaults to false.
	std::shared_ptr<screen_object> lastClickedAction = moveAction; // Holds the last clicked action, defaults to move.
	std::shared_ptr<screen_object> selectedObject; // Holds the currently selected object, if there is one.
	bool selected = false; // Flag to indicate if an object has been selected, so you can only select 1 object at a time.
	bool lock = false; // Flag so only 1 action can be performed per click. set to True after a left mouse button click, and set to false if not.
	
	while (window.isOpen()) {
			  
		window.clear();
		
		for(unsigned int i = 0; i < colors.size(); i++){
			colors[i]->draw(window);
		}
		
		for(unsigned int i = 0; i < actions.size(); i++){
			actions[i]->draw(window);
		}
		
		for(unsigned int i = 0; i < newObjects.size(); i++){
			newObjects[i]->draw(window);
		}
		
		for(unsigned int i = 0; i < screen_objects.size(); i++){
			screen_objects[i]->draw(window);
		}
		
		window.display();
		
		// Checks if the left mouse button is pressed.
		if(sf::Mouse::isButtonPressed( sf::Mouse::Left )){
			// If an object is selected and the mouse is clicked again, let go of the selected object.
			if(selected && ! lock){
				selected = false;
			}
			// If the left mouse button is not locked, check if the mouse clicked an object.
			else if(! lock){
				// Gets the current mouse location, and converts it the vector2i to a vector2f,
				// so it can be compared with the Floatrects the screen_objects return.
				sf::Vector2i mouse = sf::Mouse::getPosition( window );
				sf::Vector2f floatMouse = sf::Vector2f(mouse);
				
				
				// If a color was clicked,
				// change the lastClickedColor to the clicked color,
				// and set the lastClickedWasColor to true.
				for(unsigned i = 0; i < colors.size(); i++){
					sf::FloatRect bounds = colors[i]->getBounds();
					if(bounds.contains(floatMouse)){
						lastClickedColor = colors[i]->returnColor();
						lastClickedWasColor = true;
					}
				}
				
				// If an action is clicked,
				// change the lastClickedAction to the clicked action,
				// and set the lastClickedWasColor to false.
				for(unsigned i = 0; i < actions.size(); i++){
					sf::FloatRect bounds = actions[i]->getBounds();
					if(bounds.contains(floatMouse)){
						lastClickedAction = actions[i];
						lastClickedWasColor = false;
					}
				}
				
				// If a created objects is clicked,
				// change color, select, delete or push to backround depending on the last clicked color or action.
				for(unsigned i = 0; i < screen_objects.size(); i++){
					sf::FloatRect bounds = screen_objects[i]->getBounds();
					if(bounds.contains(floatMouse)){
						
						if(lastClickedWasColor){
							screen_objects[i]->changeColor(lastClickedColor);
						}
						else if(lastClickedAction == moveAction){
							selectedObject = screen_objects[i];
							screen_objects[i]->setOffset(floatMouse);
							selected = true;
						}
						else if(lastClickedAction == deleteAction){
							screen_objects.erase(screen_objects.begin() + i);
						}
						else if(lastClickedAction == pushBackAction){
							std::shared_ptr<screen_object> temp = screen_objects[i];
							screen_objects.erase(screen_objects.begin() + i);
							screen_objects.insert(screen_objects.begin(), temp);
						}
					}
				}
				
				// If no object is currently selected and one of the object that creates new objects is clicked, 
				// create a copy of the clicked object and select it.
				if(!selected){
					for(unsigned i = 0; i < newObjects.size(); i++){
						newObjects[i]->changeColor(lastClickedColor);
						sf::FloatRect bounds = newObjects[i]->getBounds();
						if(bounds.contains(floatMouse)){
							if(true){
								if(newObjects[i] == newCircle){
									selectedObject = std::make_shared<circle>(circle(sf::Vector2f{40, 10}, lastClickedColor, 10));
								}
								if(newObjects[i] == newRectangle){
									selectedObject = std::make_shared<rectangle>(rectangle(sf::Vector2f{40, 40}, lastClickedColor, sf::Vector2f{20, 20}));
								}
								selected = true;
								selectedObject->setOffset(floatMouse);
								screen_objects.push_back(selectedObject);
							}
						}
					}
				}
			}
			// If an left mouse button is clicked set the lock to true.
			lock = true;
		}
		// If the left mouse button is not clicked set the lock to false,
		// if an object is selected move it to the mouse location.
		else{
			if(selected){
				sf::Vector2i mouse = sf::Mouse::getPosition( window );
				sf::Vector2f floatMouse = sf::Vector2f(mouse);
				selectedObject->move(floatMouse);	
				selectedObject->draw(window);
			}
			lock = false;
		}

		sf::Event event;		
		while( window.pollEvent(event) ){
			if( event.type == sf::Event::Closed ){
				window.close();
			}
		}	
	}
}

