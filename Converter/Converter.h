#pragma once

#include "include.h"

class Converter : public NoCopy
{
public:
					Converter();
	virtual			~Converter();

	virtual void	Register(rcString inString)	= 0;
	virtual void	Register(pcChar inString)	= 0;

	virtual pcChar	Convert()					= 0;
	virtual void	Purge();

	void			Reserve(cInt inLength);
	void			Remove(cInt inIndex);
	void			Remove(cInt inIndex, cInt inLength);

protected:
	pVoid			Alloc(cInt iBlockSize);
	pVoid			AllocInternal(ppChar inHead, ppChar inPtr, cInt inBlockSize);
	void			Copy(pChar pNew, pChar pOld, cInt len);
	void			FreeBlock(ppChar ppOldBlock);
	
	virtual bool	Resize();
	virtual bool	Write(cChar inChar);
	virtual bool	CheckSize();

	static const int S_INIT_BLOCK_SIZE = 2; ///< For testing purposes, we can set the value very low to trigger many allocations
	static const int S_BLOCK_SIZE_FACTOR = 2;
	static const int S_MAX_BLOCK_SIZE = 1024;
	
	int	mBlockSize		= -1;
	pChar mBlockPtr		= nullptr;
	pChar mBlockHead	= nullptr;	///< Slave pointer, used for offset calculations but doesnt do anything

private:
};
