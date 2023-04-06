#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/System/Clock.hpp>
#include "button.hpp"
#include "text_field.hpp"
#include "visual.hpp"
#include <iostream>


int main(){
	sf::Clock animClock;
	srand(time(NULL));

	sf::RenderWindow window(sf::VideoMode(1200, 600), "bubble sort", sf::Style::Titlebar | sf::Style::Close);
	sf::Event e;
	sf::Vector2f pos(window.getSize().x / 2 - 150, 400);
	Button But(pos, "123");
	TextField Field(sf::Vector2f(10, 10));
	int page = 1;
	Visual VisualPage;
	while (window.isOpen()) {
		
		while (window.pollEvent(e) && page == 1) {
			if (e.type == sf::Event::Closed)
				window.close();
			if (page == 1){
				if (e.type == sf::Event::MouseButtonPressed){
					if(But.isClicked(e.mouseButton.x, e.mouseButton.y) && Field.isNoEmpty()){
						page = 2;
						VisualPage.catchString(Field.getString());
						std::cout << "Button start game\n";
						continue;
					}

					if(Field.isClicked(e.mouseButton.x, e.mouseButton.y)){
						Field.setTrue();
						std::cout << "Clicked Field" << std::endl;
						
					}
					else{
						Field.setFalse();
					}
					//std::cout << e.mouseButton.x << " " << e.mouseButton.y << std::endl;
				}
				if (e.type == sf::Event::TextEntered && Field.isCurrent()){
					/*
					if(e.text.unicode == 0){ // 8 delete
						//Field.pop_back();
						std::cout << "1";
					}*/
					if ((e.text.unicode >= 48 && e.text.unicode <= 57) || e.text.unicode == 32){
						Field.addLetter(e.text.unicode);
						std::cout << "Text Entered\n" << e.text.unicode << std::endl; // 48 - 57 0 - 9 32 - space
					}
					//std::cout << e.text.unicode << std::endl;
					
					if (e.text.unicode == 8){
						Field.pop_back();
						std::cout << "Delete Entered" << std::endl;
					}
				}
			}

		}
		window.clear(sf::Color(187, 173, 160));
		switch(page){
			case 1:
				But.Render(window);
				Field.Render(window);
				break;
			case 2:
				VisualPage.Render(window);
				Field.reset();
				page = 1;
				//window.clear(sf::Color(187, 173, 160));
				break;
		}

		window.display();
	}
}
