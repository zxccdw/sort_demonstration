#pragma once

#ifndef VISUAL_HPP
#include <vector>
#include <iostream>
#include <string>
#include "shape_field.hpp"
#include <time.h>
#include <chrono>
#include <thread>

const float SIZE = 100;
const float FIELD_MARGIN = 20;

class Visual{
private:
	std::vector <int> ar;
	std::vector <ShapeField> shapes;
	sf::Vector2f start_position = sf::Vector2f(50, 50);
	sf::Font font;
	sf::String temp_str;
	sf::Text temp_text;
	sf::RectangleShape temp_shape;
public:
	Visual() = default;
	Visual& operator=(const Visual&) = default;
	Visual(const sf::String &);
	void Render(sf::RenderWindow &tgt);
	void catchString(sf::String str);
	void swapCoords(ShapeField& lhs, ShapeField& rhs);

};

void Visual::catchString(sf::String str){
	temp_shape.setSize(sf::Vector2f(SIZE, SIZE));
	size_t size = str.getSize();
	if(str[size - 1] != 32){
		size += 1;
		str += sf::Uint32(32);
	}
	font.loadFromFile("../ClearSans.ttf");
	temp_text.setFont(font);
	int temp_cnt = 0;
	size_t i = 0;
	if(str[0] == 32){ // space
		i += 1;
		std::cout << "bad space\n";
	}
	std::cout << str.toAnsiString() << std::endl;
	for(; i < size; ++i){
		std::cout << str[i] << std::endl;
		if(str[i] == 32){ // space
			temp_shape.setPosition(sf::Vector2f(start_position.x + FIELD_MARGIN * temp_cnt + temp_shape.getGlobalBounds().width * temp_cnt, start_position.y));
			temp_text.setString(temp_str);
			temp_text.setPosition(temp_shape.getGlobalBounds().left + (temp_shape.getGlobalBounds().width - temp_text.getGlobalBounds().width) / 2 - 2.5, start_position.y + (SIZE / 2 - temp_text.getGlobalBounds().height));
			temp_text.setFillColor(sf::Color::Black);
			temp_text.setCharacterSize(30);
			shapes.push_back(ShapeField(temp_text, temp_shape));
			temp_str.clear();
			temp_cnt += 1;
			std::cout << temp_str.toAnsiString() << std::endl;
		}
		else{
			temp_str += str[i];
		}
	}
}
void Visual::swapCoords(ShapeField &lhs, ShapeField &rhs){
	int temp = lhs.getNumb();
	lhs.setText(rhs.getNumb());
	rhs.setText(temp);
}

void Visual::Render(sf::RenderWindow &tgt){
	for(auto& i: shapes){
		i.Render(tgt);
	}
	tgt.display();
	std::this_thread::sleep_for(std::chrono::milliseconds(200));
	for(int i = 0; i < shapes.size(); ++i){
		if(!tgt.isOpen()){
			return;
		}
		for(int j = i + 1; j < shapes.size(); ++j){
			if(shapes[i].getNumb() > shapes[j].getNumb()){
				swapCoords(shapes[i], shapes[j]);
			}
			else{
				break;
			}
		}
		tgt.clear(sf::Color(187, 173, 160));
		for(auto& i: shapes){
			i.Render(tgt);
		}
		tgt.display();
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}
	shapes.clear();
	return;
}
#endif //VISUAL_HPP