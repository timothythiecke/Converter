#pragma once

// Includes
#include <string>

// Standard typedefs
typedef int			Int;
typedef bool		Bool;
typedef char		Char;
typedef float		Float;
typedef std::string String;
typedef void		Void;

#define DECLARE_CONST(type)				\
	typedef const	type	c##type;	\
;

#define DECLARE_POINTER(type)			\
	typedef			type*	p##type;	\
	typedef			type**	pp##type;	\
	typedef const	type*	pc##type;	\
;

#define DECLARE_REFERENCE(type)			\
	typedef			type&	r##type;	\
	typedef const	type&	rc##type;	\
;

#define DECLARE_HUNGARIAN(type)			\
	DECLARE_CONST(type)					\
	DECLARE_POINTER(type)				\
	DECLARE_REFERENCE(type)				\
;

#define	DECLARE_HUNGARIAN_NO_REF(type)	\
	DECLARE_CONST(type)					\
	DECLARE_POINTER(type)				\
;

DECLARE_HUNGARIAN(Int)
DECLARE_HUNGARIAN(Bool)
DECLARE_HUNGARIAN(Char)
DECLARE_HUNGARIAN(Float)
DECLARE_HUNGARIAN(String)

DECLARE_HUNGARIAN_NO_REF(Void)

#define FOR(amount)						\
	for (int i = 0; i < amount; ++i)

#define NULLIFY(ptr)					\
	ptr = nullptr;
