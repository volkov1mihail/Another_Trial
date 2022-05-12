#pragma once


struct Point
{
	int x;
	int y;
	//Point(int x, int y) : x(x), y(y) {}

public:
	double dist(Point a)
	{
		return sqrt((x - a.x) * (x - a.x) + (y - a.y) * (y - a.y));
	}
};