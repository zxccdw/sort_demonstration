#pragma once

#ifndef SHAPE_FIELD_HPP

class ShapeField{
public:
    ShapeField(const sf::Text& temp_text, const sf::RectangleShape& temp_shape);
    int getNumb();
    void Render(sf::RenderTarget& tgt);
    void setText(int numb);
private:
    sf::Text text;
    sf::RectangleShape shape;
};

ShapeField::ShapeField(const sf::Text& temp_text, const sf::RectangleShape& temp_shape){
    this->text = temp_text;
    this->shape = temp_shape;
}

int ShapeField::getNumb(){
    //std::cout << std::stoi(text.getString().toAnsiString());
    return std::stoi(text.getString().toAnsiString());
}

void ShapeField::Render(sf::RenderTarget& tgt){
    tgt.draw(this->shape);
    tgt.draw(this->text);

}

void ShapeField::setText(int numb){
    this->text.setString(sf::String(std::to_string(numb)));

}

#endif // SHAPE_FIELD_HPP