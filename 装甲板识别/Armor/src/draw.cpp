#include "Armor.h"
//画出装甲板
void drawArmor(cv::Mat frame)
{
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
}
