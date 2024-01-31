#pragma once

#include "model.hxx"
#include "view.hxx"

class Controller : public ge211::Abstract_game
{
public:
    explicit Controller(int size = 8);

    Controller(int width, int height);
    using Rectangle = ge211::Posn<int>;
    void on_frame(double dt) override;

protected:

    void draw(ge211::Sprite_set&) override;
    View::Dimensions initial_window_dimensions() const override;
    std::string initial_window_title() const override;

private:
    Model model_;
    View  view_;
    bool instruct;
    void on_key(ge211::Key) override;
    void on_mouse_up(ge211::Mouse_button, ge211::Posn<int>) override;
    std::vector<Rectangle> nextmoves;
};
