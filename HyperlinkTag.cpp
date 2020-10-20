#include "HyperlinkTag.h"


HyperlinkTag::HyperlinkTag(): Tag(), src(nullptr)
{
}

HyperlinkTag::HyperlinkTag(const HyperlinkTag& other): Tag(other), src(nullptr)
{
	src = new(std::nothrow) char[strlen(other.GetSrc()) + 1];
	if (!src)
	{
		std::cerr << "Not enough memory!\n";
		exit(1);
	}
	strcpy_s(src, strlen(other.GetSrc()) + 1, other.GetSrc());
}

HyperlinkTag& HyperlinkTag::operator=(const HyperlinkTag& rhs)
{
	if (this != &rhs)
	{
		Tag::operator=(rhs);

		delete[] src;
		src = new(std::nothrow) char[strlen(rhs.GetSrc()) + 1];
		if (!src)
		{
			std::cerr << "Not enough memory!\n";
			exit(1);
		}
		strcpy_s(src, strlen(rhs.GetSrc()) + 1, rhs.GetSrc());
	}
	return *this;
}


HyperlinkTag::~HyperlinkTag()
{
	delete[] src;
}

void HyperlinkTag::SetSrc(const char* newSrc)
{
	src = new(std::nothrow) char[strlen(newSrc) + 1];
	if (!src)
	{
		std::cerr << "Not enough memory!\n";
		exit(1);
	}
	strcpy_s(src, strlen(newSrc) + 1, newSrc);
}

const char* HyperlinkTag::GetSrc() const
{
	return src;
}

void HyperlinkTag::SaveToFile(std::ofstream& out)
{
	out << "<a href=\"" << src
		<< "\" descr=\"" << GetDescription()
		<< "\"> " << GetContent() << "</a>\n<br>\n";
}

Tag* HyperlinkTag::Clone() const
{
	return new(std::nothrow) HyperlinkTag(*this);
}

void HyperlinkTag::print() const
{
	std::cout << "<a href=\"" << GetSrc()
		<< "\" descr=\"" << GetDescription()
		<< "\">" << GetContent() << "</a>\n";
}
