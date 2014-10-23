#ifndef game10_tetris_h
#define game10_tetris_h

#include <deque>
#include <random>
#include "tetromino.h"

#ifdef _MSC_VER
#define snprintf _snprintf
#endif

#define T_COUNT 5
#define T_ROWS 22
#define T_COLS 10
#define PIECE_COUNT 7

namespace game10_tetris
{
	enum Piece;
	class Tetromino;

	enum TickResult
	{
		move_down = 0,
		new_current = 1,
		game_over = 2
	};

	class Tetris
	{
		int score;
		bool party;
		int grid[T_ROWS][T_COLS];
		std::deque<Tetromino*> blocks;
		std::mt19937 mt;

		int clearRows(int clear);
		Piece nextPiece();

	public:
		Tetris();
		~Tetris();

		int getScore() const;
		void setParty(bool p);
		bool getParty() const;
		Tetromino* getCurrent();
		int getGridXY(int x, int y) const;

		void turn();
		void move_r();
		void move_l();
		TickResult tick();
		TickResult drop();
		bool detectCollision(Tetromino *block);
	};	
}

#endif
