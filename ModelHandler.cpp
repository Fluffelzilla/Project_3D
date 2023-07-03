#include "ModelHandler.h"

ModelHandler::ModelHandler()
{
	objhandler.LoadFile(L"objects/otherCube.obj");
}

int ModelHandler::getByteSizeData()
{
	return byteSizeOfData;
}

void* ModelHandler::getVecTrianglesData()
{
	return &vecTriangles[0];
}

int ModelHandler::getNrOfVertices()
{
	return vecTriangles.size() / 8;
}
