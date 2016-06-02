#include "include.h"

#include "StringToBinaryConverter.h"

int main()
{
	// Test cases
	TC0;

	// String to binary converter
	StringBinaryConverter to_binary_converter;

	to_binary_converter.Reserve(1024);

	String test_string("HelloWorldStringConverter");

	FOR(100)
		to_binary_converter.Register(test_string);
	
	FOR(200)
		to_binary_converter.Remove(0);
}