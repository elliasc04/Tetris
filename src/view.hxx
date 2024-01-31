#pragma once

#include "model.hxx"

#include <string>
class View
{
public:
    using Dimensions = ge211::Dims<int>;

    using Position = ge211::Posn<int>;

    using Rectangle = ge211::Rect<int>;

    explicit View(Model const&);

    void constructnext(ge211::Sprite_set&, Player, Position);

    void draw(ge211::Sprite_set& set);

    Dimensions initial_window_dimensions() const;

    std::string initial_window_title() const;

private:
    Model const& model_;
    ge211::Rectangle_sprite const square_sprite;
    ge211::Rectangle_sprite const background;
    ge211::Rectangle_sprite const Orange;
    ge211::Rectangle_sprite const Blue;
    ge211::Rectangle_sprite const Red;
    ge211::Rectangle_sprite const Yellow;
    ge211::Rectangle_sprite const LBlue;
    ge211::Rectangle_sprite const Green;
    ge211::Rectangle_sprite const Purple;
    ge211::Rectangle_sprite const Gray;
    ge211::Text_sprite Lines;
    ge211::Text_sprite Sub;
    ge211::Text_sprite Timer;
    ge211::Rectangle_sprite const Screen;
    ge211::Rectangle_sprite const Vignette;
    ge211::Text_sprite GameOver;
    ge211::Text_sprite winmsg;
    ge211::Text_sprite winmsg2;
    ge211::Text_sprite ctrl;
    ge211::Text_sprite ctrl2;
    ge211::Text_sprite ctrl3;
    ge211::Text_sprite ctrl4;
    ge211::Font scoretext {"Roboto-Black.ttf",30};
    ge211::Font subtext {"Roboto-Black.ttf",12};
    ge211::Font timetext {"Roboto-Black.ttf",15};
    std::vector<Rectangle> squares;
    Position posnmultiply(Position);
};
