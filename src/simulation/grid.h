#pragma once
#include <cstring>

constexpr int size = 128;

class Grid
{
public:
	Grid();
	~Grid();

	float get(int x, int y) const;
	float getNeighbor(int x, int y) const;
	void set(int x, int y, float value);
	const float* data();
	void clear();

public:
	int w, h;

private:
	float grid[size][size];
};
