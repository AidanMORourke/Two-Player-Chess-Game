#include "ChessBoard.h"
#include "ChessPlayer.h"

/**
 * Prints the chess board
 * 
 * @return None
 */
void ChessBoard::PrintBoard()
{
	cout << "   0  1  2  3  4  5  6  7" << endl;
	for (int i = 0; i < 8; i++)
	{
		cout << " +--+--+--+--+--+--+--+--+ " << endl;
		cout << i << '|';
		for (int j = 0; j < 8; j++)
		{
			ChessPiece& current_piece = GetBoard().at(i).at(j);
			cout << current_piece << '|';
		}
		cout << endl;
	}
	cout << " +--+--+--+--+--+--+--+--+ " << endl;
}

/**
 * Checks to see if a move between two sets of coordinates
 * can be made for a knight piece.
 *
 * @param start: The row and column of the piece to be moved
 * @param end: The row and column that the piece is to be moved to.
 * @returns: True if the move is valid, false otherwise.
 * 
 */
bool ValidKnightMove(pair<int, int> start, pair<int, int> end)
{
	// Knight moves in 1 of 8 different possible L shapes.
	return  (start.first == end.first + 1 && start.second == end.second + 2) ||
		(start.first == end.first - 1 && start.second == end.second + 2) ||
		(start.first == end.first + 1 && start.second == end.second - 2) ||
		(start.first == end.first - 1 && start.second == end.second - 2) ||
		(start.first == end.first + 2 && start.second == end.second + 1) ||
		(start.first == end.first - 2 && start.second == end.second + 1) ||
		(start.first == end.first + 2 && start.second == end.second - 1) ||
		(start.first == end.first - 2 && start.second == end.second - 1);
}

/**
 * Checks to see if a move between two sets of coordinates
 * can be made for a Bishop piece.
 *
 * @param start: The row and column of the piece to be moved
 * @param end: The row and column that the piece is to be moved to.
 * @return: True if the move is valid, false otherwise.
 *
 */
bool ValidBishopMove(pair<int, int> start, pair<int, int> end)
{
	// Bishop moves diagonally
	return (end.first - start.first == end.second - start.second) || 
		(start.first - end.first == end.second - start.second) || 
		(end.first - start.first == start.second - end.second) || 
		(start.first - end.first == start.second - end.second);
}

/**
 * Checks to see if a move between two sets of coordinates
 * can be made for a Rook piece.
 *
 * @param start: The row and column of the piece to be moved
 * @param end: The row and column that the piece is to be moved to.
 * @return: True if the move is valid, false otherwise.
 *
 */
bool ValidRookMove(pair<int, int> start, pair<int, int> end)
{
	// Rook only moves in straight lines in the X and Y direction
	return (end.first - start.first != 0 && end.second - start.second == 0) ||
		(end.first - start.first == 0 && end.second - start.second != 0);
}


/**
 * Checks to see if a move between two sets of coordinates
 * can be made for a queen piece.
 *
 * @param start: The row and column of the piece to be moved
 * @param end: The row and column that the piece is to be moved to.
 * @return: True if the move is valid, false otherwise.
 *
 */
bool ValidQueenMove(pair<int, int> start, pair<int, int> end)
{
	// Queen can move like a Rook or like a Bishop.
	return ValidBishopMove(start, end) || ValidRookMove(start, end);
}

/**
 * Returns true if the piece moves 1 space in any of the possible 8 directions.
 * This function also makes sure that true is not returned if the
 * piece does not move at all. This is used in combination with ValidQueenMove
 * to check if a move for a king is valid.
 * 
 * @param start: The row and column of the piece to be moved
 * @param end: The row and column that the piece is to be moved to.
 * @return: True if the move is valid, false otherwise.
 * 
 */
bool MovesOneSpace(pair<int, int> start, pair<int, int> end)
{
	
	return !(end.first - start.first == 0 && end.second - start.second == 0) &&
		((end.first - start.first == 1 || end.first - start.first == 0 || end.first - start.first == -1) &&
		(end.second - start.second == 1 || end.second - start.second == 0 || end.second - start.second == -1));
}

/**
 * Checks to see if a move between two sets of coordinates
 * can be made for a king piece.
 *
 * @param start: The row and column of the piece to be moved
 * @param end: The row and column that the piece is to be moved to.
 * @return: True if the move is valid, false otherwise.
 *
 */
bool ValidKingMove(pair<int, int> start, pair<int, int> end)
{
	// King can do whatever queen can as long as it only moves one space in the X and/or Y direction
	return ValidQueenMove(start, end) && MovesOneSpace(start, end);
}

/**
 * This function returns true for the specific case of a pawn moving only one space forward. It is called
 * by other functions to act as one of several possible cases where a pawn move is valid.
 *
 * @param start: The row and column of the piece to be moved
 * @param end: The row and column that the piece is to be moved to.
 * @param chess_piece: The piece that is being moved. This is passed in so that the
 * function can define what is "forward" based on the pawn's color.
 * @param chess_board: The chess board. This is to check for collisions with other pieces when trying to move forward.
 * @return: True if the move is valid, false otherwise.
 */
bool ValidPawnForwardOne(pair<int, int> start, pair<int, int> end, ChessPiece& chess_piece, ChessBoard& chess_board)
{
	auto board = chess_board.GetBoard();
	if (board.at(end.first).at(end.second).GetColor() != Color::Empty)
	{
		return false;
	}
	if (chess_piece.GetColor() == Color::White)
	{
		return end.first == start.first - 1 && end.second == start.second;
	}
	else
	{
		return end.first == start.first + 1 && end.second == start.second;
	}
}

/**
 * This function returns true if either a pawn moves one space forward, or
 * if a pawn has not moved yet and moves 2 spaces forward.
 *
 * @param start: The row and column of the piece to be moved
 * @param end: The row and column that the piece is to be moved to.
 * @param chess_piece: The piece that is being moved. This is passed in so that the
 * function can define what is "forward" based on the pawn's color, as well as to
 * check whether or not the piece has moved yet.
 * @param chess_board: The chess board. This is to check for collisions with other pieces when trying to move forward.
 * @return: True if the move is valid, false otherwise.
 */
bool ValidPawnForwardAll(pair<int, int> start, pair<int, int> end, ChessPiece& chess_piece, ChessBoard& chess_board)
{
	/**
	 * Pawns can move 1 or 2 spaces forward if they have not moved yet,
	 * and only 1 if they already have.
	 */

	auto board = chess_board.GetBoard();

	if (chess_piece.GetHasMoved() == false)
	{
		if (board.at(end.first).at(end.second).GetColor() != Color::Empty)
		{
			return false;
		}
		if (chess_piece.GetColor() == Color::White)
		{
			return (end.first == start.first - 2 && end.second == start.second) || ValidPawnForwardOne(start, end, chess_piece, chess_board);
		}
		else
		{
			return (end.first == start.first + 2 && end.second == start.second) || ValidPawnForwardOne(start, end, chess_piece, chess_board);
		}
	}
	else
	{
		return ValidPawnForwardOne(start, end, chess_piece, chess_board);
	}
}
/**
 * This function handles every possible case where moving a pawn is valid.
 * If a pawn can take a piece diagonally, it has the option to do so. It also calls
 * the ValidPawnForwardAll function to handle other cases.
 * @param start: The row and column of the piece to be moved
 * @param end: The row and column that the piece is to be moved to.
 * @param chess_piece: The piece that is being moved. This is passed in so that the
 * function can define what is "forward" based on the pawn's color, as well as to
 * check whether or not the piece has moved yet.
 * @param chess_board: The chess board is passed in as a parameter. This is because
 * pawns can move forward diagonally only if the spot they wish to move to is occupied by an enemy piece
 * @return: True if the move is valid, false otherwise.
 */
bool ValidPawnMove(pair<int, int> start, pair<int, int> end, ChessPiece& chess_piece, ChessBoard& chess_board)
{
	if (chess_board.GetBoard().at(end.first).at(end.second).GetPiece() != Piece::Empty)
	{
		if (chess_piece.GetColor() == Color::White)
		{
			return (end.first == start.first - 1) && (end.second == start.second + 1 || end.second == start.second - 1)
				|| ValidPawnForwardAll(start, end, chess_piece, chess_board);
		}
		else
		{
			return (end.first == start.first + 1) && (end.second == start.second + 1 || end.second == start.second - 1)
				|| ValidPawnForwardAll(start, end, chess_piece, chess_board);
		}
	}
	return ValidPawnForwardAll(start, end, chess_piece, chess_board);
}

/**
 * Handles the iteration of the "movement" of pieces from start to end. Even though the piece is moved
 * instantly, the path is checked one space at a time to make sure that there are no collisions.
 * Each movement is handled based on a comparison between the start and end coordinates. Each time this function
 * is called, that piece is moved one space closer to the end in the x and/or y direction.
 *
 * @param end: The row and column that the piece is to be moved to.
 * @param current_position: The current position of the piece as it is moving along its path.
 * @return: None
 */
void UpdatePosition(pair<int, int> end, pair<int, int>& current_position)
{
	if (current_position.first == end.first && current_position.second > end.second)
	{
		//Left
		current_position.second--;
	}
	else if (current_position.first == end.first && current_position.second < end.second)
	{
		//Right
		current_position.second++;
	}
	else if (current_position.first > end.first && current_position.second == end.second)
	{
		//Up
		current_position.first--;
	}
	else if (current_position.first < end.first && current_position.second == end.second)
	{
		//Down
		current_position.first++;
	}
	else if (current_position.first > end.first && current_position.second > end.second)
	{
		//Up and Left
		current_position.first--;
		current_position.second--;
	}
	else if (current_position.first < end.first && current_position.second > end.second)
	{
		//Down and Left
		current_position.first++;
		current_position.second--;
	}
	else if (current_position.first > end.first&& current_position.second < end.second)
	{
		//Up and Right
		current_position.first--;
		current_position.second++;
	}
	else if (current_position.first < end.first && current_position.second < end.second)
	{
		//Down and Right
		current_position.first++;
		current_position.second++;
	}

}

/**
 * Checks to see if a piece has a certain color and type.
 * 
 * @return: A boolean representing whether or not the piece passed in has the desired color and type.
 */
bool IsTargetPiece(ChessPiece& current_piece, Color desired_color, Piece desired_piece)
{
	return current_piece.GetColor() == desired_color && current_piece.GetPiece() == desired_piece;
}

/**
 * Checks to see if there is a collision along the path a piece wants to take from start to end.
 *
 * @param chess_board: The chess board. This is used to identify the piece that the player wishes to take.
 * @param start: The row and column of the piece to be moved
 * @param end: The row and column that the piece is to be moved to.
 *
 * @return: True if there is a collision, false otherwise.
 */
bool CheckCollision(ChessBoard chess_board, pair<int, int> start, pair<int, int> end)
{
	auto current_position = start;
	ChessPiece& end_piece = chess_board.GetBoard().at(end.first).at(end.second);
	//Move one-by-one through the path until the destination is reached.
	while (current_position.first != end.first || current_position.second != end.second)
	{
		UpdatePosition(end, current_position);
		auto& current_piece = chess_board.GetBoard().at(current_position.first).at(current_position.second);
		/**
		 * Check to see if the current position holds a piece that is NOT the piece being held at the end coordinate.
		 * This is to prevent the program from detecting collisions with the piece that one wishes to take.
		 */
		if (current_piece.GetPiece() != Piece::Empty && current_piece.GetColor() != Color::Empty
			&& !IsTargetPiece(current_piece, end_piece.GetColor(), end_piece.GetPiece()))
		{
			return true;
		}
	}
	return false;
}

/**
 * Checks if a move is valid before it is performed.
 *
 * @param chess_piece: The piece being moved
 * @param chess_board: The board
 * @param start: The coordinates of the piece on the board before it is moved
 * @param end: The coordinates of the piece on the board after it is moved
 *
 * @return: True if the move is valid, false otherwise.
 */
bool CheckValidMove(ChessPiece chess_piece, ChessBoard chess_board, pair<int, int> start, pair<int, int> end)
{
	auto board = chess_board.GetBoard();
	auto players = chess_board.players_;
	Color piece_color = board.at(start.first).at(start.second).GetColor();
	Color end_color = board.at(start.first).at(start.second).GetColor();
	
	// You can't move a piece to a square with another piece of the same color.
	if (board.at(start.first).at(start.second).GetColor() == board.at(end.first).at(end.second).GetColor())
	{
		return false;
	}

	// A move is not valid if a piece is moved to a coordinate outside of the chess board.
	if (end.first < 0 || end.first > 7 || end.second < 0 || end.second > 7)
	{
		return false;
	}

	Piece piece = chess_piece.GetPiece();

	/**
	 * Check the validity of a move based on what type of piece is being moved.
	 * Collisions are checked for every type of piece except Knight.
	 */

	if (piece != Piece::Knight && CheckCollision(chess_board, start, end))
	{
		return false;
	}
	
	switch (piece)
	{
	case(Piece::Knight):
		return ValidKnightMove(start, end);
		break;
	case(Piece::Bishop):
		return ValidBishopMove(start, end);
		break;
	case(Piece::Rook):
		return ValidRookMove(start, end);
		break;
	case(Piece::Queen):
		return ValidQueenMove(start, end);
		break;
	case(Piece::King):
		return ValidKingMove(start, end);
		break;
	case(Piece::Pawn):
		return ValidPawnMove(start, end, chess_piece, chess_board);
		break;
	}

}

/**
 * Finds the opposite color of the color passed in. Has a special case for Empty.
 *
 * @param
 * @return: The opposite color of the one passed in.
 */
Color GetOppositeColor(Color& color)
{
	switch (color)
	{
	case Color::Black:
		return Color::White;
	case Color::White:
		return Color::Black;
	case Color::Empty:
		return Color::Empty;
	}
}

/**
 * Decides whether or not the enemy king is in check, then update's the enemy's "is_in_check_" boolean if so.
 * @param enemy: The player whose king is checked for whether or not it is in check
 * @param chess_board: The chess_board
 * @return: True if the enemy is in check, false otherwise.
 */

bool UpdateInCheck(ChessPlayer& enemy, ChessBoard& chess_board)
{
	auto board = chess_board.GetBoard();
	Color enemy_color = enemy.GetColor();
	Color player_color = GetOppositeColor(enemy_color);


	// Check every piece on the board.
	for (int r = 0; r < 8; r++)
	{
		for (int c = 0; c < 8; c++)
		{
			ChessPiece& chess_piece = board.at(r).at(c);
			/**
			 * If the piece at the current space has the same color as the player, and
			 * that piece has a valid path to the king, the enemy is in check.
			 */
			if (chess_piece.GetColor() == player_color && CheckValidMove(chess_piece,
				chess_board, std::make_pair(r, c), enemy.GetKingPosition()))
			{
				cout << "Check!" << endl;
				chess_board.players_[player_color].SetKingAttackPiece(std::make_pair(r, c));
				return true;
			}
		}
	}
	return false;
}

/**
 * Checks to see if the enemy king has valid moves.
 *
 * @param enemy: The enemy player
 * @param chess_board: The chess board
 * @return: True if the 
 */
bool KingHasValidMoves(ChessPlayer& enemy, ChessBoard& chess_board)
{
	auto board = chess_board.GetBoard();
	auto king_position = enemy.GetKingPosition();
	ChessPiece& enemy_king = board.at(king_position.first).at(king_position.second);
	Color king_color = enemy_king.GetColor();
	auto king_attack_piece = chess_board.players_[GetOppositeColor(king_color)].GetKingAttackPiece();

	// Every possible space a king can move to
	std::vector<pair<int, int>> moves{ std::make_pair(king_position.first, king_position.second + 1),
	std::make_pair(king_position.first, king_position.second - 1),
	std::make_pair(king_position.first + 1, king_position.second),
	std::make_pair(king_position.first - 1, king_position.second),
	std::make_pair(king_position.first + 1, king_position.second + 1),
	std::make_pair(king_position.first + 1, king_position.second - 1),
	std::make_pair(king_position.first - 1, king_position.second + 1),
	std::make_pair(king_position.first - 1, king_position.second - 1) };

	/**
	 * Check every possible move the king can make, and skip checking validity of moves that don't exist.
	 * A move is valid in check if it meets 2 requirements:
	 * 1. The move itself is valid
	 * 2. The king is not still in check even after making the move.
	 */
	for (pair<int,int> end : moves)
	{
		if (end.first < 0 || end.first > 7 || end.second < 0 || end.second > 7)
		{
			continue;
		}
		if (CheckValidMove(enemy_king, chess_board, king_position, end) && CheckValidMove(enemy_king, chess_board, king_attack_piece, end))
		{
			return true;
		}
	}
	return false;
}


/**
 * Moves a piece from start to end
 *
 * @param chess_board: The board
 * @param start: The location of the piece before it is moved
 * @param end: The location of the piece after it is moved
 * @return: True if checkmate is hit, false otherwise
 */
bool MovePiece(ChessBoard& chess_board, pair<int, int> start, pair<int, int> end)
{
	auto board = chess_board.GetBoard();
	ChessPiece start_piece = board.at(start.first).at(start.second);
	ChessPiece end_piece = board.at(end.first).at(end.second);
	Color player_color = start_piece.GetColor();
	Color enemy_color = GetOppositeColor(player_color);
	ChessPlayer player = chess_board.players_[player_color];
	ChessPlayer enemy = chess_board.players_[enemy_color];

	/**
	 * If the piece you are moving has not moved yet, update it.
	 * This is to ensure That pawns can only move two tiles the first time they are moved.
	 */
	board.at(end.first).at(end.second).SetHasMoved(true);
	
	if (end_piece.GetPiece() == Piece::King)
	{
		return true;
	}
	/**
	 * Set the end destination's piece to the start destination's piece, then set the start destination to empty.
	 * Checking the validity of a move is done inside main.
	 */
	board.at(end.first).at(end.second).SetPiece(start_piece.GetPiece());
	board.at(end.first).at(end.second).SetColor(start_piece.GetColor());
	board.at(start.first).at(start.second).SetPiece(Piece::Empty);
	board.at(start.first).at(start.second).SetColor(Color::Empty);
	// Update the king's position if needed.
	if (start_piece.GetPiece() == Piece::King)
	{
		player.SetKingPosition(end);
	}
	chess_board.SetBoard(board);
	// See if the other player's king is in check, and update the player's check variable accordingly.
	enemy.SetCheck(UpdateInCheck(enemy, chess_board));
	// If the enemy king is in check, see if the king has any valid moves. If it doesn't update checkmate.
	if (enemy.GetIsInCheck() && !KingHasValidMoves(enemy, chess_board))
	{
		return true;
	}
	return false;
}