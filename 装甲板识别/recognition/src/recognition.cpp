#include "recognition.h"

using namespace cv;
using namespace std;

cv::Mat recognition(Mat img)
{

  // 加强图片对比度
  Mat imgCon;
  img.convertTo(imgCon, -1, 0.7, 0);

  // 将图片转换为灰度图
  Mat imgGray;
  cvtColor(imgCon, imgGray, COLOR_BGR2GRAY);

  // 将图片转换为二值图
  Mat imgBin;
  double thresholdValue = 127; // 设置阈值
  threshold(imgGray, imgBin, thresholdValue, 255, THRESH_BINARY);

  // 高斯模糊
  Mat imgBlur;
  GaussianBlur(imgBin, imgBlur, Size(7, 7), 0, 0);

  // 坎尼边缘识别
  Mat imgCan;
  Canny(imgBlur, imgCan, 0, 127);

  // 寻找边缘
  vector<vector<Point>> contours;
  vector<Vec4i> hierarchy;
  Scalar color = Scalar(0, 0, 255);
  findContours(imgCan, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);

  // 绘制边缘

  // Mat imgDraw=img.clone();
  // for( size_t i = 0; i< contours.size(); i++ )
  // {
  //  drawContours( imgDraw, contours, (int)i, color, 2, LINE_8, hierarchy, 0 );
  // }

  // 凸包
  vector<vector<Point>> hull(contours.size());
  for (size_t i = 0; i < contours.size(); i++)
  {
    convexHull(contours[i], hull[i]);
  }
  Mat imgHull = img.clone();
  for (size_t i = 0; i < contours.size(); i++)
    drawContours(imgHull, hull, (int)i, color);

  // 矩形绘制
  //  vector<vector<Point>>contours_poly(contours.size());
  //  vector<Rect>boundRect(contours.size());
  //  for( size_t i = 0; i < contours.size(); i++ )
  //  {
  //    approxPolyDP( contours[i], contours_poly[i], 3, true );
  //    boundRect[i] = boundingRect( contours_poly[i] );
  //  }
  //  Mat imgRect=img.clone();
  //  for( size_t i = 0; i< contours.size(); i++ )
  //  {
  //    Scalar color = Scalar( 0,0,255 );

  //   rectangle( imgRect, boundRect[i].tl(), boundRect[i].br(), color, 2 );
  // }

  // 旋转矩阵
  imshow("imgCon", imgCon);
  return imgHull;
};