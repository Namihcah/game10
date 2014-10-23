#ifndef GAME10_TETROMINO_H
#define GAME10_TETROMINO_H

#include <utility>
#include "tetris.h"

namespace game10_tetris
{
	class Tetris;
	
	enum Piece
	{
		kind_I = 1,
		kind_J = 2,
		kind_L = 3,
		kind_O = 4,
		kind_S = 5,
		kind_T = 6,
		kind_Z = 7
	};

	class Tetromino
	{
		Tetris *tetris;
		int shape[4][4];
		Piece kind;
		std::pair<int, int> pos;
	public:
		Tetromino(Piece type, Tetris *t);
		Piece getType() const;
		int getX() const;
		int getY() const;
		int getShapeXY(int x, int y) const;
		void setX(int x);
		void setY(int y);
		void rotateClockwise(int length);
	};
}

#endif