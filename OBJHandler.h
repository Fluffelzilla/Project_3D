#pragma once
#include<string>
#include"Mesh.h"
#include<fstream>
#include<sstream>
#include"VertexBuffer.h"

struct Position
{
	Position(double x, double y, double z):
		x(x), y(y), z(z){}
	double x, y, z;
};
struct TextureCoordinate
{
	TextureCoordinate(double x, double y) :
		u(u), v(v) {}
	double u, v;
};
struct Normal
{
	Normal(double x, double y, double z) :
		x(x), y(y), z(z) {}
	double x, y, z;
};
struct Vertex
{
	Vertex(double x = 0, double y = 0, double z = 0, double u = 0, double v = 0, double nx = 0, double ny = 0, double nz = 0):
		pos(x,y,z), tCoor(u,v), norm(nx,ny,nz) {}
	Position pos;
	TextureCoordinate tCoor;
	Normal norm;
};

struct Triangle
{
	Triangle(Vertex vertices[3])
	{
		vers[0] = vertices[0];
		vers[1] = vertices[1];
		vers[2] = vertices[2];
	}
	Vertex vers[3];

};

//struct SimpleVertex2
//{
//	float pos[24];
//	float clr[24];
//
//	SimpleVertex2(const std::array<float, 24>& position, const std::array<float, 24>& colour)
//	{
//		for (int i = 0; i < 24; ++i)
//		{
//			pos[i] = position[i];
//			clr[i] = colour[i];
//		}
//	}
//};

class OBJHandler
{
private:

	
public:
	OBJHandler();
	void initialize();
	void LoadFile(ID3D11Device* device,VertexBuffer& vertexBuffer, std::wstring filePath);

};

