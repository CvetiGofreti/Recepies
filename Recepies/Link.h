#pragma once
#include <string>
#include <iostream>
class Link
{
public:
	Link(std::string link);
	void serizalize(std::ofstream& oFile) const;
	bool isDeleted() const;
	void deleteLink();
	void print() const;
private:
	std::string _link;
	bool _deleted;
};
