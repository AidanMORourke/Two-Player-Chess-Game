#pragma once
#include "ChessPiece.h"
#include "ChessPlayer.h"

#include <array>
using std::array;
#include <utility>
using std::pair;
#include <vector>
using std::vector;
#include <map>
using std::map;

class ChessBoard
{
private:
	// The board that is being used to play the game
	array<array<ChessPiece, 8>, 8> board_;
	// A board used to reset the board when a new game is started
	array<array<ChessPiece, 8>, 8> start_{ {{ChessPiece(Color::Black, Piece::Rook),
	ChessPiece(Color::Black, Piece::Knight), ChessPiece(Color::Black, Piece::Bishop),
	ChessPiece(Color::Black, Piece::Queen), ChessPiece(Color::Black, Piece::King),
	ChessPiece(Color::Black, Piece::Bishop), ChessPiece(Color::Black, Piece::Knight), ChessPiece(Color::Black, Piece::Rook)},
	{ChessPiece(Color::Black, Piece::Pawn), ChessPiece(Color::Black, Piece::Pawn), ChessPiece(Color::Black, Piece::Pawn),
	ChessPiece(Color::Black, Piece::Pawn), ChessPiece(Color::Black, Piece::Pawn), ChessPiece(Color::Black, Piece::Pawn),
	ChessPiece(Color::Black, Piece::Pawn), ChessPiece(Color::Black, Piece::Pawn)},
	{ChessPiece(Color::Empty, Piece::Empty), ChessPiece(Color::Empty, Piece::Empty), ChessPiece(Color::Empty, Piece::Empty),
	ChessPiece(Color::Empty, Piece::Empty), ChessPiece(Color::Empty, Piece::Empty), ChessPiece(Color::Empty, Piece::Empty),
	ChessPiece(Color::Empty, Piece::Empty), ChessPiece(Color::Empty, Piece::Empty)},
	{ChessPiece(Color::Empty, Piece::Empty), ChessPiece(Color::Empty, Piece::Empty), ChessPiece(Color::Empty, Piece::Empty),
	ChessPiece(Color::Empty, Piece::Empty), ChessPiece(Color::Empty, Piece::Empty), ChessPiece(Color::Empty, Piece::Empty),
	ChessPiece(Color::Empty, Piece::Empty), ChessPiece(Color::Empty, Piece::Empty)},
	{ChessPiece(Color::Empty, Piece::Empty), ChessPiece(Color::Empty, Piece::Empty), ChessPiece(Color::Empty, Piece::Empty),
	ChessPiece(Color::Empty, Piece::Empty), ChessPiece(Color::Empty, Piece::Empty), ChessPiece(Color::Empty, Piece::Empty),
	ChessPiece(Color::Empty, Piece::Empty), ChessPiece(Color::Empty, Piece::Empty)},
	{ChessPiece(Color::Empty, Piece::Empty), ChessPiece(Color::Empty, Piece::Empty), ChessPiece(Color::Empty, Piece::Empty),
	ChessPiece(Color::Empty, Piece::Empty), ChessPiece(Color::Empty, Piece::Empty), ChessPiece(Color::Empty, Piece::Empty),
	ChessPiece(Color::Empty, Piece::Empty), ChessPiece(Color::Empty, Piece::Empty)},
	{ChessPiece(Color::White, Piece::Pawn), ChessPiece(Color::White, Piece::Pawn), ChessPiece(Color::White, Piece::Pawn),
	ChessPiece(Color::White, Piece::Pawn), ChessPiece(Color::White, Piece::Pawn), ChessPiece(Color::White, Piece::Pawn),
	ChessPiece(Color::White, Piece::Pawn), ChessPiece(Color::White, Piece::Pawn)},
	{ChessPiece(Color::White, Piece::Rook),ChessPiece(Color::White, Piece::Knight), ChessPiece(Color::White, Piece::Bishop),
	ChessPiece(Color::White, Piece::Queen), ChessPiece(Color::White, Piece::King), ChessPiece(Color::White, Piece::Bishop),
	ChessPiece(Color::White, Piece::Knight), ChessPiece(Color::White, Piece::Rook)}} };

public:
	ChessBoard() = default;
	
	map<Color, ChessPlayer> players_ = { std::make_pair(Color::White, ChessPlayer(Color::White)), std::make_pair(Color::Black, ChessPlayer(Color::Black)) };
	array<array<ChessPiece, 8>, 8> GetBoard() { return board_; };


	void SetBoard(array<array<ChessPiece, 8>, 8> board) { board_ = board; }
	void Reset() { board_ = start_; };

	void PrintBoard();
};

bool ValidKnightMove(pair<int, int> start, pair<int, int> end);

bool ValidBishopMove(pair<int, int> start, pair<int, int> end);

bool ValidRookMove(pair<int, int> start, pair<int, int> end);

bool ValidQueenMove(pair<int, int> start, pair<int, int> end);

bool ValidKingMove(pair<int, int> start, pair<int, int> end);

bool ValidPawnForwardOne(pair<int, int> start, pair<int, int> end, ChessPiece& chess_piece);

bool ValidPawnForwardAll(pair<int, int> start, pair<int, int> end, ChessPiece& chess_piece);

bool ValidPawnMove(pair<int, int> start, pair<int, int> end, ChessPiece& chess_piece, ChessBoard& chess_board);

void UpdatePosition(pair<int, int> end, pair<int, int>& current_position);

bool IsTargetPiece(ChessPiece& current_piece, Color desired_color, Piece desired_piece);

bool CheckCollision(ChessBoard chess_board, pair<int, int> start, pair<int, int> end);

bool CheckValidMove(ChessPiece chess_piece, ChessBoard chess_board, pair<int, int> start, pair<int, int> end);

Color GetOppositeColor(Color& color);

bool UpdateInCheck(ChessPlayer& enemy, ChessBoard& chess_board);

bool KingHasValidMoves(ChessPlayer& enemy, ChessBoard& chess_board);

bool MovePiece(ChessBoard& chess_board, pair<int, int> start, pair<int, int> end);