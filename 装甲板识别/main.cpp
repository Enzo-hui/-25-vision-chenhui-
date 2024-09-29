#include<opencv2/opencv.hpp>
#include"recognition.h"

int main()
{
    cv::Mat img =cv::imread("test.jpg");
    cv::imshow("img",img);
    cv::imshow("finalimg",recognition(img));
    cv::waitKey(0);
    return 0;
}