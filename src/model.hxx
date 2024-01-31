#pragma once

#include "player.hxx"
#include "board.hxx"

#include <ge211.hxx>

#include <iostream>
#include <vector>
class Model
{
public:
    using Dimensions = Board::Dimensions;

    using Position = Board::Position;

    using Rectangle = Board::Rectangle;

    explicit Model(int size = 8);

    Model(int width, int height);

    Rectangle all_positions() const;

    Player turn() const
    { return turn_; }

    bool Hits_Left();
    bool Hits_Right();
    bool Hits_Bottom();
    bool Hits_Ceiling();

    Player operator[](Position) const;

    Board board_;
    void on_frame(double);
    void check_clear();
    bool line_full(std::vector<Position>);
    void line_clear(std::vector<Position>);
    void fill_in(std::vector<Position>);
    int lines_cleared;
    int savedthresh;

    float time_;
    float frames;
    bool is_game_over;
    bool instructions;
    bool cleared;
    bool saved;
    void clear_();
    void set_();
    void Rotate();
    void Hard_Drop();
    void Soft_Drop();
    void Left();
    void Right();
    Player saved_piece;
    void Save_Piece();
    using Pos =ge211::Posn<int>;
    std::vector<Player> on_deck;
    void Set_Piece();
    Player turn_;
#ifdef CS211_TESTING

#endif

private:

    // vector of all positions that make up the current piece
    std::vector<Pos> Current;

    // temporary placeholder to assign a new current
    std::vector<Pos> Temp;

    // timer
    float elapsed;



    void Make_Move(Dimensions);

    bool Rotate_Bottom();
    bool Rotate_Left();
    bool Rotate_Right();

    bool find_vec(Position, std::vector<Position>);
};

