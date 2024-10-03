#include "Armor.h"

float f = 13.5, u = 720, v = 540, dx = 2.88 / 1440, dy = 2.16 / 1080;
float fu = f / dx, fv = f / dy;
float a = 0, b = 0, c = 0, d = 0;
float e = 1;

cv::Mat camera_matrix = (Mat_<float>(3, 3) << fu, a, u,
                         b, fv, v,
                         c, d, e);
cv::Mat distCoeffs = (Mat_<float>(1, 4) << 0, 0, 0, 0);
void getdistance(Mat img, std::vector<Point2f> targetContour)
{   
    double distance;
    Mat rvec,tVec;
    std::vector<cv::Point3f> objectPoints; // 世界坐标系中的点
    std::vector<cv::Point2f> imagePoints;  // 图像坐标系中的点
    std::vector<cv::Point3f> Amror_3D;     // 装甲板的3D坐标
    double width = 135;
    double height = 125;
    double half_x = width / 2.0;
    double half_y = height / 2.0;
    Amror_3D.push_back(Point3f(-half_x, half_y, 0));//左上
    Amror_3D.push_back(Point3f(half_x, half_y, 0));//右上
    Amror_3D.push_back(Point3f(half_x, -half_y, 0));//左下
    Amror_3D.push_back(Point3f(-half_x, -half_y, 0));//右下
    solvePnP(Amror_3D, targetContour, camera_matrix, distCoeffs, rvec, tVec, false, SOLVEPNP_ITERATIVE);
    distance=cv::norm(tVec);
    cv::Mat rotationMatrix;
    cv::Rodrigues(rvec, rotationMatrix); // 将旋转向量转换为旋转矩阵
    cv::Point2f axis = rotationMatrix.at<double>(0, 0) * cv::Point2f(1, 0); // 计算旋转轴
    double angle = acos(rotationMatrix.at<double>(0, 0)); // 计算旋转角度

    // 输出距离和偏转角度
    std::cout << "Distance to armor plate: " << distance << std::endl;
    std::cout << "Rotation angle: " << angle << std::endl;
}