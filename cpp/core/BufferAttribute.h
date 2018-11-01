#ifndef __THREE_BUFFER_ATTRIBUTE__
#define __THREE_BUFFER_ATTRIBUTE__

// @TODO: Use template

class BufferAttribute {
public:
	void* array;
	enum type { Float32, Uint16, Uint8 };
	type dataType;
	int itemSize;
	int count;
	int bytePerElement;
	int version;
	bool needsUpdate;

	BufferAttribute(
		void *_array,
		type _dataType,
		int _dataLength,
		int _itemSize
	);

	float getXAsFloat(
		int index
	);

	float getYAsFloat(
		int index
	);

	float getZAsFloat(
		int index
	);
};

#endif
