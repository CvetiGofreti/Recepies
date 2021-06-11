#include "ProductWithVolume.h"
#include <iomanip>

ProductWithVolume::ProductWithVolume(std::string product, double volume, std::string unit) {
	_product = product;
	_volume = volume;
	_unit = unit;
	_deleted = false;
}

std::string ProductWithVolume::getProduct() {
	return _product;
}

double ProductWithVolume::getVolume() {
	return _volume;
}

std::string ProductWithVolume::getUnit() {
	return _unit;
}

void ProductWithVolume::serizalize(std::ofstream& oFile) const {
	oFile.write((const char*)&_volume, sizeof(_volume));

	unsigned int productLength = _product.size();
	oFile.write((const char*)&productLength, sizeof(productLength));
	oFile.write((const char*)_product.data(), productLength);

	unsigned int unitLength = _unit.size();
	oFile.write((const char*)&unitLength, sizeof(unitLength));
	oFile.write((const char*)_unit.data(), unitLength);
}

bool ProductWithVolume::isDeleted() const {
	return _deleted;
}

void ProductWithVolume::deleteProduct() {
	_deleted = true;
}

void ProductWithVolume::printInfo() const{
	std::cout << _product << ": " << std::setprecision(2) << std::fixed << _volume << " " << _unit << std::endl;
}
