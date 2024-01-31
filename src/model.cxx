#include "model.hxx"

using namespace ge211;

Model::Model(int size)
        : Model(size, size)
{}

Model::Model(int width, int height)
        : board_({width, height})
{
    is_game_over = true;

    // change to true when ready to work on the starting page.
    instructions = true;
    std::time_t time();

    saved_piece = Player::neither;
    lines_cleared = 40;
    savedthresh = 0;
    cleared = false;
    time_ = 0;
    frames = 0;
    saved = false;
    on_deck = {other_player(other_player(Player::OPiece)),other_player(other_player(Player::SqPiece)),other_player(Player::LPiece),other_player(Player::LPiece)};
    Set_Piece();
}

Model::Rectangle
Model::all_positions() const
{
    return board_.all_positions();
}

void
Model::clear_(){
    int i = 0;
    for (Position posn : Current){
        if (i <= 3){
            board_[posn] = Player::neither;
        }
        i++;
    }
}

void
Model::set_(){
    int i = 0;
    for (Position posn : Current){
        if (i<=3){
            board_[posn] = turn_;
        }
        i++;
    }
}

Player
Model::operator[](Position pos) const
{
    return board_[pos];
}

void
Model::Set_Piece(){
    turn_ = on_deck[3];
    on_deck[3] = on_deck[2];
    on_deck[2] = on_deck[1];
    on_deck[1] = on_deck[0];
    if (turn_ == Player::OPiece){
        Current = {{4,1},{5,1},{6,1},{6,0},{0,0}};
    }
    if (turn_ == Player::BPiece){
        Current = {{4,1},{5,1},{6,1},{4,0},{0,0}};
    }
    if (turn_ == Player::LPiece){
        Current = {{4,1},{5,1},{6,1},{7,1},{0,0}};
    }
    if (turn_ == Player::GPiece){
        Current = {{4,1},{5,1},{5,0},{6,0},{0,0}};
    }
    if (turn_ == Player::RPiece){
        Current = {{4,0},{5,0},{5,1},{6,1},{0,0}};
    }
    if (turn_ == Player::TPiece){
        Current = {{4,1},{5,1},{6,1},{5,0},{0,0}};
    }
    if (turn_ == Player::SqPiece){
        Current = {{5,1},{6,1},{5,0},{6,0},{0,0}};
    }
    for (Position posn : Current){
        if (board_[posn] != Player::neither){
            is_game_over = true;
            turn_ = Player::neither;
        }
    }
    set_();
}

void
Model::Right(){
    if (Hits_Right()){
        return;
    }
    Make_Move({1,0});
}

void
Model::Left(){
    if (Hits_Left()){
        return;
    }
    Make_Move({-1,0});
}

void
Model::Soft_Drop(){
    if (Hits_Bottom()){
        return;
    }
    set_();
    Make_Move({0,1});
}

void
Model::Hard_Drop(){
    Dimensions down = {0,1};
    while(!Hits_Bottom()){
        Make_Move({down});
    }
}

void
Model::Make_Move(Dimensions dim){
    clear_();
    Position rotation = Current[4];
    Temp.clear();
    Temp = Current;
    Current.clear();
    int i = 0;
    for (Position posn : Temp){
        if (i<=3){
            Current.push_back({posn + dim});
        }
        i++;
    }
    Current.push_back(rotation);
    set_();
}

bool
Model::Hits_Ceiling(){
    int min = 0;
    for (Position posn : Current){
        if (posn.y < min){
            min = posn.y;
        }
    }
    if(min > 0){
        return false;
    }
    min = min*(-1);
    Current[0].y = Current[0].y + min;
    Current[1].y = Current[1].y + min;
    Current[2].y = Current[2].y + min;
    Current[3].y = Current[3].y + min;
    return true;
}

bool
Model::Rotate_Bottom(){
    int min = 19;
    int max = 0;
    for (Position posn : Current){
        if (board_[posn] == Player::neither &&  posn.y > max){
            max = posn.y;
        }
        if (board_[posn] != Player::neither && posn.y < min){
            min = posn.y;
        }
    }
    int diff = max - min;
    if(diff <= 0){
        return false;
    }
    Current[0].y = Current[0].y - diff;
    Current[1].y = Current[1].y - diff;
    Current[2].y = Current[2].y - diff;
    Current[3].y = Current[3].y - diff;
    return true;
}

bool
Model::Rotate_Left(){
    int min = 0;
    for (Position posn : Current){
        if (posn.x < 0){
            min = posn.x;
        }
    }
    if(min >= 0){
        return false;
    }
    int diff = 0-min;
    Current[0].x = Current[0].x + diff;
    Current[1].x = Current[1].x + diff;
    Current[2].x = Current[2].x + diff;
    Current[3].x = Current[3].x + diff;
    return true;
}

bool
Model::Rotate_Right(){
    int min = 9;
    for (Position posn : Current){
        if (posn.x > min){
            min = posn.x;
        }
    }
    if(min <= 9){
        return false;
    }
    min = min - 9;
    Current[0].x = Current[0].x - min;
    Current[1].x = Current[1].x - min;
    Current[2].x = Current[2].x - min;
    Current[3].x = Current[3].x - min;
    return true;
}

void Model::Rotate(){
    clear_();
    if (turn_ == Player::OPiece){
        int i = 0;
        Position center = {0,0};
        for (Position posn : Current){
            if (i == 1){
                center = posn;
            }
            if (i == 4){
                if (posn.x % 4 == 0){
                    Current = {{center.x,center.y+1},center,{center.x,center.y-1},{center.x+1,center.y+1},{1,0}};
                }
                if (posn.x % 4 == 1){
                    Current = {{center.x-1,center.y},center,{center.x+1,center.y},{center.x-1,center.y+1},{2,0}};
                }
                if (posn.x % 4 == 2){
                    Current = {{center.x,center.y+1},center,{center.x,center.y-1},{center.x-1,center.y-1},{3,0}};
                }
                if (posn.x % 4 == 3){
                    Current = {{center.x-1,center.y},center,{center.x+1,center.y},{center.x+1,center.y-1},{0,0}};
                }
            }
            i++;
        }
    }
    if (turn_ == Player::BPiece){
        int i = 0;
        Position center = {0,0};
        for (Position posn : Current){
            if (i == 1){
                center = posn;
            }
            if (i == 4){
                if (posn.x % 4 == 0){
                    Current = {{center.x,center.y+1},center,{center.x,center.y-1},{center.x+1,center.y-1},{1,0}};
                }
                if (posn.x % 4 == 1){
                    Current = {{center.x-1,center.y},center,{center.x+1,center.y},{center.x+1,center.y+1},{2,0}};
                }
                if (posn.x % 4 == 2){
                    Current = {{center.x,center.y+1},center,{center.x,center.y-1},{center.x-1,center.y+1},{3,0}};
                }
                if (posn.x % 4 == 3){
                    Current = {{center.x-1,center.y},center,{center.x+1,center.y},{center.x-1,center.y-1},{0,0}};
                }
            }
            i++;
        }
    }
    if (turn_ == Player::GPiece){
        int i = 0;
        Position center = {0,0};
        for (Position posn : Current){
            if (i == 1){
                center = posn;
            }
            if (i == 4){
                if (posn.x % 4 == 0){
                    Current = {{center.x,center.y-1},center,{center.x+1,center.y},{center.x+1,center.y+1},{1,0}};
                }
                if (posn.x % 4 == 1){
                    Current = {{center.x+1,center.y},center,{center.x,center.y+1},{center.x-1,center.y+1},{2,0}};
                }
                if (posn.x % 4 == 2){
                    Current = {{center.x-1,center.y},center,{center.x,center.y+1},{center.x-1,center.y-1},{3,0}};
                }
                if (posn.x % 4 == 3){
                    Current = {{center.x+1,center.y},center,{center.x,center.y+1},{center.x-1,center.y+1},{0,0}};
                }
            }
            i++;
        }
    }
    if (turn_ == Player::LPiece){
        int i = 0;
        Position center = {0,0};
        for (Position posn : Current){
            if (i == 2){
                center = posn;
            }
            if (i == 4){
                if (posn.x % 4 == 0){
                    Current = {{center.x,center.y-2},center,{center.x,center.y-1},{center.x,center.y+1},{1,0}};
                }
                if (posn.x % 4 == 1){
                    Current = {{center.x-2,center.y},center,{center.x-1,center.y},{center.x+1,center.y},{2,0}};
                }
                if (posn.x % 4 == 2){
                    Current = {{center.x,center.y+1},center,{center.x,center.y+2},{center.x,center.y-1},{3,0}};
                }
                if (posn.x % 4 == 3){
                    Current = {{center.x-1,center.y-1},
                               {center.x,center.y-1},{center.x+1,center.y-1},{center.x+2,center.y-1},{0,0}};
                }
            }
            i++;
        }
    }
    if (turn_ == Player::RPiece){
        int i = 0;
        Position center = {0,0};
        for (Position posn : Current){
            if (i == 1){
                center = posn;
            }
            if (i == 4){
                if (posn.x % 4 == 0){
                    Current = {{center.x+1,center.y},center,{center.x,center.y+1},{center.x+1,center.y-1},{1,0}};
                }
                if (posn.x % 4 == 1){
                    Current = {{center.x,center.y-1},center,{center.x+1,center.y},{center.x-1,center.y-1},{2,0}};
                }
                if (posn.x % 4 == 2){
                    Current = {{center.x,center.y-1},center,{center.x-1,center.y},{center.x-1,center.y+1},{3,0}};
                }
                if (posn.x % 4 == 3){
                    Current = {{center.x+1,center.y},center,{center.x,center.y-1},{center.x-1,center.y-1},{0,0}};
                }
            }
            i++;
        }
    }
    if (turn_ == Player::TPiece){
        int i = 0;
        Position center = {0,0};
        for (Position posn : Current){
            if (i == 1){
                center = posn;
            }
            if (i == 4){
                if (posn.x % 4 == 0){
                    Current = {{center.x,center.y-1},center,{center.x,center.y+1},{center.x+1,center.y},{1,0}};
                }
                if (posn.x % 4 == 1){
                    Current = {{center.x-1,center.y},center,{center.x+1,center.y},{center.x,center.y+1},{2,0}};
                }
                if (posn.x % 4 == 2){
                    Current = {{center.x,center.y-1},center,{center.x,center.y+1},{center.x-1,center.y},{3,0}};
                }
                if (posn.x % 4 == 3){
                    Current = {{center.x+1,center.y},center,{center.x-1,center.y},{center.x,center.y-1},{0,0}};
                }
            }
            i++;
        }
    }
    Hits_Ceiling();
    Rotate_Left();
    Rotate_Right();
    Rotate_Bottom();
    set_();
}



bool
Model::find_vec(Position posn, std::vector<Position> vector){
    for (Position pos : vector){
        if (posn.x == pos.x && posn.y == pos.y){
            return true;
        }
    }
    return false;
}

bool
Model::Hits_Left(){
    int i = 0;
    for (Position posn : Current){
        if (i<=3){
            if (posn.x == 0){
                return true;
            }
            if (board_[{posn.x-1,posn.y}] != Player::neither && !find_vec({posn.x-1,posn.y},Current)){
                return true;
            }
        }
        i++;
    }
    return false;
}
bool
Model::Hits_Right(){
    int i = 0;
    for (Position posn : Current){
        if (i<=3){
            if (posn.x == 9){
                return true;
            }
            if (board_[{posn.x+1,posn.y}] != Player::neither && !find_vec({posn.x+1,posn.y},Current)){
                return true;
            }
        }
        i++;
    }
    return false;
}

bool
Model::Hits_Bottom(){
    int i = 0;
    for (Position posn : Current){
        if (i<=3){
            if (posn.y == 19){
                on_deck[0] = other_player(turn_);
                elapsed = 0;
                Set_Piece();
                return true;
            }
            if (board_[{posn.x,posn.y+1}] != Player::neither && !find_vec({posn.x,posn.y+1},Current)){
                on_deck[0] = other_player(turn_);
                elapsed = 0;
                Set_Piece();
                return true;
            }
        }
        i++;
    }
    savedthresh = 0;
    return false;
}



void
Model::check_clear(){
    for (int i = 0; i <= 19; i++){
        std::vector<Position> row = {{0,i},{1,i},{2,i},{3,i},{4,i},{5,i},{6,i},{7,i},{8,i},{9,i}};
        if (line_full(row)){
            fill_in(row);
        }
    }
}

bool
Model::line_full(std::vector<Position> vec){
    for (Position posn : vec){
        if (board_[posn] == Player::neither){
            return false;
        }
    }
    return true;
}

void
Model::fill_in(std::vector<Position> vec){
    Dimensions up = {0,-1};
    clear_();
    for (int i = 0; i < 10; i++){
        while(vec[i].y > 0){
            board_[vec[i]] = board_[vec[i] + up];
            vec[i] = vec[i] + up;
        }
    }
    lines_cleared -= 1;
    if (lines_cleared <= 0){
        is_game_over = true;
        turn_ = Player::neither;
        cleared = true;
    }
    set_();
}

void
Model::Save_Piece(){
    if (saved == false){
        clear_();
        saved_piece = turn_;
        on_deck[0] = other_player(turn_);
        elapsed = 0;
        Set_Piece();
        saved = true;
        savedthresh ++;
    } else if (saved == true && savedthresh < 1){
        Player temp = turn_;
        turn_ = saved_piece;
        saved_piece = temp;
        clear_();
        if (turn_ == Player::OPiece){
            Current = {{4,1},{5,1},{6,1},{6,0},{0,0}};
        }
        if (turn_ == Player::BPiece){
            Current = {{4,1},{5,1},{6,1},{4,0},{0,0}};
        }
        if (turn_ == Player::LPiece){
            Current = {{4,1},{5,1},{6,1},{7,1},{0,0}};
        }
        if (turn_ == Player::GPiece){
            Current = {{4,1},{5,1},{5,0},{6,0},{0,0}};
        }
        if (turn_ == Player::RPiece){
            Current = {{4,0},{5,0},{5,1},{6,1},{0,0}};
        }
        if (turn_ == Player::TPiece){
            Current = {{4,1},{5,1},{6,1},{5,0},{0,0}};
        }
        if (turn_ == Player::SqPiece){
            Current = {{5,1},{6,1},{5,0},{6,0},{0,0}};
        }
        for (Position posn : Current){
            if (board_[posn] != Player::neither){
                is_game_over = true;
                turn_ = Player::neither;
            }
        }
        set_();
        savedthresh ++;
    }
}

void
Model::on_frame(double dt){
    if (!is_game_over){
        elapsed += dt;
        if (elapsed > 0.75){
            Soft_Drop();
            elapsed = 0;
        }
        time_ += dt;
        if (time_<1){
            frames += 1;
        }
    }
}