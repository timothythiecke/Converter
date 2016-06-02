#pragma once

#include "include.h"

/**
@brief Interface for disabling copy constructor and assignment operator
**/
class NoCopy
{
	DECLARE_HUNGARIAN(NoCopy)
public:
	NoCopy() { }
private:
	NoCopy(rcNoCopy inRef)				= delete;
	rNoCopy operator=(rcNoCopy inRef)	= delete;
};
