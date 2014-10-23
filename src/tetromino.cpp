#include "tetromino.h"

namespace game10_tetris
{
	Tetromino::Tetromino(Piece type, Tetris *t)
	{
		kind = type;
		tetris = t;

		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				shape[i][j] = 0;
			}
		}

		switch (kind){
		case kind_J:
			shape[1][0] = type;
			shape[1][1] = type;
			shape[1][2] = type;
			shape[2][2] = type;
			break;
		case kind_L:
			shape[1][0] = type;
			shape[1][1] = type;
			shape[1][2] = type;
			shape[2][0] = type;
			break;
		case kind_O:
			shape[0][0] = type;
			shape[0][1] = type;
			shape[1][0] = type;
			shape[1][1] = type;
			break;
		case kind_S:
			shape[1][1] = type;
			shape[1][2] = type;
			shape[2][0] = type;
			shape[2][1] = type;
			break;
		case kind_T:
			shape[1][0] = type;
			shape[1][1] = type;
			shape[1][2] = type;
			shape[2][1] = type;
			break;
		case kind_Z:
			shape[1][1] = type;
			shape[2][2] = type;
			shape[2][1] = type;
			shape[1][0] = type;
			break;
		default:
			shape[2][0] = type;
			shape[2][1] = type;
			shape[2][2] = type;
			shape[2][3] = type;
			break;
		}
		
		pos.first = 0;
		pos.second = 3;
	}

	Piece Tetromino::getType() const
	{
		return kind;
	}

	int Tetromino::getX() const
	{
		return pos.second;
	}

	int Tetromino::getY() const
	{
		return pos.first;
	}

	void Tetromino::setX(int x)
	{
		pos.second = x;
	}

	void Tetromino::setY(int y)
	{
		pos.first = y;
	}

	int Tetromino::getShapeXY(int x, int y) const
	{
		return shape[x][y];
	}

	void Tetromino::rotateClockwise(int length)
	{
		int old_shape[4][4];

		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				old_shape[i][j] = shape[i][j];
			}
		}

		for (int i = 0; i < length; ++i)
		{
			for (int j = 0; j < length; ++j)
			{
				shape[i][j] = old_shape[length - j - 1][i];
			}
		}

		if (tetris->detectCollision(this))
		{
			for (int i = 0; i < 4; ++i)
			{
				for (int j = 0; j < 4; ++j)
				{
					shape[i][j] = old_shape[i][j];
				}
			}
		}
	}
}