#pragma once
#include "Tag.h"

class HyperlinkTag : public Tag
{
public:
	HyperlinkTag();
	HyperlinkTag(const HyperlinkTag& other);
	HyperlinkTag& operator=(const HyperlinkTag& rhs);
	virtual ~HyperlinkTag();

	void SetSrc(const char* newSrc);
	const char* GetSrc() const;

	virtual void SaveToFile(std::ofstream& out);
	virtual Tag* Clone() const;
	virtual void print() const;

private:
	char* src;
};

