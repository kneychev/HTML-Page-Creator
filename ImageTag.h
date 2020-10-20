#pragma once
#include "Tag.h"
class ImageTag : public Tag
{
public:
	ImageTag();
	ImageTag(const ImageTag& other);
	ImageTag& operator=(const ImageTag& rhs);
	virtual ~ImageTag();

	virtual void SaveToFile(std::ofstream& out);
	virtual Tag* Clone() const;
	virtual void print() const; 

};

