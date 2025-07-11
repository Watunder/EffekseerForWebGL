#pragma once

#include <Effekseer.h>

#include <algorithm>
#include <emscripten.h>
#include <math.h>
#include <stdlib.h>

namespace EffekseerForWebGL
{
class CustomFileReader : public Effekseer::FileReader
{
	uint8_t* fileData;
	size_t fileSize;
	int currentPosition;

public:
	CustomFileReader(uint8_t* fileData, size_t fileSize) : fileData(fileData), fileSize(fileSize), currentPosition(0) {}
	~CustomFileReader() { free(fileData); }
	size_t Read(void* buffer, size_t size)
	{
		if (currentPosition + size > fileSize)
		{
			size = fileSize - currentPosition;
		}
		memcpy(buffer, fileData + currentPosition, size);
		currentPosition += size;
		return size;
	}
	void Seek(int position) { currentPosition = position; }
	int GetPosition() const override { return currentPosition; }
	size_t GetLength() const override { return fileSize; }
};

class CustomFileInterface : public Effekseer::FileInterface
{
public:
	Effekseer::FileReaderRef OpenRead(const EFK_CHAR* path, bool isRequired)
	{
		// Request to load file
		int loaded = EM_ASM_INT({ return Module._loadEffectCustomFile(UTF16ToString($0), $1) != null; }, path, isRequired);
		if (!loaded)
		{
			return nullptr;
		}

		uint8_t* fileData = nullptr;
		int fileSize = 0;

		// Copy data from arraybuffer
		EM_ASM_INT(
			{
				var buffer = Module._loadEffectCustomFile(UTF16ToString($0), $3);
				var memptr = _malloc(buffer.byteLength);
				HEAP8.set(new Uint8Array(buffer), memptr);
				setValue($1, memptr, "i32");
				setValue($2, buffer.byteLength, "i32");
			},
			path,
			&fileData,
			&fileSize,
			isRequired);

		if (fileData == nullptr)
		{
			return nullptr;
		}

		return Effekseer::MakeRefPtr<CustomFileReader>(fileData, fileSize);
	}

	Effekseer::FileReaderRef OpenRead(const EFK_CHAR* path) override { return OpenRead(path, true); }

	Effekseer::FileReaderRef TryOpenRead(const EFK_CHAR* path) override { return OpenRead(path, false); }

	Effekseer::FileWriterRef OpenWrite(const EFK_CHAR* path) override { return nullptr; }
};
} // namespace EffekseerForWebGL