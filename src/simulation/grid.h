#pragma once
#include <cstring>

class Grid
{
public:
	Grid();
	~Grid();

	float get(int x, int y) const;
	void set(int x, int y, float value);

private:
	float grid[128][128];
};
