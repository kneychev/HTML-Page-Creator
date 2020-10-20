#include "PageCreator.h"

const int MAX_COMMAND_LENGTH = 7;
const int MAX_TAG_NAME_LENGTH = 8;
const int MAX_DESCRIPTION_LENGTH = 512;
const int MAX_CONTENT_LENGTH = 512;
const int MAX_LINK_LENGTH = 512;
const int MAX_FILE_NAME_LENGTH = 128;

PageCreator::PageCreator()
{
}

PageCreator::~PageCreator()
{
}

void PageCreator::Run()
{
	bool addedTag = false;
	while (true)
	{
		char command[MAX_COMMAND_LENGTH];
		std::cin >> command;

		if (strcmp(command, "add") == 0)
		{
			char tagType[MAX_TAG_NAME_LENGTH];
			std::cin >> tagType;
			if (strcmp(tagType, "heading") == 0)
			{
				HeadingTag h;
				char descr[MAX_DESCRIPTION_LENGTH];
				char content[MAX_CONTENT_LENGTH];
				
				std::cin.ignore(100, ' '); // ignoring spaces
				std::cin.getline(descr, MAX_DESCRIPTION_LENGTH, '>'); // reding 'til we meet >
				processDescription(descr); // removing < from descr

				std::cin.ignore(100, ' '); // ignoring spaces
				std::cin.getline(content, MAX_CONTENT_LENGTH);
				
				h.SetDescription(descr);
				h.SetContent(content);
				tags.AddTag(h);
				addedTag = true;
			}
			else if (strcmp(tagType, "text") == 0) // similarly to the first "if"
			{
				ParagraphTag p;
				char descr[MAX_DESCRIPTION_LENGTH];
				char content[MAX_CONTENT_LENGTH];

				std::cin.ignore(100, ' ');
				std::cin.getline(descr, MAX_DESCRIPTION_LENGTH, '>');
				processDescription(descr);

				std::cin.ignore(100, ' ');
				std::cin.getline(content, MAX_CONTENT_LENGTH);

				p.SetDescription(descr);
				p.SetContent(content);
				tags.AddTag(p);
				addedTag = true;
			}
			else if (strcmp(tagType, "video") == 0) // similarly to the first "if"
			{
				VideoTag v;
				char descr[MAX_DESCRIPTION_LENGTH];
				char content[MAX_CONTENT_LENGTH];

				std::cin.ignore(100, ' ');
				std::cin.getline(descr, MAX_DESCRIPTION_LENGTH, '>');
				processDescription(descr);

				std::cin.ignore(100, ' ');
				std::cin.getline(content, MAX_CONTENT_LENGTH);

				v.SetDescription(descr);
				v.SetContent(content);
				tags.AddTag(v);
				addedTag = true;
			}
			else if (strcmp(tagType, "image") == 0) // similarly to the first "if"
			{
				ImageTag i;
				char descr[MAX_DESCRIPTION_LENGTH];
				char content[MAX_CONTENT_LENGTH];
				
				std::cin.ignore(100, ' ');
				std::cin.getline(descr, MAX_DESCRIPTION_LENGTH, '>');
				processDescription(descr);

				std::cin.ignore(100, ' ');
				std::cin.getline(content, MAX_CONTENT_LENGTH);

				i.SetDescription(descr);
				i.SetContent(content);
				tags.AddTag(i);
				addedTag = true;
			}
			else if (strcmp(tagType, "link") == 0) // similarly to the first "if"
			{
				HyperlinkTag l;
				char descr[MAX_DESCRIPTION_LENGTH];
				char link[MAX_LINK_LENGTH];
				char content[MAX_CONTENT_LENGTH];

				std::cin.ignore(100, ' ');
				std::cin.getline(descr, MAX_DESCRIPTION_LENGTH, '>');
				processDescription(descr);

				std::cin.ignore(100, ' ');
				std::cin.getline(link, MAX_LINK_LENGTH);

				std::cin.ignore(100, ' ');
				std::cin.getline(content, MAX_CONTENT_LENGTH);

				l.SetDescription(descr);
				l.SetSrc(link);
				l.SetContent(content);
				tags.AddTag(l);
				addedTag = true;
			}
		}
		else if (strcmp(command, "remove") == 0)
		{
			char descr[MAX_DESCRIPTION_LENGTH];
			std::cin.ignore(100, ' ');
			std::cin.getline(descr, MAX_DESCRIPTION_LENGTH);

			tags.RemoveTag(descr);
		}
		else if (strcmp(command, "print") == 0)
		{
			tags.PrintCollection();
		}
		else if (strcmp(command, "moveTo") == 0)
		{
			int to;
			char descr[MAX_DESCRIPTION_LENGTH];
			std::cin >> to;
			std::cin.ignore(100, ' ');
			std::cin.getline(descr, MAX_DESCRIPTION_LENGTH);

			tags.Move(to, descr);
		}
		else if (strcmp(command, "load") == 0)
		{
			if (addedTag == true)
			{
				std::cout << "A file is being created, so you can't load another one!\n";
				continue;
			}

			char fileName[MAX_FILE_NAME_LENGTH];
			std::cin.ignore(100, ' ');
			std::cin.getline(fileName , MAX_FILE_NAME_LENGTH);

			tags.ReadCollectionFromFile(fileName);
		}
		else if (strcmp(command, "save") == 0)
		{
			char fileName[MAX_FILE_NAME_LENGTH];
			std::cin.ignore(100, ' ');
			std::cin.getline(fileName, MAX_FILE_NAME_LENGTH);

			tags.SaveCollectionToFile(fileName);
		}
		else if (strcmp(command, "exit") == 0)
		{
			break;
		}
		else
		{
			std::cout << "Unknown coomand!\n";
			std::cin.ignore(10000, '\n'); // ignoring everythig until we reach the new line
		}
	}
}

void PageCreator::processDescription(char* descr)
{
	for (unsigned int i = 0; i < strlen(descr) + 1; ++i)
	{
		descr[i] = descr[i + 1]; // overriding symbols until the end of descr
		if (i == strlen(descr))
		{
			descr[i] = '\0'; // setting the new end of descr
			break;
		}
	}
}
