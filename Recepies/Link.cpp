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

void Link::deleteProduct() {
	_deleted = true;
}
