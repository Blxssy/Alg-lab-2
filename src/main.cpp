#include <iostream>
#include <vector>
#include <cmath>
#include <random>

#include "../include/point.hpp"
#include "../include/rec.hpp"
#include "../include/func.hpp"

using namespace std;

std::vector<Point> GeneratePoints(int number, int range) {
    const int X_PRIME = 65537;
    const int Y_PRIME = 7919;
    std::vector<Point> points;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, range);

    for (int i = 0; i < number; i++) {
        int x = (X_PRIME * i) % range;
        int y = (Y_PRIME * i) % range;
        points.push_back(Point(x, y));
    }
    return points;
}


vector<Rectangle> GenerateRecs(int count){
    vector<Rectangle> rectangles;
    
    for (int i = 0; i < count; i++) {
        rectangles.push_back(Rectangle(Point(10 * i, 10 * i), Point(10 * (2 * count - i), 10 * (2 * count - i))));
    }
    return rectangles;
}


int main(){
    vector<Rectangle> recs = GenerateRecs(1000);
    vector<Point> points = GeneratePoints(100, recs.size() * 2 - 1);
    vector<vector<int>> map = BuildMap(recs);

    BruteForceTime(recs, points);
    MapTime(map, points);

    return 0;
}
