#pragma once

#ifndef FUNC
#define FUNC

#include <iostream>
#include <vector>
#include <chrono>

#include "point.hpp"
#include "rec.hpp"

using namespace std;

inline std::vector<int> compX;
inline std::vector<int> compY;

int Comp(vector<int>& arr, int x);
std::vector<std::vector<int>> BuildMap(std::vector<Rectangle>& rectangles);

int Map(vector<vector<int>>& map, Point point);
void MapTime(vector<vector<int>>& map, vector<Point>& points);

int BruteForce(vector<Rectangle>& recs, Point point);
void BruteForceTime(vector<Rectangle>& recs, vector<Point>& point);

#endif