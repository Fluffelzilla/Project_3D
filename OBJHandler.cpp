#include "OBJHandler.h"

OBJHandler::OBJHandler()
{

}

void OBJHandler::initialize()
{
    
}

bool OBJHandler::LoadFile(std::wstring filePath)
{
    bool couldLoadFile = false;
    std::wifstream fileIn(filePath.c_str());
    if (fileIn)
    {
        couldLoadFile = true;
        std::wstring line;
        std::vector<Position> vecPos;
        std::vector<TextureCoordinate> vecTexcoor;
        std::vector<Normal> vecNorm;
        std::vector<Triangle> vecTriangles;
        while (std::getline(fileIn,line))
        {
            std::wstringstream ssLine(line);
            if (line.size()>0)
            {
                wchar_t trash;
                std::wstring command;
                //ssLine >> first;
                ssLine >> command;
                double x, y, z;
                if (command==L"v")
                {
                    ssLine >> x;
                    ssLine >> y;
                    ssLine >> z;
                    vecPos.emplace_back(x,y,z);
                }
                else if (command == L"vt")
                {
                    ssLine >> x;
                    ssLine >> y;
                    vecTexcoor.emplace_back(x, y);
                }
                else if (command == L"vn")
                {
                    ssLine >> x;
                    ssLine >> y;
                    ssLine >> z;
                    vecNorm.emplace_back(x, y, z);
                }
                else if (command == L"f")
                {
                    Vertex ver[3];
                    for (int i = 0; i < 3; i++)
                    {
                        ssLine >> x;
                        ssLine >> trash;
                        ssLine >> y;
                        ssLine >> trash;
                        ssLine >> z;
                        ver[i].pos = vecPos[x - 1];
                        ver[i].tCoor = vecTexcoor[y - 1];
                        ver[i].norm = vecNorm[z - 1];
                    }
                    vecTriangles.emplace_back(ver);
                }
            }

        }
        bool hello = true;
    }
    return couldLoadFile;
}
