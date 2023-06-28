#pragma once
#include<string>
#include"Mesh.h"
#include<fstream>
#include<sstream>

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
//struct Vertex
//{
//	Vertex(double x = 0, double y = 0, double z = 0, double u = 0, double v = 0, double nx = 0, double ny = 0, double nz = 0):
//		pos(x,y,z), tCoor(u,v), norm(nx,ny,nz) {}
//	Position pos;
//	TextureCoordinate tCoor;
//	Normal norm;
//};

//struct Triangle
//{
//	Triangle(Vertex vertices[3])
//	{
//		vers[0] = vertices[0];
//		vers[1] = vertices[1];
//		vers[2] = vertices[2];
//	}
//	Vertex vers[3];
//
//};

class OBJHandler
{
private:
	int byteSizeOfData;
	std::vector<float> vecTriangles; // stores the combined information to a triangle
	
public:
	OBJHandler();
	void LoadFile(std::wstring filePath);
	int getByteSizeData();
	std::vector<float> getVecTriangles();
	void* getVecTrianglesData();
	int getNrOfVertices();
};

