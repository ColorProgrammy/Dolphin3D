#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include "Vector3.h"

class Mesh {
public:
    std::vector<vec3> vertices;
    std::vector<std::vector<int>> faces;
    
    bool loadFromOBJ(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) return false;

        std::string line;
        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string prefix;
            ss >> prefix;

            if (prefix == "v") {  // Вершины
                float x, y, z;
                ss >> x >> y >> z;
                vertices.push_back(vec3(x, y, z));
            } else if (prefix == "f") {  // Грани
                std::vector<int> face;
                std::string vertexData;
                while (ss >> vertexData) {
                    int vIndex;
                    std::stringstream vs(vertexData);
                    vs >> vIndex;
                    face.push_back(vIndex - 1);  // OBJ индексация с 1
                }
                faces.push_back(face);
            }
        }

        file.close();
        return true;
    }
};
