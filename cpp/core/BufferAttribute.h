#ifndef __THREE_BUFFER_ATTRIBUTE__
#define __THREE_BUFFER_ATTRIBUTE__

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
};

#endif
