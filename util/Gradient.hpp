#ifndef GRADIENT_H
#define GRADIENT_H


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <iostream>

class GradientColor {
    public:
        glm::vec3 color;
        double pos;

        GradientColor(glm::vec3 a_color, double a_pos)
        {
            color = a_color;
            pos = a_pos;
        }

};

class Gradient {
    public:
        std::vector<GradientColor> colors;

        //colors should be sorted
        Gradient(std::vector<GradientColor> a_colors)
        {
            colors = a_colors;
        }

        glm::vec3 GetColor(double pos) {
            for (int i = 0; i < colors.size(); i++)
            {
                if (pos < colors.at(i).pos)
                {
                    if (i == 0)
                    {
                        return colors.at(i).color;
                    }

                    if (colors.at(i).pos - pos < pos - colors.at(i - 1).pos)
                    {
                        return colors.at(i).color;
                    } else  {
                        return colors.at(i - 1).color;
                    }
                }
            }

            return colors.at(colors.size() - 1).color;
        }

        
};


#endif