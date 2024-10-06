#include "Armor.h"

void setArmorVertices(const LightBar &l_light, const LightBar &r_light, Armor &armor)
{
    // 将两个灯条上的顶点赋给装甲板
    cv::Size exLSize(int(l_light.lightRect.size.width), int(l_light.lightRect.size.height * 2));
    cv::Size exRSize(int(r_light.lightRect.size.width), int(r_light.lightRect.size.height * 2));
    cv::RotatedRect exLLight(l_light.center, exLSize, armor.armorAngle);
    cv::RotatedRect exRLight(r_light.center, exRSize, armor.armorAngle);

    cv::Point2f pts_l[4];
    exLLight.points(pts_l);
    cv::Point2f upper_l = pts_l[2];
    cv::Point2f lower_l = pts_l[3];

    cv::Point2f pts_r[4];
    exRLight.points(pts_r);
    cv::Point2f upper_r = pts_r[1];
    cv::Point2f lower_r = pts_r[0];

    armor.armorVertices[0] = upper_l;
    armor.armorVertices[1] = upper_r;
    armor.armorVertices[2] = lower_r;
    armor.armorVertices[3] = lower_l;
}

Armor::Armor()//无参构造
{
    l_index = -1;
    r_index = -1;
    l_light = LightBar();
    r_light = LightBar();
    armorVertices.resize(4);
    center = Point2f();
    armorRect = Rect();
    armorImg = Mat();
}

Armor::Armor(const LightBar &l_light, const LightBar &r_light)//有参构造
{
    this->l_light = l_light;
    this->r_light = r_light;

    armorAngle = (l_light.angle + r_light.angle) / 2;

    armorVertices.resize(4);
    setArmorVertices(l_light, r_light, *this);

   

    armorRect = boundingRect(armorVertices);
}

Armor ::~Armor()
{
}

//  装甲板左右灯条角度差
float Armor::getAngleDiff() const
{
    float angle_diff = abs(l_light.angle - r_light.angle); //  灯条的角度差
    return angle_diff;
}

// 灯条错位度角(两灯条中心连线与水平线夹角)
float Armor::getDeviationAngle() const
{
    float delta_x = r_light.center.x - l_light.center.x;               // Δx
    float delta_y = r_light.center.y - l_light.center.y;               // Δy
    float deviationAngle = abs(atan(delta_y / delta_x)) * 180 / CV_PI; // tanθ=Δy/Δx
    return deviationAngle;
}

// 灯条位置差距 两灯条中心x方向差距比值
float Armor::getDislocationX() const
{
    float meanLen = (l_light.length + r_light.length) / 2;
    float xDiff = abs(l_light.center.x - r_light.center.x); // x distance ration y轴方向上的距离比值（y轴距离与灯条平均值的比）
    float xDiff_ratio = xDiff / meanLen;
    return xDiff_ratio;
}

// 灯条位置差距 两灯条中心Y方向差距比值
float Armor::getDislocationY() const
{
    float meanLen = (l_light.length + r_light.length) / 2;
    float yDiff = abs(l_light.center.y - r_light.center.y); // y distance ration x轴方向上的距离比值（x轴距离与灯条平均值的比）
    float yDiff_ratio = yDiff / meanLen;
    return yDiff_ratio;
}

//  左右灯条长度差比值
float Armor::getLengthRation() const
{
    float length_diff = abs(l_light.length - r_light.length);
    float lengthDiffRation = length_diff / MAX(l_light.length, r_light.length);
    return lengthDiffRation;
}

//   判断本装甲板是否是合适的装甲板
bool Armor::isSuitableArmor() const
{
    return this->getAngleDiff() < 6 &&       //灯条角度差判断，需小于允许的最大角差
           this->getDeviationAngle() < 50 && //灯条错位度角(两灯条中心连线与水平线夹角)判断
           this->getDislocationX() < 5 &&  //灯条位置差距 两灯条中心x、y方向差距不可偏大（用比值作为衡量依据）
           this->getDislocationY() < 0.5 &&  //灯条位置差距 两灯条中心x、y方向差距不可偏大（用比值作为衡量依据）
           this->getLengthRation() < 0.5;
}
