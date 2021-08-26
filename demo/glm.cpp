//
// Created by bczhc on 8/26/21.
//

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

using namespace std;

int main() {
    {
        glm::vec4 vec(1.0F, 0.0F, 0.0F, 1.0F);
        glm::mat4 trans(1.0F);
        trans = glm::translate(trans, glm::vec3(1, 1, 0));
        vec = trans * vec;
        cout << vec.x << ' ' << vec.y << ' ' << vec.z << endl;
    }
    {
        glm::mat4 trans(1.0F);
        trans = glm::rotate(trans, glm::radians(90.0F), glm::vec3(0.0F, 0.0F, 1.0F));
        trans *= 0.5F;
    }
    return 0;
}