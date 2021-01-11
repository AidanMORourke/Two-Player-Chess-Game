#include "ChessPiece.h"

/**
 * This operator is used to print chess pieces. They are printed as an
 * abbreviation of their color and type, and if a piece is empty, "--" is printed.
 *
 * @param out: The ostream& that will be used for printing.
 * @param chess_piece: The chess piece that is used to determine what is printed
 * @return: The ostream& that will be used for printing.
 */
ostream& operator<<(ostream& out, ChessPiece& chess_piece)
{
	Color color = chess_piece.GetColor();
	Piece piece = chess_piece.GetPiece();
	switch (color)
	{
	case Color::Black:
		out << "B";
		break;
	case Color::White:
		out << "W";
		break;
	case Color::Empty:
		out << "--";
		return out;
	}

	switch (piece)
	{
	case Piece::Bishop:
		out << "B";
		break;
	case Piece::King:
		out << "K";
		break;
	case Piece::Knight:
		out << "N";
		break;
	case Piece::Pawn:
		out << "P";
		break;
	case Piece::Queen:
		out << "Q";
		break;
	case Piece::Rook:
		out << "R";
		break;
	}
	return out;
}

/**
 * This operator is used to print the names of colors.
 *
 * @param out: The ostream& that will be used for printing.
 * @param chess_piece: The color that is used to determine what is printed
 * @return: The ostream& that will be used for printing.
 */
ostream& operator<<(ostream& out, Color& color)
{
	switch (color)
	{
	case Color::Black:
		out << "Black";
		break;
	case Color::White:
		out << "White";
		break;
	case Color::Empty:
		out << "Empty";
		break;
	}
	return out;
}

/**
 * This operator is used to print the names of piece types.
 *
 * @param out: The ostream& that will be used for printing.
 * @param chess_piece: The type of piece that is used to determine what is printed
 * @return: The ostream& that will be used for printing.
 */

ostream& operator<<(ostream& out, Piece& piece)
{
	switch (piece)
	{
	case Piece::King:
		out << "King";
		break;
	case Piece::Queen:
		out << "Queen";
		break;
	case Piece::Bishop:
		out << "Bishop";
		break;
	case Piece::Knight:
		out << "Knight";
		break;
	case Piece::Rook:
		out << "Rook";
		break;
	case Piece::Pawn:
		out << "Pawn";
		break;
	case Piece::Empty:
		out << "Empty";
		break;
	}
	return out;
}
