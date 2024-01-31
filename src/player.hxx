#pragma once

#include <iostream>
#include <queue>

enum class Player
{
    LPiece,
    BPiece,
    OPiece,
    SqPiece,
    GPiece,
    TPiece,
    RPiece,
    neither,
    over,
};
Player other_player(Player);
Player random_player(int);

