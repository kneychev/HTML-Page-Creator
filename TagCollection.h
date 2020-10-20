#pragma once
#include"Tag.h"
#include "HeadingTag.h"
#include "ParagraphTag.h"
#include "ImageTag.h"
#include "VideoTag.h"
#include "HyperlinkTag.h"

class TagCollection
{
public:
	// We don't need copy constructor and assigning operator because we have one collection
	TagCollection();
	~TagCollection();

	Tag& operator[](int idx);
	const Tag& operator[](int idx) const;
	const int GetSize() const;
	
	void AddTag(const Tag& t);
	void RemoveTag(const char* description);
	void PrintCollection() const;
	void Move(int to, const char* descr);
	void SaveCollectionToFile(const char* fileName) const;
	void ReadCollectionFromFile(const char* fileName);

private:
	void freeCollection();
	void resizeCollection();
	char* extractDesription(const char* line, char* extracted);
	char* extractContentFromHeadParLink(const char* line, char* extracted);
	char* extractContentFromImageTagAndVideoTag(const char* line, char* extracted);
	char* extractLinkFromHyperlinkTag(const char* line, char* extracted);


private:
	Tag ** tags;
	int size;
	int cap;
};

