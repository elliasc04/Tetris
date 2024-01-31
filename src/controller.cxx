#include "controller.hxx"

Controller::Controller(int width, int height)
        : model_(width, height),
          view_(model_)
{ instruct = false;}

void
Controller::draw(ge211::Sprite_set& sprites)
{
    view_.draw(sprites);
}

void
Controller::on_key(ge211::Key key){
    if (key==ge211::Key::code('b') && instruct == false){
        model_.is_game_over = false;
        instruct = true;
        model_.instructions = false;
    }
    if (!model_.is_game_over){
        if (key == ge211::Key::left()) {
            model_.Left();

        } else if (key == ge211::Key::right()) {
            model_.Right();

        } else if (key == ge211::Key::up()) {
            model_.Rotate();

        } else if (key == ge211::Key::down()){
            model_.Soft_Drop();
            model_.check_clear();
        } else if (key==ge211::Key::code(' ')){
            model_.Hard_Drop();
            model_.check_clear();
        } else if (key==ge211::Key::code('d')){
            model_.Rotate();
            model_.Rotate();
            model_.Rotate();
        } else if (key==ge211::Key::code('a')){
            model_.Rotate();
            model_.Rotate();
        } else if (key==ge211::Key::code('c')){
            model_.Save_Piece();
        }
    }

}

void
Controller::on_mouse_up(ge211::Mouse_button, ge211::Posn<int> position){
}

View::Dimensions
Controller::initial_window_dimensions() const
{
    return view_.initial_window_dimensions();
}

void
Controller::on_frame(double dt){
    model_.on_frame(dt);
}

std::string
Controller::initial_window_title() const
{
    return view_.initial_window_title();
}

