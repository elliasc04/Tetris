#include "view.hxx"
using Color = ge211::Color;
using Sprite_set = ge211::Sprite_set;

static ge211::Color const square_color {0, 0, 0};
static int const grid_size = 21;

View::View(Model const& model)
        : model_(model),


        square_sprite({grid_size+1,grid_size+1},square_color),



        background({(square_sprite.dimensions().width+1)*10+1,(square_sprite.dimensions().height+1)*20},{72,72,72}),
        Orange({square_sprite.dimensions().width,square_sprite.dimensions().height},{255,165,0}),
        Blue({square_sprite.dimensions().width,square_sprite.dimensions().height},{0,0,255}),
        Red({square_sprite.dimensions().width,square_sprite.dimensions().height},{255,0,0}),
        Yellow({square_sprite.dimensions().width,square_sprite.dimensions().height},{255,255,0}),
        LBlue({square_sprite.dimensions().width,square_sprite.dimensions().height},{135,206,235}),
        Green({square_sprite.dimensions().width,square_sprite.dimensions().height},{0,255,0}),
        Purple({square_sprite.dimensions().width,square_sprite.dimensions().height},{128,0,128}),
        Gray({square_sprite.dimensions().width, square_sprite.dimensions().height},{72,72,72}),
        Lines(),
        Sub(),
        Timer(),
        Screen({300,300},{100,100,100}),
        Vignette({1000,1000},{0,0,0,70}),
        GameOver(),
        winmsg(),
        winmsg2(),
        ctrl(),
        ctrl2(),
        ctrl3(),
        ctrl4()
{ }

void View::draw(Sprite_set& set)
{
    set.add_sprite(background,{119,0},-5);
    int spacing = 1;
    squares.clear();
    for (int row = 0; row < 10; row++){
        for (int col = 0; col < 20; col++){
            if (model_[{row,col}] == Player::OPiece){
                set.add_sprite(Orange, posnmultiply({row,col}),5);
            } else if (model_[{row,col}] == Player::LPiece){
                set.add_sprite(LBlue, posnmultiply({row,col}),5);
            } else if (model_[{row,col}] == Player::SqPiece){
                set.add_sprite(Yellow, posnmultiply({row,col}),5);
            } else if (model_[{row,col}] == Player::TPiece){
                set.add_sprite(Purple, posnmultiply({row,col}),5);
            } else if (model_[{row,col}] == Player::GPiece){
                set.add_sprite(Green, posnmultiply({row,col}),5);
            } else if (model_[{row,col}] == Player::RPiece){
                set.add_sprite(Red, posnmultiply({row,col}),5);
            } else if (model_[{row,col}] == Player::BPiece){
                set.add_sprite(Blue, posnmultiply({row,col}),5);
            } else if (model_[{row,col}] == Player::over){
                set.add_sprite(Gray,posnmultiply({row,col}),5);
            }
            squares.push_back(Rectangle(square_sprite.dimensions().width * row + spacing*row+120,square_sprite.dimensions().height*col + spacing*col,square_sprite.dimensions().width, square_sprite.dimensions().height));
        }
    }
    for (const Rectangle& square : squares) {
        set.add_sprite(square_sprite, {square.x, square.y},-1);
    }

    Player next = model_.on_deck[3];
    Player next1 = model_.on_deck[2];
    Player next2 = model_.on_deck[1];
    Player saved = model_.saved_piece;
    Position p1 = {10,0};
    Position p2 = {10,3};
    Position p3 = {10,6};
    Position s1 = {-5,0};
    if (!model_.is_game_over){
        constructnext(set,next,p1);
        constructnext(set,next1,p2);
        constructnext(set,next2,p3);
        constructnext(set,saved,s1);
    }

    int lines = model_.lines_cleared;
    ge211::Text_sprite::Builder score_builder(scoretext);
    score_builder.color({255,255,255}) << lines;
    Lines.reconfigure(score_builder);
    set.add_sprite(Lines,{395,230},40);

    std::string subs = "Lines Remaining";
    ge211::Text_sprite::Builder sub_builder(subtext);
    sub_builder.color({211,211,211}) << subs;
    Sub.reconfigure(sub_builder);
    set.add_sprite(Sub,{370,270},40);

    float timer = model_.time_;
    ge211::Text_sprite::Builder time_builder(timetext);
    time_builder.color({211,211,211}) << timer;
    Timer.reconfigure(time_builder);
    set.add_sprite(Timer,{385,360},40);

    if (model_.is_game_over){
        for (int row = 0; row < 10; row++){
            for (int col = 0; col<20; col++){
                if (model_[{row,col}] != Player::neither){
                    set.add_sprite(Gray,posnmultiply({row,col}),10);
                }
            }
        }
        set.add_sprite(Vignette,{0,0},100);
        set.add_sprite(Screen,{100,85},101);
        std::string Congratulations;
        Position msgposn = {0,0};
        if (model_.cleared){
            Congratulations = "Congratulations!";
            msgposn = {135,105};

            std::string cleared = "You cleared all 40 lines in";
            ge211::Text_sprite::Builder congrats_builder(timetext);
            congrats_builder.color({200,200,200}) << cleared;
            winmsg.reconfigure(congrats_builder);
            set.add_sprite(winmsg, {150,185},102);

            std::string cleared2 = " seconds!";
            ge211::Text_sprite::Builder congrats2_builder(timetext);
            congrats2_builder.color({200,200,200}) << timer << cleared2;
            winmsg2.reconfigure(congrats2_builder);
            set.add_sprite(winmsg2, {185,203},102);

        } else if (!model_.cleared && model_.instructions == false){
            Congratulations = "Game Over";
            msgposn = {170,105};

            std::string failed = "Sorry, you failed to clear all 40 lines";
            std::string failed2 = "before topping out.";
            ge211::Text_sprite::Builder final_builder(timetext);
            final_builder.color({200,200,200}) << failed;
            winmsg.reconfigure(final_builder);
            set.add_sprite(winmsg, {130,185},102);

            ge211::Text_sprite::Builder final2_builder(timetext);
            final2_builder.color({200,200,200}) << failed2;
            winmsg2.reconfigure(final2_builder);
            set.add_sprite(winmsg2,{185,203},102);
        } else {
            Congratulations = "Controls:";
            msgposn = {185,105};

            std::string failed = "Right, Left, and Down arrow keys move";
            std::string failed2 = "the piece in their direction.";
            ge211::Text_sprite::Builder final_builder(timetext);
            final_builder.color({200,200,200}) << failed;
            winmsg.reconfigure(final_builder);
            set.add_sprite(winmsg, {120,185},102);

            ge211::Text_sprite::Builder final2_builder(timetext);
            final2_builder.color({200,200,200}) << failed2;
            winmsg2.reconfigure(final2_builder);
            set.add_sprite(winmsg2,{160,203},102);

            std::string ctr = "Up arrow rotates CW, D rotates CCW";
            std::string ctr2 = "A flips the piece, C saves it.";
            ge211::Text_sprite::Builder ctr_builder(timetext);
            ctr_builder.color({200,200,200}) << ctr;
            ctrl.reconfigure(ctr_builder);
            set.add_sprite(ctrl, {120,225},102);

            ge211::Text_sprite::Builder ctr2_builder(timetext);
            ctr2_builder.color({200,200,200}) << ctr2;
            ctrl2.reconfigure(ctr2_builder);
            set.add_sprite(ctrl2,{160,243},102);

            std::string ctr3 = "Clear 40 lines as quick as possible.";
            ge211::Text_sprite::Builder ctr3_builder(timetext);
            ctr3_builder.color({200,200,200}) << ctr3;
            ctrl3.reconfigure(ctr3_builder);
            set.add_sprite(ctrl3,{130,290},102);

            std::string ctr4 = "Good Luck! Press B to start.";
            ge211::Text_sprite::Builder ctr4_builder(timetext);
            ctr4_builder.color({200,200,200}) << ctr4;
            ctrl4.reconfigure(ctr4_builder);
            set.add_sprite(ctrl4,{160,313},102);
        }

        ge211::Text_sprite::Builder message_builder(scoretext);
        message_builder.color({255,255,255}) << Congratulations;
        GameOver.reconfigure(message_builder);
        set.add_sprite(GameOver,msgposn,102);
    }
}

void
View::constructnext(Sprite_set& set, Player player, Position posn){
    if (player == Player::LPiece){
        set.add_sprite(LBlue,posnmultiply({posn.x+1,posn.y+1}));
        set.add_sprite(LBlue,posnmultiply({posn.x+2,posn.y+1}));
        set.add_sprite(LBlue,posnmultiply({posn.x+3,posn.y+1}));
        set.add_sprite(LBlue,posnmultiply({posn.x+4,posn.y+1}));
    }else if (player == Player::BPiece){
        set.add_sprite(Blue,posnmultiply({posn.x+1,posn.y+1}));
        set.add_sprite(Blue,posnmultiply({posn.x+1,posn.y+2}));
        set.add_sprite(Blue,posnmultiply({posn.x+2,posn.y+2}));
        set.add_sprite(Blue,posnmultiply({posn.x+3,posn.y+2}));
    }else if (player == Player::OPiece){
        set.add_sprite(Orange,posnmultiply({posn.x+1,posn.y+2}));
        set.add_sprite(Orange,posnmultiply({posn.x+2,posn.y+2}));
        set.add_sprite(Orange,posnmultiply({posn.x+3,posn.y+2}));
        set.add_sprite(Orange,posnmultiply({posn.x+3,posn.y+1}));
    }else if (player == Player::GPiece){
        set.add_sprite(Green,posnmultiply({posn.x+1,posn.y+2}));
        set.add_sprite(Green,posnmultiply({posn.x+2,posn.y+2}));
        set.add_sprite(Green,posnmultiply({posn.x+2,posn.y+1}));
        set.add_sprite(Green,posnmultiply({posn.x+3,posn.y+1}));
    }else if (player == Player::RPiece){
        set.add_sprite(Red,posnmultiply({posn.x+1,posn.y+1}));
        set.add_sprite(Red,posnmultiply({posn.x+2,posn.y+1}));
        set.add_sprite(Red,posnmultiply({posn.x+2,posn.y+2}));
        set.add_sprite(Red,posnmultiply({posn.x+3,posn.y+2}));
    }else if (player == Player::TPiece){
        set.add_sprite(Purple,posnmultiply({posn.x+1,posn.y+2}));
        set.add_sprite(Purple,posnmultiply({posn.x+2,posn.y+2}));
        set.add_sprite(Purple,posnmultiply({posn.x+3,posn.y+2}));
        set.add_sprite(Purple,posnmultiply({posn.x+2,posn.y+1}));
    }else if (player == Player::SqPiece){
        set.add_sprite(Yellow,posnmultiply({posn.x+2,posn.y+1}));
        set.add_sprite(Yellow,posnmultiply({posn.x+3,posn.y+1}));
        set.add_sprite(Yellow,posnmultiply({posn.x+2,posn.y+2}));
        set.add_sprite(Yellow,posnmultiply({posn.x+3,posn.y+2}));
    }
}

View::Position
View::posnmultiply(Position posn){
    Position newposn = {posn.x*23+120,posn.y*23};
    return newposn;
}

View::Dimensions
View::initial_window_dimensions() const
{
    return {model_.all_positions().dimensions().width*grid_size+120,model_.all_positions().dimensions().height*grid_size-3};
}

std::string
View::initial_window_title() const
{
    return "Tetris";
}

