#include "BufferAttribute.h"

BufferAttribute::BufferAttribute(
	void *_array,
	type _dataType,
	int _dataLength,
	int _itemSize
): array(_array), dataType(_dataType), itemSize(_itemSize),
	needsUpdate(false), version(0) {
	if(_dataType == Float32) {
		this->bytePerElement = 4;
	} else if(_dataType == Uint16) {
		this->bytePerElement = 2;
	} else {
		this->bytePerElement = 1;
	}
	this->count = _dataLength / this->itemSize / this->bytePerElement;
}
