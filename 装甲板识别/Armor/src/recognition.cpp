#include "Armor.h"

using namespace cv;
using namespace std;

#include "Armor.h"

std::mutex mtx;
std::vector<LightBar> lights;
std::vector<Armor> armors;
// 清空上一帧所绘制的灯条
void reset()
{
  lights.clear();
  armors.clear();
}

void recognition(const Mat frame)
{

 

  // HSV颜色识别
  Mat imgHSV, imgBin;
  int hmin = 0, hmax = 30, smin = 120, smax = 255, vmin = 120, vmax = 255;
  cvtColor(frame, imgHSV, COLOR_BGR2HSV);
  Scalar lower(hmin, smin, vmin);
  Scalar upper(hmax, smax, vmax);
  inRange(imgHSV, lower, upper, imgBin);

  // 高斯模糊
  Mat imgBlur;
  GaussianBlur(imgBin, imgBlur, Size(7, 7), 0, 0);

  imgHSV.release();
  imgBin.release();



  // 寻找边缘
  vector<vector<Point>> contours;
  Scalar color = Scalar(0, 0, 255);


  // 旋转矩阵
  Mat imgCon = imgBlur.clone();
  imgBlur.release();
  findContours(imgCon, contours, 0, 2);
  imgCon.release();
  RotatedRect lightRect;
  LightBar light;
  for (const auto &contour : contours) // 遍历容器contours中的每一项
  {
    if (contour.size() < 6)
      continue;
    if (contourArea(contour) < 100 ||contourArea(contour)>2000)//面积初筛
      continue;

    lightRect = fitEllipse(contour);//拟合椭圆
    light = LightBar(lightRect);//旋转矩形

    if (abs(light.angle) > 45)//筛选灯条角度
      continue;

    lights.emplace_back(light);
  }
};