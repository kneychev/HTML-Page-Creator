#pragma once
#include "TagCollection.h"

class PageCreator
{
public:
	PageCreator();
	~PageCreator();

	void Run();

private:
	void processDescription(char* descr); // removing "<"

private:
	TagCollection tags;
};

