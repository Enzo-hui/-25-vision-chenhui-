#include "Armor.h"

// 找大数函数的实现
float Max(float a, float b)
{
    if (a > b)
        return a;
    else
        return b;
}
// 灯条的无参构造函数
LightBar::LightBar()
{
    lightRect = RotatedRect();
    length = 0;
    center = Point2f();
    angle = 0;
}

// 灯条的有参构造函数
LightBar::LightBar(const RotatedRect &lightRect)
{
    this->lightRect = lightRect;
    center = lightRect.center;
    length = Max(lightRect.size.height, lightRect.size.width);
    //判断旋转矩形的偏角，使得偏角的绝对值小于90
    if (lightRect.angle > 90)
        angle = lightRect.angle - 180;
    else
        angle = lightRect.angle;
}

LightBar::~LightBar()
{

};
