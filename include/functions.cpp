#include "functions.hpp"

float f1(float x, float y){
    return (std::pow(std::pow(x,2) + std::pow(y,2) - 4, 3) - std::pow(x,2)*std::pow(y,3));
}
float f2(float x, float y){
    return (std::pow(x,4) + std::pow(y,4)-x*y-8);
}
float f3(float x, float y){
    return (std::pow(x,3) + y -4);
}
float f4(float x, float y){
    return (std::pow(x,7)-std::pow(y,5)+std::pow(x,2)*std::pow(y,3)- std::pow(x*y,2));
}
float f5(float x, float y){
    return (std::pow(x,2)+std::pow(y,2)+x*y-(std::pow(x*y,2)*0.5-0.25));
}
float f6(float x, float y){
    return (std::abs(x) + std::abs(y)-2);
}
float f7(float x, float y){
    return (std::pow(x,3)+std::pow(y,2)-6*x*y);
}
float f8(float x, float y){
    return (std::pow(x,3)+std::pow(y,3)-3*x*y);
}
float f9(float x, float y){
    return ((std::pow(3*std::pow(x,2)-std::pow(y,2),2)*std::pow(y,2)-(std::pow(std::pow(x,2)+std::pow(y,2),4))));
}
float f10(float x, float y){
    return (std::pow(x,2)*(4-std::pow(x,2))-std::pow(y,2));
}
float f11(float x, float y){
    return (std::pow(y,3)+std::pow(y,2)-5*y-std::pow(x,2)+4);
}
float f12(float x, float y){
    return ((3*std::pow(x,2)-std::pow(y,2)*std::pow(y,2)-(std::pow(std::pow(x,2)+std::pow(y,2),4))));
}


Functions::Functions(){
    this->initFunctions();
}

Functions::~Functions(){
}

std::function<float(float, float)> Functions::getFunction(int i){
    return functions[i];
}

void Functions::initFunctions(){
    this->functions.emplace_back(f1);
    this->functions.emplace_back(f2);
    this->functions.emplace_back(f3);
    this->functions.emplace_back(f4);
    this->functions.emplace_back(f5);
    this->functions.emplace_back(f6);
    this->functions.emplace_back(f7);
    this->functions.emplace_back(f8);
    this->functions.emplace_back(f9);
    this->functions.emplace_back(f10);
    this->functions.emplace_back(f11);
    this->functions.emplace_back(f12);
}

