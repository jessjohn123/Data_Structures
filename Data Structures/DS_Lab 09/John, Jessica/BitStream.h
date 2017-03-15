#pragma once
#include <vector>
#include <fstream>
using namespace std;
class BitOStream
{
private:
	char buffer = 0;
	ofstream ofile;
	int count = 7;
public:
	BitOStream(const char* filePath, const char* headerChunk = nullptr, int numberOfBytes = 0);
	~BitOStream();
	BitOStream& operator<<(vector<int> &bits);
	void close();

};

class BitIStream
{
private:
	char buffer1 = 0;
	ifstream ifile;
	int count1 = 7;
public:
	BitIStream(const char* filePath, char* headerChunk = NULL, int numberOfBytes = 0);
	~BitIStream();
	BitIStream& operator>>(int &bit);
	bool eof();
	void close();
};

BitOStream::BitOStream(const char* filePath, const char* headerChunk, int numberOfBytes)
{
	buffer = 0;
	count = 7;
	ofile.open(filePath, ios::binary);
	if (ofile.is_open())
	{
		if (headerChunk != NULL)
		{
			ofile.write(headerChunk, numberOfBytes);
		}
	}
}

BitOStream::~BitOStream()
{
	close();
}

BitOStream &BitOStream ::operator<<(vector<int> &bits)
{
	for (unsigned int i = 0; i < bits.size(); i++)
	{
		buffer = buffer | (bits[i] << count);
		count--;
		if (count == -1)
		{
			ofile.write(&buffer, 1);
			buffer = 0;
			count = 7;
		}
	}
	
	return *this;
}

void BitOStream::close()
{
	if (count != 7)
	{
		ofile.write(&buffer, 1);
	}
	
		
		ofile.close();
}


BitIStream::BitIStream(const char* filePath, char* headerChunk, int numberOfBytes)
{
	buffer1 = 0;
	count1 = 7;
	ifile.open(filePath, ios::binary);
	if (ifile.is_open())
	{
		if (headerChunk != NULL)
		{
			ifile.read(headerChunk, numberOfBytes);
		}
		ifile.read((char *)&buffer1, 1);
	}
}


BitIStream::~BitIStream()
{
	close();
}

BitIStream &BitIStream::operator>>(int &bit)
{
	
	if (buffer1 & (1 << count1))
		bit = 1;
	else
		bit = 0;
	count1--;
	if (count1 == -1)
	{
		ifile.read(&buffer1, 1);
		count1 = 7;
	}
	return *this;
}

void BitIStream::close()
{
	ifile.close();
}

bool BitIStream::eof()
{
	if (ifile.eof() && count1 == 6)
	{
		return true;
	}
	else
	{

	return false;
	}
	
}