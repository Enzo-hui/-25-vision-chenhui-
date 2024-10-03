#pragma once 
#include <iostream>
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <opencv2/opencv.hpp>
#include <math.h>
#include <mutex>
#include <thread>
#include <condition_variable>
#include <queue>
#include <atomic>



using namespace cv;

extern std::mutex mtx;

void getdistance(Mat img,std::vector<Point2f> contours);
void reset();

// recognition函数的声明
void recognition(const Mat frame);
class LightBar
{
public:
    LightBar();
    LightBar(const RotatedRect &light); // RotatedRect在"math.h"下
    ~LightBar();

public:
    RotatedRect lightRect; // 灯条的旋转矩形
    float length;          // 灯条的长度
    Point2f center;        // 灯条的中心
    float angle;
};

// 装甲板类的声明
class Armor
{
public:
    Armor();

    Armor(const LightBar &l_light, const LightBar &r_light);
    ~Armor();

    float getAngleDiff() const;

    float getDeviationAngle() const;

    float getDislocationX() const;

    float getDislocationY() const;

    float getLengthRation() const;

    bool isSuitableArmor() const;

public:
    LightBar l_light, r_light;
    int l_index, r_index;
    std::vector<Point2f> armorVertices;
    Point2f center;
    Rect armorRect;
    float armorAngle;
    Mat armorImg;
};
extern std::vector<LightBar> lights;
extern std::vector<Armor> armors;
void matchArmors();
void deleteErrorArmor(std::vector<Armor> &aromrs);
float getPointsDistance(const Point2f& a, const Point2f& b);