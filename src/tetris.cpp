#include <chrono>

#include "dbg.h"
#include "tetris.h"

using namespace std;

namespace game10_tetris
{
	Tetris::Tetris()
	{
		score = 0;
		party = false;

		for (int i = 0; i < T_ROWS; ++i)
		{
			for (int j = 0; j < T_COLS; ++j)
			{
				grid[i][j] = 0;
			}
		}

		auto seed = chrono::high_resolution_clock::now().time_since_epoch().count();
		mt.seed(seed);

		while (blocks.size() < T_COUNT)
		{
			Tetromino *t = new Tetromino(nextPiece(), this);

			blocks.push_back(t);
		}
	}

	Tetris::~Tetris()
	{
		while (blocks.size() > 0)
		{
			Tetromino *t = blocks.front();
			delete t;
			blocks.pop_front();
		}
	}

	int Tetris::getScore() const
	{
		return score;
	}

	void Tetris::setParty(bool p)
	{
		party = p;
	}

	bool Tetris::getParty() const
	{
		return party;
	}

	Tetromino* Tetris::getCurrent()
	{
		if (blocks.size() == 0)
		{
			Tetromino *t = new Tetromino(nextPiece(), this);
			blocks.push_back(t);
		}

		return blocks.front();
	}

	int Tetris::getGridXY(int x, int y) const
	{
		return grid[x][y];
	}

	void Tetris::turn()
	{
		switch (getCurrent()->getType())
		{
		case kind_O:
			break;
		case kind_I:
			getCurrent()->rotateClockwise(4);
			break;
		default:
			getCurrent()->rotateClockwise(3);
			break;
		}
	}

	void Tetris::move_r()
	{
		getCurrent()->setX(getCurrent()->getX() + 1);
		if (detectCollision(getCurrent())) getCurrent()->setX(getCurrent()->getX() - 1);
	}
	void Tetris::move_l()
	{
		getCurrent()->setX(getCurrent()->getX() - 1);
		if (detectCollision(getCurrent())) getCurrent()->setX(getCurrent()->getX() + 1);
	}

	TickResult Tetris::tick()
	{
		getCurrent()->setY(getCurrent()->getY() + 1);

		if (detectCollision(getCurrent()))
		{
			getCurrent()->setY(getCurrent()->getY() + -1);
			for (int i = 0, j, col, row = getCurrent()->getY(); i < 4; i++, row++)
			{
				j = 0;
				for (col = getCurrent()->getX(); j < 4; j++, col++)
				{
					if (getCurrent()->getShapeXY(i,j) > 0)
					{
						grid[row][col] = getCurrent()->getType();
					}
				}
			}

			Tetromino *t = getCurrent();
			delete t;
			blocks.pop_front();

			getCurrent()->setY(0);
			if (detectCollision(getCurrent()))
			{
				return game_over;
			}
			else
			{
				int clear = clearRows(0);
				switch (clear)
				{
				case 0:
					break;
				case 1:
					if (party) score += 1000;
					score += 500;
					party = true;
					break;
				default:
					if (party) score += 500 * clear;
					party = true;
					score += clear * 1000;
					break;
				}
				return new_current;
			}
		}
		else
		{
			return move_down;
		}
	}

	TickResult Tetris::drop()
	{
		TickResult r = move_down;
		do
		{
			r = tick();
		} while (r == move_down);

		return r;
	}

	int Tetris::clearRows(int clear)
	{
		for (int i = T_ROWS - 1, j, hits; i >= 0; --i)
		{
			for (j = 0, hits = 0; j < T_COLS; ++j)
			{
				if (grid[i][j] > 0) hits++;
			}
			if (hits == T_COLS)
			{
				for (int ni = i - 1, nj; ni >= 0; --ni)
				{
					for (nj = 0; nj < T_COLS; ++nj)
					{
						grid[ni + 1][nj] = grid[ni][nj];
					}
				}
				clear++;
				return clearRows(clear);
			}
		}
		return clear;
	}

	Piece Tetris::nextPiece()
	{
		uniform_int_distribution<int> intDist(1, 7);
		
		return (Piece) intDist(mt);
	}

	bool Tetris::detectCollision(Tetromino *block)
	{
		for (int i = 0, j, col, row = block->getY(); i < 4; i++, row++)
		{
			j = 0;
			for (col = block->getX(); j < 4; j++, col++)
			{
				if (block->getShapeXY(i, j) > 0)
				{
					if (row >= T_ROWS || row < 0)
					{
						return true;
					}
					else if (col >= T_COLS || col < 0)
					{
						return true;
					}
					else if (grid[row][col] > 0)
					{
						return true;
					}
				}
			}
		}
		return false;
	};
}
	

	

	
	

		
