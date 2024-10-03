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

  // // 加强图片对比度
  // Mat imgCon;
  // img.convertTo(imgCon, -1, 0.7, 0);

  // // 将图片转换为灰度图
  // Mat imgGray;
  // cvtColor(imgCon, imgGray, COLOR_BGR2GRAY);

  // // 将图片转换为二值图
  // Mat imgBin;
  // double thresholdValue = 127; // 设置阈值
  // threshold(imgGray, imgBin, thresholdValue, 255, THRESH_BINARY);

  // HSV颜色识别
  Mat imgHSV, imgBin;
  int hmin = 0, hmax = 50, smin = 43, smax = 255, vmin = 46, vmax = 255;
  cvtColor(frame, imgHSV, COLOR_BGR2HSV);
  Scalar lower(hmin, smin, vmin);
  Scalar upper(hmax, smax, vmax);
  inRange(imgHSV, lower, upper, imgBin);

  // 高斯模糊
  Mat imgBlur;
  GaussianBlur(imgBin, imgBlur, Size(7, 7), 0, 0);

  imgHSV.release();
  imgBin.release();

  // 坎尼边缘识别
  // Mat imgCan;
  // Canny(imgBlur, imgCan, 0, 127);

  // 寻找边缘
  vector<vector<Point>> contours;
  Scalar color = Scalar(0, 0, 255);

  // 绘制边缘

  // Mat imgDraw=img.clone();
  // for( size_t i = 0; i< contours.size(); i++ )
  // {
  //  drawContours( imgDraw, contours, (int)i, color, 2, LINE_8, hierarchy, 0 );
  // }

  // 凸包
  // vector<vector<Point>> hull(contours.size());
  // for (size_t i = 0; i < contours.size(); i++)
  // {
  //   convexHull(contours[i], hull[i]);
  // }
  // Mat imgHull = img.clone();
  // for (size_t i = 0; i < contours.size(); i++)
  //   drawContours(imgHull, hull, (int)i, color);

  // 矩形绘制
  // vector<vector<Point>> contours_poly(contours.size());
  // vector<Rect> boundRect(contours.size());
  // for (size_t i = 0; i < contours.size(); i++)
  // {
  //   approxPolyDP(contours[i], contours_poly[i], 3, true);
  //   boundRect[i] = boundingRect(contours_poly[i]);
  // }
  // Mat imgRect = img.clone();
  // for (size_t i = 0; i < contours.size(); i++)
  // {
  //   Scalar color = Scalar(0, 0, 255);

  //   rectangle(imgRect, boundRect[i].tl(), boundRect[i].br(), color, 2);
  // }

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
    if (contourArea(contour) < 200 || contourArea(contour) > 1500)
      continue;

    lightRect = fitEllipse(contour);
    light = LightBar(lightRect);

    if (abs(light.angle) > 45)
      continue;

    lights.emplace_back(light);
  }
  // Mat imgDraw = img.clone();
  // for (auto light : lights)
  // {
  //   Point2f lightVertices[4];
  //   light.lightRect.points(lightVertices);

  // 画出灯条轮廓
  //   for (size_t i = 0; i < 4; i++)
  //   {
  //     line(imgDraw, lightVertices[i], lightVertices[(i + 1) % 4], Scalar(0, 0, 255), 1, 8, 0);
  //   }
  // }
  // sort(lights.begin(), lights.end(),
  //      [](LightBar &a1, LightBar &a2)
  //      { return a1.center.x < a2.center.x; });

  matchArmors();
  // 画出装甲板轮廓
  Mat imgAmr = frame.clone();
  if (!armors.empty())
  {
    putText(imgAmr, "ARMOR FOUND!", Point(100, 50), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 255, 0), 1, 8, false);
    for (auto armor : armors)
    {
      for (size_t i = 0; i < 4; i++)
      {
        line(imgAmr, armor.armorVertices[i], armor.armorVertices[(i + 1) % 4], Scalar(0, 0, 255), 2, 8, 0);
      }
    }
  }
  else
  {
    {
      putText(imgAmr, "ARMOR NOT FOUND!", Point(100, 50), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 0, 255), 1, 8, false); // title NOT FOUND 大标题 “没找到装甲板”
    }
  }
  imshow("test", imgAmr);
  for (auto armor : armors)
  {
    getdistance(imgAmr, armor.armorVertices);
  }
  
};