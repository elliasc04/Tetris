
#include "player.hxx"
#include <cstdlib>
using namespace std;


Player
other_player(Player player)
{
    int num = 1 + (rand() % 7);
    switch (player) {
    default:
        return random_player(num);
    }
}

Player
random_player(int num)
{
    if (num < 1 || num > 7){
        throw("random num generated out of bounds");
    }
    if (num == 1){
        return Player::LPiece;
    }
    if (num == 2){
        return  Player::BPiece;
    }
    if (num == 3){
        return Player::OPiece;
    }
    if (num == 4){
        return  Player::SqPiece;
    }
    if (num == 5){
        return  Player::GPiece;
    }
    if (num == 6){
        return  Player::RPiece;
    }
    if (num == 7){
        return  Player::TPiece;
    } else{
        return  Player::LPiece;
    }
}


