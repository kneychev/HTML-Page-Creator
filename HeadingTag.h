#pragma once
#include "Tag.h"

class HeadingTag : public Tag
{
public:
	HeadingTag();
	HeadingTag(const HeadingTag& other);
	HeadingTag& operator=(const HeadingTag& rhs);
	virtual ~HeadingTag();

	virtual void SaveToFile(std::ofstream& out);
	virtual Tag* Clone() const;
	virtual void print() const;

};

