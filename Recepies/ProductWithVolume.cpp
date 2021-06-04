#include "ProductWithVolume.h"

ProductWithVolume::ProductWithVolume(std::string product, double volume) {
	_product = product;
	_volume = volume;
}

std::string ProductWithVolume::getProduct() {
	return _product;
}

double ProductWithVolume::getVolume() {
	return _volume;
}

void ProductWithVolume::serizalize(std::ofstream& oFile) const {
	oFile.write((const char*)&_volume, sizeof(_volume));
	unsigned int productLength = _product.size();
	oFile.write((const char*)&productLength, sizeof(_volume));
	oFile.write((const char*)_product.data(), productLength);
}
