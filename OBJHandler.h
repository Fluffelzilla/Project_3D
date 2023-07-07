#pragma once
#include<string>
#include"Mesh.h"
#include<fstream>
#include<sstream>
#include"Shader.h"

struct Position
{
	Position(double x, double y, double z):
		x(x), y(y), z(z){}
	double x, y, z;
};
struct TextureCoordinate
{
	TextureCoordinate(double x, double y) :
		u(x), v(y) {}
	double u, v;
};
struct Normal
{
	Normal(double x, double y, double z) :
		x(x), y(y), z(z) {}
	double x, y, z;
};

class OBJHandler
{
private:
	int byteSizeOfData;
	std::vector<float> vecTriangles; // stores the combined information to a triangle
	
public:
	OBJHandler();
	void LoadFile(std::wstring filePath);
	int getByteSizeData();
	void* getVecTrianglesData();
	int getNrOfVertices();
	
};

