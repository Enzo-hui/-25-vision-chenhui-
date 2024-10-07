#include "Armor.h"

using namespace std;

void deleteErrorArmor(vector<Armor> &armors);

// 匹配装甲板
void matchArmors()
{
    int num1 = 0;
    // 将灯条和每一个其他灯条进行配对
    for (auto light : lights)
    {
        int num2 = 0;

        for (auto light : lights)
        {

            if (num2 = 0)
            {
                continue;
            }
        
            Armor armor = Armor(lights[num1], lights[num2]);
            if (armor.isSuitableArmor()) // 判断装甲板是否合适
            {
                armor.l_index = num1;
                armor.r_index = num2;
                armors.emplace_back(armor);
                break;
            }
            num2++;
        }
        num1++;
    }
}



