#pragma once
#ifndef TEXT_FIELD_HPP
#define TEXT_FIELD_HPP
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/String.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

constexpr int CNT_LIMIT = 5;

class TextField{
public:
    TextField(sf::Vector2f location, bool curr = 0);
    void Render(sf::RenderTarget &tgt);
    bool isClicked(float x, float y);
    bool isCurrent();
    void setFalse();
    void setTrue();
    void addLetter(sf::Uint32);
    void pop_back();
    bool isNoEmpty();
    void reset();
    sf::String getString();
private:
    sf::String playerInput;
    sf::Text playerText;
    sf::RectangleShape rectangle;
    bool current = 0;
    sf::Font font;
    int cnt = 0;
};

TextField::TextField(sf::Vector2f location, bool curr){
    rectangle.setSize(sf::Vector2f(1000, 50));
    rectangle.setFillColor(sf::Color::White);
    rectangle.setPosition(location);
    
    font.loadFromFile("../ClearSans.ttf");
    playerText.setFont(font);
    //text.setStyle(sf::Text::Style::Bold);
    playerText.setFillColor(sf::Color::Black);
    playerText.setString("");
    playerText.setCharacterSize(30);
    playerText.setPosition(location.x + 10, location.y + (50 - playerText.getLocalBounds().height) / 2 - 20);
    this->current = curr;
}


void TextField::Render(sf::RenderTarget &tgt){
    tgt.draw(this->rectangle);
    tgt.draw(this->playerText);
}

bool TextField::isClicked(float x, float y){
    if (x > rectangle.getPosition().x && x < (rectangle.getPosition().x + this->rectangle.getSize().x)) {
        if(y > rectangle.getPosition().y && y < (rectangle.getPosition().y + rectangle.getSize().y)) {
            return 1;
        }
    }
    return 0 ;
}

bool TextField::isCurrent(){
    return this->current;
}

void TextField::setFalse(){
    this->current = 0;
}

void TextField::setTrue(){
    this->current = 1;
}


void TextField::addLetter(sf::Uint32 unic){
    size_t temp = playerInput.getSize();
    if (this->cnt > CNT_LIMIT){
            return;
     }
    if(temp == 0 && unic == 32){
        return;
    }
    if(playerInput[temp  - 2] != 32 && playerInput[temp - 1] != 32 && unic != 32){
        if (this->cnt == CNT_LIMIT){
            return;
        }   
        playerInput += sf::Uint32(32);
        this->cnt += 1;
    }
    if(unic == 32 && playerInput[temp - 1] == 32){
        return;
    }
    if(playerInput[temp - 1] == 48){
        playerInput += sf::Uint32(32);
        this->cnt += 1;
    }
    switch (unic){
        case 32:
            if (this->cnt == CNT_LIMIT || playerInput[temp - 1] == 32){
                return;
            }
            playerInput += sf::Uint32(32);
            this->cnt += 1;
            break;
        case 48:
            playerInput += sf::Uint32(48);
            playerInput += sf::Uint32(32);
            this->cnt += 1;
            break;
        default:
            playerInput += unic;
            break;
        }
    playerText.setString(playerInput);
}

void TextField::pop_back(){
    size_t temp = playerInput.getSize();
    if (temp > 0){
        if(playerInput[temp - 1] == 32){
            this->cnt -= 1;
        }
        playerInput.erase(temp - 1);
        playerText.setString(playerInput);
    }
}

bool TextField::isNoEmpty(){
    return playerInput.getSize() > 0;
}

sf::String TextField::getString(){
    return this->playerInput;
}

void TextField::reset(){
    playerText.setString("");
    playerInput.clear();
    cnt = 0;
    return;
}

#endif // TEXT_FIELD_HPP