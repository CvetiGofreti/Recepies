#include "Link.h"
#include <fstream>
Link::Link(std::string link) {
	_link = link;
	_deleted = false;
}

void Link::serizalize(std::ofstream& oFile) const {
	unsigned int linkLength = _link.size();
	oFile.write((const char*)&linkLength, sizeof(linkLength));
	oFile.write((const char*)_link.data(), linkLength);
}

bool Link::isDeleted() const {
	return _deleted;
}

void Link::deleteLink() {
	_deleted = true;
}

void Link::print() const{
	std::cout << _link << std::endl;
}
