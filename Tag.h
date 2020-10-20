#pragma once
#include <iostream>
#include <fstream>

class Tag
{
public:
	Tag();
	Tag(const Tag& other);
	Tag& operator=(const Tag& rhs);
	virtual ~Tag();

	void SetDescription(const char* newDescription);
	void SetContent(const char* newContent);

	const char* GetDescription() const;
	const char* GetContent() const;

	virtual void SaveToFile(std::ofstream& out) = 0;
	virtual Tag* Clone() const = 0;
	virtual void print() const = 0;


private:
	void copyFrom(const Tag& other);
	void free();

private:
	char* description;
	char* content;

};

