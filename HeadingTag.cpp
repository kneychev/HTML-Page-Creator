#include "HeadingTag.h"

HeadingTag::HeadingTag() : Tag()
{
}

HeadingTag::HeadingTag(const HeadingTag& other): Tag(other)
{
}

HeadingTag& HeadingTag::operator=(const HeadingTag& rhs)
{
	if (this != &rhs)
	{
		Tag::operator=(rhs);
	}
	return *this;
}


HeadingTag::~HeadingTag()
{
}

void HeadingTag::SaveToFile(std::ofstream& out)
{
	out << "<h2 descr=\"" << GetDescription() << "\">"
		<< GetContent() << "</h2>\n<br>\n";
}

Tag* HeadingTag::Clone() const
{
	return new(std::nothrow) HeadingTag(*this);
}

void HeadingTag::print() const
{
	std::cout << "<h2 descr=\"" << GetDescription() << "\">"
		<< GetContent() << "</h2>\n";
}
