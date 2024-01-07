#pragma once
#include "config.h"

class Material {
public :
	Material(char* fileName);
	void use(int unit);
	~Material();
private:
	unsigned int texture;
};