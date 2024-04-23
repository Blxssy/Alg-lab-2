#pragma once

#ifndef POINT_H
#define POINT_H

class Point {
public:
    Point(int x, int y);

    Point();

    int getX();

    int getY();
    
private:
    int x;
    int y;
};

#endif