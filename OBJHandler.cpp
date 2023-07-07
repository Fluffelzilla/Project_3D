#include "OBJHandler.h"

OBJHandler::OBJHandler()
{

}

void OBJHandler::LoadFile(std::wstring filePath)
{
    bool couldLoadFile = false;
    std::wifstream fileIn(filePath.c_str()); //loading the file
    if (fileIn)
    {
        couldLoadFile = true;
        std::wstring line; // string to place the loaded text in
        std::vector<Position> vecPos; // a vector to store a vertex position
        std::vector<TextureCoordinate> vecTexcoor; // vector to store texturecoordinates in
        std::vector<Normal> vecNorm; // vector to stor nomals in
         
        while (std::getline(fileIn,line)) // gets a line in the obj file
        {
            std::wstringstream ssLine(line); //puts line into buffer
            if (line.size()>0)
            {
                wchar_t trash; //contains unusable information, used for emtying other variable
                std::wstring command;
                ssLine >> command; // moves first object in buffer to command, to identify its type
                double x, y, z;

                //cheks what command contains and handle the remaining content of the buffer
                if (command==L"v")
                {
                    ssLine >> x;
                    ssLine >> y;
                    ssLine >> z;
                    //  emplace_back() constructs the object in-place, potentially avoiding a copy operation. (is more work for the compiler)
                    vecPos.emplace_back(x,y,z); // add information to vector
                }
                else if (command == L"vt")
                {
                    ssLine >> x;
                    ssLine >> y;
                    vecTexcoor.emplace_back(x, y); // add information to vector
                }
                else if (command == L"vn")
                {
                    ssLine >> x;
                    ssLine >> y;
                    ssLine >> z;
                    vecNorm.emplace_back(x, y, z); // add information to vector
                }

                // the following function creates a triangle from the vertex position, texturecoordinates and normal,
                // also the obj file starts with vertex 1 and we are therefor changing it to vertex 0 as a list starts at 0.
                else if (command == L"f")
                {
                    for (int i = 0; i < 3; i++)
                    {
                        ssLine >> x;
                        ssLine >> trash; // trash contains "/" that is unsubable
                        ssLine >> y;
                        ssLine >> trash; // trash contains "/" that is unsubable
                        ssLine >> z;
                        vecTriangles.emplace_back(vecPos[x - 1].x);
                        vecTriangles.emplace_back(vecPos[x - 1].y);
                        vecTriangles.emplace_back(vecPos[x - 1].z);
                        vecTriangles.emplace_back(vecTexcoor[y - 1].u);
                        vecTriangles.emplace_back(vecTexcoor[y - 1].v);                  
                        vecTriangles.emplace_back(vecNorm[z - 1].x);
                        vecTriangles.emplace_back(vecNorm[z - 1].y);
                        vecTriangles.emplace_back(vecNorm[z - 1].z);
                    }
                }
            }

        }

        byteSizeOfData = vecTriangles.size() * sizeof(float);

    }
}

int OBJHandler::getByteSizeData()
{
    return byteSizeOfData;
}


void* OBJHandler::getVecTrianglesData()
{
    return &vecTriangles[0];
}

int OBJHandler::getNrOfVertices()
{
    //every vertex uses 8 floats:
    //position x,y,z = 3 floats
    //texturecoordinates u,v = 2 floats
    //normal = x,y,z = 3 floats
    return vecTriangles.size()/8;
}

