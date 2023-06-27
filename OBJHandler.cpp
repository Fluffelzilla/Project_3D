#include "OBJHandler.h"

OBJHandler::OBJHandler()
{

}

void OBJHandler::initialize()
{
    
}

void OBJHandler::LoadFile(ID3D11Device* device, VertexBuffer& vertexBuffer,std::wstring filePath)
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
        std::vector<Triangle> vecTriangles; // stores the combined information to a triangle
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
                    Vertex ver[3];
                    for (int i = 0; i < 3; i++)
                    {
                        ssLine >> x;
                        ssLine >> trash; // trash contains "/" that is unsubable
                        ssLine >> y;
                        ssLine >> trash; // trash contains "/" that is unsubable
                        ssLine >> z;
                        ver[i].pos = vecPos[x - 1];
                        ver[i].tCoor = vecTexcoor[y - 1];
                        ver[i].norm = vecNorm[z - 1];
                    }
                    vecTriangles.emplace_back(ver);
                }
            }

        }
        int byteSizeOfVertex = sizeof(Normal) + sizeof(TextureCoordinate) + sizeof(Position);
        int byteSizeOfTriangle = byteSizeOfVertex * 3;
        int byteSizeOfData = byteSizeOfTriangle * vecTriangles.size();

        vertexBuffer.Initialize(device, byteSizeOfData, vecTriangles.size() * 0, &vecTriangles[0]);
        
    }
}
