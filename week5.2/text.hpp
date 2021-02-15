#ifndef TEXT_HPP
#define TEXT_HPP

#include <SFML/Graphics.hpp>
#include <string>

class text{
private:
	sf::Vector2f position;
	float size;
	sf::Color color;
	std::string font_file;
	std::string string;
	sf::Font font;
	sf::Text text_shape;

public:
	text(sf::Vector2f position, float size, sf::Color color, std::string font_file, std::string string):
        position{ position },
        size{ size },
        color{ color },
		font_file{ font_file },
		string{ string }

    {
		font.loadFromFile(font_file);
		text_shape.setFont(font);
		text_shape.setString(string);
		text_shape.setPosition(position);
		text_shape.setCharacterSize(size);
		text_shape.setFillColor(color);
		text_shape.setStyle(sf::Text::Bold);
		text_shape.setOutlineColor(sf::Color::Black);
		text_shape.setOutlineThickness(1);
    }


	void set_string(const std::string & s){
		string = s;
		text_shape.setString(string);
	}

	void draw( sf::RenderWindow & window ) const{
        window.draw( text_shape );
    }


};

#endif
