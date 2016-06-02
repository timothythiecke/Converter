#include "Converter.h"


/**
Default ctor
**/
Converter::Converter()
{
	mBlockSize	= S_INIT_BLOCK_SIZE;

	ppChar p_p_head = &mBlockHead;
	ppChar p_p_ptr = &mBlockPtr;
	AllocInternal(p_p_head, p_p_ptr, S_INIT_BLOCK_SIZE);
}


/**
Dtor
**/
Converter::~Converter()
{
	// Blockhead will always point to the first element
	delete[] mBlockHead;
	
	mBlockHead = nullptr;
	mBlockPtr = nullptr;
}



/**
Deletes old info and allocates new block to start all over again
Should it deallocate? seems a little wasteful
otherwise, add a clear function
**/
void Converter::Purge()
{
	delete[] mBlockHead;

	ppChar p_p_head = &mBlockHead;
	ppChar p_p_ptr = &mBlockPtr;
	AllocInternal(p_p_head, p_p_ptr, mBlockSize);
}



/**
Allocates a new block of memory
**/
pVoid Converter::Alloc(cInt iBlockSize)
{
	return new char[iBlockSize];
}


/**
Indirection
**/
pVoid Converter::AllocInternal(ppChar inHead, ppChar inPtr, cInt inBlockSize)
{
	*inHead = static_cast<pChar>(Alloc(inBlockSize));
	*inPtr = *inHead;

	return *inHead;
}



/**
Frees previous memory block
**/
void Converter::FreeBlock(ppChar ppOldBlock)
{
	delete[] *ppOldBlock;

	*ppOldBlock = nullptr;
	ppOldBlock = nullptr;
}



/**
Copies data block into other data block
Templated interface?
**/
void Converter::Copy(pChar pNew, pChar pOld, cInt iLen)
{
	for (int i = 0; i < iLen; ++i)
		pNew[i] = pOld[i];
}



/**
Resize the current block
We first check if there's still a possibility of allocating more memory
Create back up values
Allocate a block based on the previous block size * static const factor in header
Copy old values from 
**/
bool Converter::Resize()
{
	// Resize failed if reallocation happened to often
	if (mBlockSize >= S_MAX_BLOCK_SIZE)
		return false;

	cInt original_offset = mBlockPtr - mBlockHead;
	cInt new_block_size = mBlockSize * S_BLOCK_SIZE_FACTOR;

	pChar p_old_block = mBlockHead;

	// Allocate
	ppChar p_p_head = &mBlockHead;
	ppChar p_p_ptr	= &mBlockPtr;
	AllocInternal(p_p_head, p_p_ptr, new_block_size);
	NULLIFY(p_p_head)
	NULLIFY(p_p_ptr)

	// Copy old values
	Copy(mBlockPtr, p_old_block, original_offset);

	// Free memory
	ppChar p_p_temp_ptr = &p_old_block;
	FreeBlock(p_p_temp_ptr);
	
	// Apply offset and new block size
	mBlockPtr += original_offset;
	mBlockSize = new_block_size;

	return true;
}



/**
Write a character to the memory block
**/
bool Converter::Write(cChar inChar)
{
	// Always check before writing if we can reallocate memory
	bool should_resize = CheckSize();
	bool has_resized = false;

	if (should_resize)
	{
		if (Resize())
			has_resized = true;
	}

	// Write to the array
	if (!should_resize || has_resized)
	{
		*mBlockPtr = inChar;
		++mBlockPtr;
		return true;
	}

	return false;
}



/**
Control if we are too close to the end
Check necessary to see if we need to reallocate
**/
bool Converter::CheckSize()
{
	return (mBlockPtr - mBlockHead) >= (mBlockSize - 1); // Note: I think I might implement a write block call eventually, so this magic value will disappear most likely
}



/**
Reserves a chunk of memory, this allows us to avoid memory allocations
**/
void Converter::Reserve(cInt inLength)
{
	// No need to allocate if input is smaller than expected
	if (inLength <= mBlockSize)
		return;

	// We would like to allocate an amount which is a power of 2
	// Opt out before we reach 1 as i % 1 will always amount to 0, allowing anyone to allocate freely
	bool is_power_of_two = false;
	for (int i = S_MAX_BLOCK_SIZE; i > 1; i /= S_BLOCK_SIZE_FACTOR)
	{
		if (inLength % i == 0) 
		{
			is_power_of_two = true;
			break;
		}
	}

	if (!is_power_of_two)
		return;

	Alloc(inLength);
}



/**
Removes element at specified index
Moves elements after to the left
**/
void Converter::Remove(cInt inIndex)
{
	if (inIndex < 0 || inIndex >= mBlockSize)
		return;

	pChar temp = &mBlockHead[inIndex];
	*temp = '\0';

	for (int i = ((temp - mBlockHead) + 1); i < mBlockSize; ++i)
	{
		temp[i - 1] = temp[i];
	}
}



/**
Removes elements from range inIndex -> inIndex + inLength
**/
void Converter::Remove(cInt inIndex, cInt inLength)
{

}