#pragma once
#include "Tag.h"

class VideoTag : public Tag
{
public:
	VideoTag();
	VideoTag(const VideoTag& other);
	VideoTag& operator=(const VideoTag& rhs);
	virtual ~VideoTag();

	virtual void SaveToFile(std::ofstream& out);
	virtual Tag* Clone() const;
	virtual void print() const; 

};

