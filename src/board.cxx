#include "board.hxx"

using namespace ge211;

Board::Board(Dimensions dims)
        : dims_(dims)
{
}

Board::Dimensions
Board::dimensions() const
{
    return dims_;
}

bool
Board::good_position(Position pos) const
{
    return 0 <= pos.x && pos.x < dims_.width &&
           0 <= pos.y && pos.y < dims_.height;
}

Player
Board::operator[](Position pos) const
{
    bounds_check_(pos);
    return get_(pos);
}

Board::reference
Board::operator[](Position pos)
{
    bounds_check_(pos);
    return reference(*this, pos);
}

Board::Rectangle
Board::all_positions() const
{
    return Rectangle::from_top_left(the_origin, dims_);
}

bool
operator==(Board const& b1, Board const& b2)
{
    return b1.dims_ == b2.dims_ &&
           b1.LPiece_ == b2.LPiece_ &&
            b1.BPiece_ == b2.BPiece_ &&
            b1.OPiece_ == b2.OPiece_ &&
            b1.SqPiece_ == b2.SqPiece_ &&
            b1.TPiece_ == b2.TPiece_ &&
            b1.GPiece_ == b2.GPiece_ &&
            b1.RPiece_ == b2.RPiece_;
}

Player
Board::get_(Position pos) const
{
    if (LPiece_[pos]) {
        return Player::LPiece;
    } else if (BPiece_[pos]) {
        return Player::BPiece;
    } else if (OPiece_[pos]) {
        return Player::OPiece;
    } else if (SqPiece_[pos]) {
        return Player::SqPiece;
    } else if (TPiece_[pos]) {
        return Player::TPiece;
    } else if (GPiece_[pos]) {
        return Player::GPiece;
    } else if (RPiece_[pos]) {
        return Player::RPiece;
    } else {
        return Player::neither;
    }
}

void
Board::set_(Position pos, Player player)
{
    switch (player) {
    case Player::LPiece:
        LPiece_[pos] = true;
        BPiece_[pos] = false;
        OPiece_[pos] = false;
        SqPiece_[pos] = false;
        TPiece_[pos] = false;
        GPiece_[pos] = false;
        RPiece_[pos] = false;
        break;
        case Player::BPiece:
            LPiece_[pos] = false;
            BPiece_[pos] = true;
            OPiece_[pos] = false;
            SqPiece_[pos] = false;
            TPiece_[pos] = false;
            GPiece_[pos] = false;
            RPiece_[pos] = false;
            break;
        case Player::OPiece:
            LPiece_[pos] = false;
            BPiece_[pos] = false;
            OPiece_[pos] = true;
            SqPiece_[pos] = false;
            TPiece_[pos] = false;
            GPiece_[pos] = false;
            RPiece_[pos] = false;
            break;
        case Player::SqPiece:
            LPiece_[pos] = false;
            BPiece_[pos] = false;
            OPiece_[pos] = false;
            SqPiece_[pos] = true;
            TPiece_[pos] = false;
            GPiece_[pos] = false;
            RPiece_[pos] = false;
            break;
        case Player::TPiece:
            LPiece_[pos] = false;
            BPiece_[pos] = false;
            OPiece_[pos] = false;
            SqPiece_[pos] = false;
            TPiece_[pos] = true;
            GPiece_[pos] = false;
            RPiece_[pos] = false;
            break;
        case Player::GPiece:
            LPiece_[pos] = false;
            BPiece_[pos] = false;
            OPiece_[pos] = false;
            SqPiece_[pos] = false;
            TPiece_[pos] = false;
            GPiece_[pos] = true;
            RPiece_[pos] = false;
            break;
        case Player::RPiece:
            LPiece_[pos] = false;
            BPiece_[pos] = false;
            OPiece_[pos] = false;
            SqPiece_[pos] = false;
            TPiece_[pos] = false;
            GPiece_[pos] = false;
            RPiece_[pos] = true;
            break;

    default:
        LPiece_[pos] = false;
        BPiece_[pos] = false;
        OPiece_[pos] = false;
        SqPiece_[pos] = false;
        TPiece_[pos] = false;
        GPiece_[pos] = false;
        RPiece_[pos] = false;
    }
}

void
Board::set_all(Position_set pos_set, Player player)
{
    switch (player) {
    case Player::LPiece:
        LPiece_ |= pos_set;
        OPiece_ &= ~pos_set;
        BPiece_ &= ~pos_set;
        SqPiece_ &= ~pos_set;
        TPiece_ &= ~pos_set;
        RPiece_ &= ~pos_set;
        GPiece_ &= ~pos_set;
        break;

        case Player::OPiece:
            LPiece_ &= ~pos_set;
            OPiece_ |= pos_set;
            BPiece_ &= ~pos_set;
            SqPiece_ &= ~pos_set;
            TPiece_ &= ~pos_set;
            RPiece_ &= ~pos_set;
            GPiece_ &= ~pos_set;
            break;
        case Player::BPiece:
            LPiece_ &= ~pos_set;
            OPiece_ &= ~pos_set;
            BPiece_ |= pos_set;
            SqPiece_ &= ~pos_set;
            TPiece_ &= ~pos_set;
            RPiece_ &= ~pos_set;
            GPiece_ &= ~pos_set;
            break;
        case Player::SqPiece:
            LPiece_ &= ~pos_set;
            OPiece_ &= ~pos_set;
            BPiece_ &= ~pos_set;
            SqPiece_ |= pos_set;
            TPiece_ &= ~pos_set;
            RPiece_ &= ~pos_set;
            GPiece_ &= ~pos_set;
            break;
        case Player::TPiece:
            LPiece_ &= ~pos_set;
            OPiece_ &= ~pos_set;
            BPiece_ &= ~pos_set;
            SqPiece_ &= ~pos_set;
            TPiece_ |= pos_set;
            RPiece_ &= ~pos_set;
            GPiece_ &= ~pos_set;
            break;
        case Player::RPiece:
            LPiece_ &= ~pos_set;
            OPiece_ &= ~pos_set;
            BPiece_ &= ~pos_set;
            SqPiece_ &= ~pos_set;
            TPiece_ &= ~pos_set;
            RPiece_ |= pos_set;
            GPiece_ &= ~pos_set;
            break;
        case Player::GPiece:
            LPiece_ &= ~pos_set;
            OPiece_ &= ~pos_set;
            BPiece_ &= ~pos_set;
            SqPiece_ &= ~pos_set;
            TPiece_ &= ~pos_set;
            RPiece_ &= ~pos_set;
            GPiece_ |= pos_set;
            break;



    default:
        LPiece_ &= ~pos_set;
            OPiece_ &= ~pos_set;
            BPiece_ &= ~pos_set;
            SqPiece_ &= ~pos_set;
            TPiece_ &= ~pos_set;
            RPiece_ &= ~pos_set;
            GPiece_ &= ~pos_set;
    }
}

void
Board::bounds_check_(Position pos) const
{
    if (!good_position(pos)) {
        throw Client_logic_error("Board: position out of bounds");
    }
}

bool
operator!=(Board const& b1, Board const& b2)
{
    return !(b1 == b2);
}


Board::reference::reference(Board& board, Position pos) noexcept
        : board_(board),
          pos_(pos)
{ }

Board::reference&
Board::reference::operator=(reference const& that) noexcept
{
    *this = Player(that);
    return *this;
}

Board::reference&
Board::reference::operator=(Player player) noexcept
{
    board_.set_(pos_, player);
    return *this;
}

Board::reference::operator Player() const noexcept
{
    return board_.get_(pos_);
}