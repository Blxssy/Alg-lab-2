#include "../include/rec.hpp"

Rectangle::Rectangle(Point leftP, Point rightP){
    this->leftPoint = leftP;
    this->rightPoint = rightP;
}

Point Rectangle::getLeftPoint(){
    return leftPoint;
}

Point Rectangle::getRightPoint(){
    return rightPoint;
}