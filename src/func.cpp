#include "../include/func.hpp"



int Comp(vector<int>& arr, int x) {
    int left = 0;
    int right = arr.size() - 1;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (arr[mid] > x) {
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    return left - 1;
}

vector<vector<int>> BuildMap(std::vector<Rectangle>& rectangles) {
    auto begin = std::chrono::steady_clock::now();

    vector<vector<int>> map;
    for (auto& rectangle : rectangles) {
        compX.push_back(rectangle.getLeftPoint().getX());
        compX.push_back(rectangle.getRightPoint().getX());
        compY.push_back(rectangle.getLeftPoint().getY());
        compY.push_back(rectangle.getRightPoint().getY());
    }
    std::sort(compX.begin(), compX.end());
    compX.erase(std::unique(compX.begin(), compX.end()), compX.end());

    std::sort(compY.begin(), compY.end());
    compY.erase(std::unique(compY.begin(), compY.end()), compY.end());

    map.resize(compX.size(), std::vector<int>(compY.size(), 0));

    for (auto& rectangle : rectangles) {
        Point leftCompressed(Comp(compX, rectangle.getLeftPoint().getX()), Comp(compY, rectangle.getLeftPoint().getY()));
        Point rightCompressed(Comp(compX, rectangle.getRightPoint().getX()), Comp(compY, rectangle.getRightPoint().getY()));
        for (int i = leftCompressed.getX(); i < rightCompressed.getX(); ++i) {
                for (int j = leftCompressed.getY(); j < rightCompressed.getY(); ++j) {
                map[i][j]++;
            }
        }
    }

    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - begin;
    std::cout << "Build Map: " << elapsed_seconds.count() << " seconds" << "\n";

    return map;
}

int Map(vector<vector<int>>& map, Point point) {
    int x = Comp(compX, point.getX());
    int y = Comp(compY, point.getY());
    if (x < 0 || y < 0) {
        return 0;
    }

    return map[x][y];
}

void MapTime(vector<vector<int>>& map, vector<Point>& points){
    size_t n = points.size();
    auto begin = std::chrono::steady_clock::now();

    for (size_t i = 0; i < n; ++i) {
        Map(map, points[i]);
    }

    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - begin;
    std::cout << "Execution time Map: " << elapsed_seconds.count() << " seconds" << "\n";
}

int BruteForce(vector<Rectangle>& recs, Point point){
    int counter = 0;

    for (Rectangle& rectangle : recs) {
        if (rectangle.getLeftPoint().getX() <= point.getX() && point.getX() < rectangle.getRightPoint().getX() &&
            rectangle.getLeftPoint().getY() <= point.getY() && point.getY() < rectangle.getRightPoint().getY()) {
            counter++;
        }
    }

    return counter;
}

void BruteForceTime(vector<Rectangle>& recs, vector<Point>& points){
    size_t n = points.size();
    auto begin = std::chrono::steady_clock::now();

    for (size_t i = 0; i < n; ++i) {
        BruteForce(recs, points[i]);
    }

    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - begin;
    std::cout << "Execution time BruteForce: " << elapsed_seconds.count() << " seconds" << "\n";
}