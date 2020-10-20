#include "Tag.h"

Tag::Tag() : description(nullptr), content(nullptr)
{
}

Tag::Tag(const Tag& other)
{
	copyFrom(other);
}

Tag& Tag::operator=(const Tag& rhs)
{
	if (this != &rhs)
	{
		free();
		copyFrom(rhs);
	}
	return *this;
}


Tag::~Tag()
{
	free();
}

void Tag::SetDescription(const char* newDescription)
{
	description = new(std::nothrow) char[strlen(newDescription) + 1];
	if (!description)
	{
		std::cerr << "Could not allocate memory!\n";
		exit(1);
	}
	strcpy_s(description, strlen(newDescription) + 1, newDescription);
}

void Tag::SetContent(const char* newContent)
{
	content = new(std::nothrow) char[strlen(newContent) + 1];
	if (!content)
	{
		std::cerr << "Could not allocate memory!\n";
		exit(1);
	}
	strcpy_s(content, strlen(newContent) + 1, newContent);
}

const char* Tag::GetDescription() const
{
	return description;
}

const char* Tag::GetContent() const
{
	return content;
}

void Tag::copyFrom(const Tag & other)
{
	description = new(std::nothrow) char[strlen(other.description) + 1];
	if (!description)
	{
		std::cerr << "Could not allocate memory!\n";
		exit(1);
	}
	strcpy_s(description, strlen(other.description) + 1, other.description);

	content = new(std::nothrow) char[strlen(other.content) + 1];
	if (!content)
	{
		std::cerr << "Could not allocate memory!\n";
		exit(1);
	}
	strcpy_s(content, strlen(other.content) + 1, other.content);
}

void Tag::free()
{
	delete[] description;
	delete[] content;
}
