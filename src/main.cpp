#include <iostream>
#include <vector>
#include <cmath>
#include <chrono>
#include <random>

#include "../include/point.hpp"
#include "../include/rec.hpp"

using namespace std;


int bruteForce(vector<Rectangle>& recs, vector<Point>& points){
    auto begin = std::chrono::steady_clock::now();

    int counter = 0;
    for (auto& point : points){
        for (Rectangle& rectangle : recs) {
        // cout << point.getX() << " " << point.getY() << "\n";

        // cout << rectangle.getLeftPoint().getX() << " ";
        // cout << rectangle.getLeftPoint().getY() << " ";
        // cout << rectangle.getRightPoint().getX() << " ";
        // cout << rectangle.getRightPoint().getY() << "\n";
            if (rectangle.getLeftPoint().getX() <= point.getX() && point.getX() < rectangle.getRightPoint().getX() &&
                rectangle.getLeftPoint().getY() <= point.getY() && point.getY() < rectangle.getRightPoint().getY()) {
                counter++;
            }
        }
    }
    

    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - begin;
    
    std::cout << "Время выполнения: " << elapsed_seconds.count() << " секунд" << "\n";

    return counter;
}


std::vector<Point> GeneratePoints(int number, int range) {
    const int X_PRIME = 65537; // Большое простое число для X
    const int Y_PRIME = 7919; // Большое простое число для Y
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
    vector<Rectangle> rectangles = GenerateRecs(50000);
    vector<Point> points = GeneratePoints(10000, rectangles.size() * 2 - 1);
    
    int res = bruteForce(rectangles, points);

    return 0;
}
