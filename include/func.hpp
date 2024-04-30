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

int Comp(std::vector<int>& arr, int x);
std::vector<std::vector<int>> BuildMap(std::vector<Rectangle>& rectangles);

int Map(std::vector<std::vector<int>>& map, Point point);
void MapTime(std::vector<std::vector<int>>& map, std::vector<Point>& points);

int BruteForce(std::vector<Rectangle>& recs, Point point);
void BruteForceTime(std::vector<Rectangle>& recs, std::vector<Point>& point);

#endif