#pragma once

#include "include.h"

#include "Converter.h"

class StringBinaryConverter : public Converter
{
public:
			StringBinaryConverter();
			~StringBinaryConverter();

	void	Register(rcString inString);
	void	Register(pcChar inString);

	pcChar	Convert();

private:
};