#pragma once

#include "player.hxx"
#include "position_set.hxx"

#include <ge211.hxx>

#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

class Board
{
public:
    using Dimensions = ge211::Dims<int>;
    using Position = ge211::Posn<int>;
    using Rectangle = ge211::Rect<int>;
    class reference;

private:
    Dimensions dims_;
    Position_set LPiece_;
    Position_set BPiece_;
    Position_set OPiece_;
    Position_set SqPiece_;
    Position_set GPiece_;
    Position_set RPiece_;
    Position_set TPiece_;

public:
    explicit Board(Dimensions dims);
    Dimensions dimensions() const;
    bool good_position(Position) const;

    Player operator[](Position pos) const;

    reference operator[](Position pos);

    void set_all(Position_set, Player);

    Rectangle all_positions() const;

    friend bool operator==(Board const&, Board const&);

private:

    Player get_(Position where) const;
    void set_(Position where, Player who);
    void bounds_check_(Position where) const;

#ifdef CS211_TESTING

#endif
};

bool
operator!=(Board const&, Board const&);

class Board::reference
{
    Board& board_;
    Position pos_;

public:
    reference& operator=(reference const&) noexcept;

    reference& operator=(Player) noexcept;

    operator Player() const noexcept;

private:
    friend class Board;

    reference(Board&, Position) noexcept;
};
