#include "grid.h"

Grid::Grid()
{
	std::memset(grid, 0, sizeof(grid));
}

Grid::~Grid()
{

}

float Grid::get(int x, int y) const
{
	return grid[y][x];
}

void Grid::set(int x, int y, float value)
{
	grid[y][x] = value;
}