#pragma once
#ifndef BUTTON_HPP
#define BUTTON_HPP
#include <string>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <iosfwd>
#include <SFML/Graphics/RectangleShape.hpp>

class Button{
public:
    Button(sf::Vector2f location, std::string text);
    bool isClicked(float x, float y);
    bool setText(std::string);
    void Render(sf::RenderTarget& tgt);

private:
    sf::RectangleShape rectangle;
    sf::Text text;
    bool current;
    sf::Font font;
};


Button::Button(sf::Vector2f location, std::string str){
    rectangle.setPosition(location);
    rectangle.setSize(sf::Vector2f(300, 100));
    rectangle.setFillColor(sf::Color(238, 228, 218));

    font.loadFromFile("../ClearSans.ttf");
    text.setFont(font);
    //text.setStyle(sf::Text::Style::Bold);
    text.setFillColor(sf::Color(119, 110, 101));
    text.setString("Start");
    text.setCharacterSize(50);
    text.setPosition(rectangle.getGlobalBounds().left + (rectangle.getGlobalBounds().width - text.getGlobalBounds().width) / 2, rectangle.getGlobalBounds().top + (rectangle.getGlobalBounds().height - text.getLocalBounds().height) / 2 - 15);
    sf::FloatRect fr = text.getLocalBounds();

    
}

void Button::Render(sf::RenderTarget &tgt){
    tgt.draw(rectangle);
    tgt.draw(text);
    
}

bool Button::isClicked(float x, float y){
    if (x > rectangle.getPosition().x && x < (rectangle.getPosition().x + this->rectangle.getSize().x)) {
        if(y > rectangle.getPosition().y && y < (rectangle.getPosition().y + rectangle.getSize().y)) {
            return 1;
        }
    }
    return 0;

}
#endif // BUTTON_HPP