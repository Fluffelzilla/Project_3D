#pragma once
#include"OBJHandler.h"
class ModelHandler
{
private:
	int byteSizeOfData;
	std::vector<float> vecTriangles;
public:
	ModelHandler();
	int getByteSizeData();
	void* getVecTrianglesData();
	int getNrOfVertices();
	OBJHandler objhandler;
};

