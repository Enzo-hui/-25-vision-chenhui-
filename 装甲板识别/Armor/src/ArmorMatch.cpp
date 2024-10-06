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
        deleteErrorArmor(armors); // 删除错误装甲板
    }
}


// 删除错误的装甲板
void deleteErrorArmor(vector<Armor> &aromrs)
{
    int length = armors.size();
    vector<Armor>::iterator it = armors.begin();
    for (size_t i = 0; i < length; i++)
    {
        for (size_t j = i + 1; j < length; j++)
        {
            if (armors[i].l_index == armors[j].l_index ||
                armors[i].l_index == armors[j].r_index ||
                armors[i].r_index == armors[j].l_index ||
                armors[i].r_index == armors[j].r_index)
            {
                armors[i].getDeviationAngle() > armors[j].getDeviationAngle() ? armors.erase(it + i) : armors.erase(it + j);
            }
        }
    }
}

