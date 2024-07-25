#include "GameData.h"

namespace GameData
{
	const std::vector<Vector2> shipPoints
	{
		{4, 0},
		{3, -1 },
		{ 2,-1 },
		{ 1,-2 },
		{ 0,-2 },
		{ -2, -4 },

		{ -2,4 },
		{ 0,2 },
		{ 1,2 },
		{ 2,1 },
		{ 3,1 },
		{ 4, 0 }

	};
	const std::vector<Vector2> enemyPoints
	{
		{2, 0},
		{0, -1},
		{-2, -1},
		{0, -1},
		{-1, 0},
		{0, 1},
		{-2, 1},
		{0, 1},
		{2, 0}
	};
	const std::vector<Vector2> bulletPoints
	{
		{ 5, 0 },
		{ -5, -5 },
		{ -5, 5 },
		{ 5, 0 }
	};
	const std::vector<Vector2> healthPickup
	{
		{0, -1},
		{1, -1},
		{-1, -1},
		{0, -1},
		{0, 1},
		{1, 1},
		{-1, 1},
	};
	const std::vector<Vector2> spreadPickup
	{
		{0,0},
		{-1, -1},
		{0,0},
		{-1, 0},
		{0,0},
		{-1, 1},
	};
}