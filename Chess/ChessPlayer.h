#pragma once
#include <map>

#include "ChessPiece.h"

using std::map;
class ChessPlayer
{
private:
	Color color_ = Color::Empty;
	bool is_in_check_ = false;
	bool king_taken = false;
	std::pair<int,int> king_attack_piece_;
	
	map<Color, int> default_king_rows_ = { {Color::White, 7}, {Color::Black, 0} };
	std::pair<int, int> king_position_;

public:
	// A player can be initialized either with no parameters, or with a color.
	ChessPlayer() = default;
	ChessPlayer(Color color) { color_ = color, king_position_ = std::make_pair(default_king_rows_[color_], 4); }

	Color GetColor() { return color_; }
	std::pair<int, int> GetKingPosition() { return king_position_; }
	bool GetIsInCheck() { return is_in_check_; }
	std::pair<int,int> GetKingAttackPiece() { return king_attack_piece_; }
	
	void SetKingPosition(std::pair<int, int> king_position) { king_position_ = king_position; }
	void SetCheck(bool check) { is_in_check_ = check; }
	void SetKingAttackPiece(std::pair<int,int> king_attack_piece) { king_attack_piece_ = king_attack_piece; }
};