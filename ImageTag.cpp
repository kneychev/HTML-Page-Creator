#include "ImageTag.h"

ImageTag::ImageTag(): Tag()
{
}

ImageTag::ImageTag(const ImageTag& other): Tag(other)
{
}

ImageTag& ImageTag::operator=(const ImageTag& rhs)
{
	if (this != &rhs)
	{
		Tag::operator=(rhs);
	}
	return *this;
}


ImageTag::~ImageTag()
{
}

void ImageTag::SaveToFile(std::ofstream& out)
{
	out << "<img src=\"" << GetContent() << "\" "
		<< "descr=\"" << GetDescription() << "\">\n<br>\n";
}

Tag* ImageTag::Clone() const
{
	return new(std::nothrow) ImageTag(*this);
}

void ImageTag::print() const
{
	std::cout << "<img src=\"" << GetContent() << "\" "
		<< "descr=\"" << GetDescription() << "\">\n";
}
