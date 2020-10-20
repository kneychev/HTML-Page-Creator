#include "ParagraphTag.h"

ParagraphTag::ParagraphTag(): Tag()
{
}

ParagraphTag::ParagraphTag(const ParagraphTag& other) : Tag(other)
{
}

ParagraphTag& ParagraphTag::operator=(const ParagraphTag& rhs)
{
	if (this != &rhs)
	{
		Tag::operator=(rhs);
	}
	return *this;
}


ParagraphTag::~ParagraphTag()
{
}

void ParagraphTag::SaveToFile(std::ofstream& out)
{
	out << "<p descr=\"" << GetDescription() << "\">"
		<< GetContent() << "</p>\n<br>\n";
}

Tag* ParagraphTag::Clone() const
{
	return new(std::nothrow) ParagraphTag(*this);
}

void ParagraphTag::print() const
{
	std::cout << "<p descr=\"" << GetDescription() << "\">"
		<< GetContent() << "</p>\n";
}
