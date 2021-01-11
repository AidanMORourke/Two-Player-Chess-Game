#pragma once
#include <iostream>

using std::cin;
using std::cout;
using std::endl;
using std::ostream;
#include <string>
using std::string;

enum class Color { Black = -1, White = 1, Empty = 0};
enum class Piece { Empty, Pawn, Knight, Bishop, Rook, Queen, King };

class ChessPiece
{
private:
	Color color_ = Color::Empty;
	Piece piece_ = Piece::Empty;
	bool has_moved_ = false;
	
public:
	ChessPiece() = default;
	ChessPiece(Color color, Piece piece) : color_(color), piece_(piece) {}

	//Setters
	void SetColor(Color color) { color_ = color; }
	void SetPiece(Piece piece) { piece_ = piece; }
	void SetHasMoved(bool has_moved) { has_moved_ = has_moved; }
	
	//Accessors
	Color GetColor() { return color_; }
	Piece GetPiece() { return piece_; }
	bool GetHasMoved() { return has_moved_; }
};	

ostream& operator<<(ostream& out, ChessPiece& chess_piece);

ostream& operator<<(ostream& out, Color& color);

ostream& operator<<(ostream& out, Piece& piece);