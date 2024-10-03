#include "Armor.h"

using namespace std;

void deleteErrorArmor(vector<Armor> &armors);

void matchArmors()
{
    for (int i = 0; i < lights.size() - 1; i++)
    {
        for (int j = i + 1; j < lights.size(); j++)
        {
            Armor armor = Armor(lights[i], lights[j]);
            if (armor.isSuitableArmor())
            {
                armor.l_index = i;
                armor.r_index = j;
                armors.emplace_back(armor);
            }
        }
        deleteErrorArmor(armors);
    }
}

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

// //两点间的距离
// float getPointsDistance(const Point2f& a, const Point2f& b) 
// {
// 	float delta_x = a.x - b.x;
// 	float delta_y = a.y - b.y;
// 	return sqrt(delta_x * delta_x + delta_y * delta_y);
// }