#pragma once

#ifndef REC_H
#define REC_H

#include "point.hpp"

class Rectangle {
public:
    Rectangle(Point leftP, Point rightP);

    Point getLeftPoint();

    Point getRightPoint();
    
private:
    Point leftPoint;
    Point rightPoint;
};

#endif