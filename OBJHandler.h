#pragma once
#include<string>

class OBJHandler
{
private:
	std::string fileName;
public:
	OBJHandler(std::string filePath);
	bool LoadFile();
};

