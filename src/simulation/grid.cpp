#include "grid.h"
#include <algorithm>

Grid::Grid()
{
	w = size;
	h = size;
	std::memset(grid, 0, sizeof(int) * size * size);
}

Grid::~Grid()
{

}

float Grid::get(int x, int y) const
{
	return grid[y][x];
}

float Grid::getNeighbor(int x, int y) const
{
	x = std::clamp(x, 0, size - 1);
	y = std::clamp(y, 0, size - 1);
	return grid[y][x];
}

void Grid::set(int x, int y, float value)
{
	grid[y][x] = value;
}

const float* Grid::data()
{
	return &grid[0][0];
}

void Grid::clear()
{
	std::memset(grid, 0, sizeof(grid));
}
