#include "TagCollection.h"

const int MAX_ROW_SIZE = 1024;
const int MAX_DESCRIPTION_LENGTH = 512;
const int MAX_TAG_SIZE = 7;

TagCollection::TagCollection(): tags(nullptr), size(0), cap(0)
{
}

TagCollection::~TagCollection()
{
	freeCollection();
}

Tag& TagCollection::operator[](int idx)
{
	return *tags[idx];
}

const Tag& TagCollection::operator[](int idx) const
{
	return *tags[idx];
}

const int TagCollection::GetSize() const
{
	return size;
}

void TagCollection::AddTag(const Tag& t)
{
	if (size == cap)
		resizeCollection();

	tags[size] = t.Clone();
	if (!tags[size])
	{
		std::cerr << "Could not allocate memory!\n";
		exit(1);
	}
	++size;
}

void TagCollection::RemoveTag(const char* description)
{
	int idx = -1;
	for (int i = 0; i < size; ++i) // here we find the element with the right description
	{
		if (strcmp(tags[i]->GetDescription(), description) == 0)
		{
			idx = i; // index of the element we want to delete
			break;
		}
	}

	if (idx == -1)
	{
		std::cerr << "The description does not exist!\n";
		return;
	}

	delete[] tags[idx]; // deleting the element

	--size;
	for (int i = idx; i < size; ++i) // redirecting pointers
	{
		tags[i] = tags[i + 1];
	}

}

void TagCollection::PrintCollection() const
{
	if (size == 0)
	{
		std::cout << "Empty...\n";
		return;
	}

	for (int i = 0; i < size; ++i)
	{
		std::cout << "On position " << i + 1 << ":\n";
		tags[i]->print();
	}
}

void TagCollection::Move(int to, const char* descr)
{
	if (to > size)
	{
		std::cerr << "The position you entered is bigger than the size of the array!\n";
		return;
	}

	int from = -1;
	for (int i = 0; i < size; ++i) // finding the element we want to move
	{
		if (strcmp(tags[i]->GetDescription(), descr) == 0)
		{
			from = i;
			break;
		}
	}

	if (from == -1)
	{
		std::cerr << "Element wiht the description, you putted in, does not exist!\n";
		return;
	}

	if (to == from + 1 || (to == 0 && from == 0))
	{
		std::cerr << "The row is at this position already!\n";
		return;
	}

	if (from < to) // if the element is before the position we want to move to
	{
		Tag* tmp = tags[from]; // "pointing" the element
		for (int i = from; i < to; ++i)
		{
			tags[i] = tags[i + 1]; // assigning pointers
		}
		tags[to - 1] = tmp; // assigning the pointer of "pointed" element, in the position
	}
	else // if the element is after the position we want to move to
	{
		Tag* tmp = tags[from];
		for (int i = from - 1; i >= to - 1; --i)
		{
			tags[i + 1] = tags[i];
		}
		tags[to - 1] = tmp;
	}
}

void TagCollection::SaveCollectionToFile(const char* fileName) const
{
	std::ofstream outFile;
	outFile.open(fileName, std::ios::trunc);
	if (!outFile)
	{
		std::cerr << "Could not open " << fileName << "!\n";
		return;
	}
	outFile << "<!DOCTYPE html>\n<html>\n<head></head>\n<body>\n";

	for (int i = 0; i < size; ++i)
	{
		tags[i]->SaveToFile(outFile);
	}
	outFile << "</body>\n</html>";
	outFile.close();
}

void TagCollection::ReadCollectionFromFile(const char* fileName)
{
	std::ifstream inFile(fileName); // trying to open the file
	if (!inFile)
	{
		std::cerr << "Error: Can't open " << fileName << "!\n";
		std::cout << "-> File " << fileName << " created!\n";

		std::ofstream out(fileName); // create file
		if (!out)
		{
			std::cerr << "Something is seriously wrong.\nCan't open "
				<< fileName << " again!\n";
			return;
		}
		out.close();
		
		return;
	}

	char rowBuffer[MAX_ROW_SIZE];
	char tagBuffer[MAX_TAG_SIZE];

	while (!inFile.eof()) // reading to the end of file
	{
		inFile.getline(rowBuffer, MAX_ROW_SIZE); // reading line by line
		int j = 0;
		for (int i = 1; i < MAX_TAG_SIZE; ++i) // extracting the tag from the row.
		{									   // We know that the tag is at the beginning,
			if (rowBuffer[i] == ' ')		   // so we start from the second symbol,
				break;						   // which is the first letter of the tag,
											   // and continue untill we meet "space",
			tagBuffer[j++] = rowBuffer[i];	   // which is after the end of the tag name.
		}
		tagBuffer[j] = '\0'; 

		// Comparing which tag we have, so that we can create the right type of object.
		// Then we set the contend and the description of the tag, and add it to the array.

		if (strcmp(tagBuffer, "h2") == 0)
		{
			char* descr = nullptr;
			descr = extractDesription(rowBuffer, descr); // extracting description
			if (descr == nullptr)
			{
				std::cerr << "No description!\n";
				continue;
			}
			
			char* cont = nullptr;
			cont = extractContentFromHeadParLink(rowBuffer, cont); // extracting content
			if (cont == nullptr)
			{
				std::cerr << "No content!\n";
				delete[] descr;
				continue;
			}

			HeadingTag h; // creating object
			h.SetDescription(descr);
			h.SetContent(cont);
			AddTag(h); // adding the object

			delete[] descr;
			delete[] cont;
			continue;
		}
		if (strcmp(tagBuffer, "p") == 0)
		{
			// similarly
			char* descr = nullptr;
			descr = extractDesription(rowBuffer, descr);
			if (descr == nullptr)
			{
				std::cerr << "No description!\n";
				continue;
			}

			char* cont = nullptr;
			cont = extractContentFromHeadParLink(rowBuffer, cont);
			if (cont == nullptr)
			{
				std::cerr << "No content!\n";
				delete[] descr;
				continue;
			}

			ParagraphTag p;
			p.SetDescription(descr);
			p.SetContent(cont);
			AddTag(p);

			delete[] descr;
			delete[] cont;
			continue;
		}
		if (strcmp(tagBuffer, "iframe") == 0)
		{ 
			// similarly
			char* descr = nullptr;
			descr = extractDesription(rowBuffer, descr);
			if (descr == nullptr)
			{
				std::cerr << "No description!\n";
				continue;
			}

			char* content = nullptr;
			content = extractContentFromImageTagAndVideoTag(rowBuffer, content);
			if (content == nullptr)
			{
				std::cerr << "No content!\n";
				delete[] descr;
				continue;
			}

			VideoTag v;
			v.SetDescription(descr);
			v.SetContent(content);
			AddTag(v);

			delete[] descr;
			delete[] content;
			continue;
		}
		if (strcmp(tagBuffer, "img") == 0)
		{
			// similarly
			char* descr = nullptr;
			descr = extractDesription(rowBuffer, descr);
			if (descr == nullptr)
			{
				std::cerr << "No description!\n";
				continue;
			}

			char* content = nullptr;
			content = extractContentFromImageTagAndVideoTag(rowBuffer, content);
			if (content == nullptr)
			{
				std::cerr << "No content!\n";
				delete[] descr;
				continue;
			}

			ImageTag i;
			i.SetDescription(descr);
			i.SetContent(content);
			AddTag(i);

			delete[] descr;
			delete[] content;
			continue;
		}
		if (strcmp(tagBuffer, "a") == 0)
		{
			// similarly
			char* descr = nullptr;
			descr = extractDesription(rowBuffer, descr);
			if (descr == nullptr)
			{
				std::cerr << "No description!\n";
				continue;
			}

			char* content = nullptr;
			content = extractContentFromHeadParLink(rowBuffer, content);
			if (content == nullptr)
			{
				std::cerr << "No content!\n";
				delete[] descr;
				continue;
			}

			char* link = nullptr;
			link = extractLinkFromHyperlinkTag(rowBuffer, link);
			if (link == nullptr)
			{
				std::cerr << "No link!\n";
				delete[] descr;
				delete[] content;
				continue;
			}

			HyperlinkTag l;
			l.SetDescription(descr);
			l.SetContent(content);
			l.SetSrc(link);
			AddTag(l);

			delete[] descr;
			delete[] content;
			delete[] link;
			continue;
		}
	}
	inFile.close();
}

void TagCollection::freeCollection()
{
	for (int i = 0; i < size; ++i)
	{
		delete[] tags[i];
	}
	delete[] tags;
	size = 0;
	cap = 0;
}

void TagCollection::resizeCollection()
{
	if (cap == 0)
		cap = 1;

	cap *= 2;
	Tag** newTags = new(std::nothrow) Tag*[cap]; // allocating new array of pointers
	if (!newTags)
	{
		std::cerr << "Could not allocate array for the posts!\n";
		exit(1);
	}
	
	// We don't have to delete the objects, we only have to redirect pointers
	for (int i = 0; i < size; ++i)
	{
		newTags[i] = tags[i];
	}
	delete[] tags;
	tags = newTags;
}

char* TagCollection::extractDesription(const char* line, char* extracted)
{
	if (extracted)
		return nullptr;

	extracted = new(std::nothrow) char[MAX_DESCRIPTION_LENGTH];
	if (!extracted)
	{
		std::cerr << "Not enough memory!\n";
		exit(1);
	}

	char helper[8] = { "descr=\"" };

	while (*line != '\0') // to the end of the line
	{
		if (*line == 'd') // if we find "d" we might have found descr=", but not 100% sure
		{
			int i = 0;
			while (line)
			{
				if (*line == helper[i]) // see if the substing we found is descr="
				{
					++i;
					++line;
					continue;
				}
				break; // if not => break //// or break at the end of descr="
			}

			if (i == 7) // => we have found the beginning of the description
				break;
		}
		++line;
	}

	int c = 0;
	while (*line != '\"')
	{
		extracted[c] = *line;
		++c;
		++line;
	}
	extracted[c] = '\0';

	return extracted;
}


// Extract the content from the Headings and the Paragraphs
char* TagCollection::extractContentFromHeadParLink(const char* line, char* extracted)
{
	if (extracted)
		return nullptr;

	extracted = new(std::nothrow) char[MAX_DESCRIPTION_LENGTH];
	if (!extracted)
	{
		std::cerr << "Not enough memory!\n";
		exit(1);
	}

	while (*line != '\0') // to the end of the line
	{
		if (*line == '>') // if we find ">" we have found the content
		{
			++line; // ++line so that the pointer is on the first letter of the content
			int c = 0;
			while (*line != '<') // if we reach "<", we have reached the end ot the content
			{
				extracted[c] = *line;
				++c;
				++line;
			}
			extracted[c] = '\0';
			break;
		}
		++line;
	}

	return extracted;
}

// Extract the content from the image tags and the video tags
char* TagCollection::extractContentFromImageTagAndVideoTag(const char* line, char* extracted)
{
	if (extracted)
		return nullptr;

	extracted = new(std::nothrow) char[MAX_DESCRIPTION_LENGTH];
	if (!extracted)
	{
		std::cerr << "Not enough memory!\n";
		exit(1);
	}

	char helper[6] = { "src=\"" };

	while (*line != '\0') // to the end of the line
	{
		if (*line == 's') // if we find "s" we might have found src=", but not 100% sure
		{
			int i = 0;
			while (line)
			{
				if (*line == helper[i]) // see if the substing we found is src="
				{
					++i;
					++line;
					continue;
				}
				break; // if not => break //// or break at the end of src="
			}

			if (i == 5) // => we have found the beginning of the content
				break;
		}
		++line;
	}

	int c = 0;
	while (*line != '\"')
	{
		extracted[c] = *line;
		++c;
		++line;
	}
	extracted[c] = '\0';

	return extracted;
}

// Extract the link from the hyperlink tags
char* TagCollection::extractLinkFromHyperlinkTag(const char* line, char* extracted)
{
	if (extracted)
		return nullptr;

	extracted = new(std::nothrow) char[MAX_DESCRIPTION_LENGTH];
	if (!extracted)
	{
		std::cerr << "Not enough memory!\n";
		exit(1);
	}
						
	char helper[7] = { "href=\"" };

	while (*line != '\0') // to the end of the line
	{
		if (*line == 'h') // if we find "h" we might have found href=", but not 100% sure
		{
			int i = 0;
			while (line)
			{
				if (*line == helper[i]) // see if the substing we found is href="
				{
					++i;
					++line;
					continue;
				}
				break; // if not => break //// or break at the end of src="
			}

			if (i == 6) // => we have found the beginning of the link
				break;
		}
		++line;
	}

	int c = 0;
	while (*line != '\"')
	{
		extracted[c] = *line;
		++c;
		++line;
	}
	extracted[c] = '\0';

	return extracted;
}
