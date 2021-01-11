#include "ChessPiece.h"
#include "ChessBoard.h"
#include "ChessPlayer.h"

/**
 * Prompts the user for coordinates of the piece they'd like to move and
 * where they'd like to move it to.
 *
 * @return: A pair of pairs of integers representing these two coordinate pairs.
 */
pair<pair<int, int>, pair<int, int>> GetStartAndEnd()
{
	int start_x, start_y;
	cout << "Give the row of the piece you want to move." << endl;
	cin >> start_x;
	cout << "Give the column of the piece you want to move." << endl;
	cin >> start_y;
	pair<int, int> start = std::make_pair(start_x, start_y);
	int end_x, end_y;
	cout << "Give the row you want to move it to." << endl;
	cin >> end_x;
	cout << "Give the column you want to move it to." << endl;
	cin >> end_y;
	pair<int, int> end = std::make_pair(end_x, end_y);
	return std::make_pair(start, end);
}

int main()
{
	vector<Color> colors = { Color::White, Color::Black };
	ChessBoard my_board;
	// Set the board to be as it would at the beginning of a chess game and then print it.
	my_board.Reset();
	my_board.PrintBoard();
	auto players = my_board.players_;
	Color losing_color = Color::Empty;
	bool game_active = true;

	// While both players still have their kings
	while (game_active)
	{
		// Alternate between the two colors of pieces
		for (Color color : colors)
		{
			// Print the color of the player whose turn it is.
			cout << color << "'s turn" << endl;
			
			// Prompt that player to move a piece.
			auto coord_pairs = GetStartAndEnd();

			// Is the player moving one of their own pieces?
			while (players[color].GetColor() != my_board.GetBoard().at(coord_pairs.first.first).at(coord_pairs.first.second).GetColor())
			{
				cout << "Please move one of your own pieces" << endl;
				coord_pairs = GetStartAndEnd();
			}

			// Is the move valid in the first place?
			while (!CheckValidMove(my_board.GetBoard().at(coord_pairs.first.first).at(coord_pairs.first.second), my_board, coord_pairs.first, coord_pairs.second ))
			{
				cout << "Please move your piece to a valid spot" << endl;
				coord_pairs = GetStartAndEnd();
			}

			// Is the player trying to move something other than their king while they're in check?
			if (players[color].GetIsInCheck())
			{
				while (my_board.GetBoard().at(coord_pairs.first.first).at(coord_pairs.first.second).GetPiece() != Piece::King)
				{
					cout << "You're in check, you must move your king!" << endl;
					coord_pairs = GetStartAndEnd();
				}
			}
			// Move the piece and then print the board. If the King was taken, declare the loser.
			bool checkmate = MovePiece(my_board, coord_pairs.first, coord_pairs.second);
			my_board.PrintBoard();
			if (checkmate)
			{
				losing_color = GetOppositeColor(color);
				game_active = false;
				break;
			}
		}
	}
	// Finally, the loser is declared.
	switch(losing_color)
	{
	case Color::White:
		cout << "Checkmate! The white king has fallen!" << endl;
		break;
	case Color::Black:
		cout << "Checkmate! The black king has fallen!" << endl;
		break;
	}
}