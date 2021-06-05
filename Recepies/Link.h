#pragma once
#include <string>
class Link
{
public:
	Link(std::string link);
	void serizalize(std::ofstream& oFile) const;
	bool isDeleted() const;
	void deleteProduct();
private:
	std::string _link;
	bool _deleted;
};
