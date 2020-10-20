#pragma once
#include "Tag.h"

class ParagraphTag : public Tag
{
public:
	ParagraphTag();
	ParagraphTag(const ParagraphTag& other);
	ParagraphTag& operator=(const ParagraphTag& rhs);
	virtual ~ParagraphTag();

	virtual void SaveToFile(std::ofstream& out);
	virtual Tag* Clone() const;
	virtual void print() const;

};
