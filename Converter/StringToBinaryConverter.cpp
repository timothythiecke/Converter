#include "StringToBinaryConverter.h"



StringBinaryConverter::StringBinaryConverter()	{ }
StringBinaryConverter::~StringBinaryConverter() { }

/**
@brief Register an std::string
**/
void StringBinaryConverter::Register(rcString inString)
{
	for (cChar c : inString)
	{
		if (!Write(c))
			break;
	}
}



/**
@brief Register an array of chars
**/
void StringBinaryConverter::Register(pcChar inString)
{

}


/**
@brief Returns a pointer to our allocated block
**/
pcChar StringBinaryConverter::Convert()
{
	return mBlockHead;
}

