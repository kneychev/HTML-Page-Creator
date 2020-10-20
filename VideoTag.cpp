#include "VideoTag.h"

VideoTag::VideoTag(): Tag()
{
}

VideoTag::VideoTag(const VideoTag& other): Tag(other)
{
}

VideoTag& VideoTag::operator=(const VideoTag& rhs)
{
	if (this != &rhs)
	{
		Tag::operator=(rhs);
	}
	return *this;
}

VideoTag::~VideoTag()
{
}

void VideoTag::SaveToFile(std::ofstream& out)
{
	out << "<iframe src=\"" << GetContent() << "\" "
		<< "descr=\"" << GetDescription() << "\"></iframe>\n<br>\n";
}

Tag* VideoTag::Clone() const
{
	return new(std::nothrow) VideoTag(*this);
}

void VideoTag::print() const
{
	std::cout  << "<iframe src=\"" << GetContent() << "\" "
		<< "descr=\"" << GetDescription() << "\"></iframe>\n";
}
