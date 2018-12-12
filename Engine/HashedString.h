#ifndef __HASHED_STRING_H
#define __HASHED_STRING_H

namespace Engine
{
	
class HashedString
{
public:
	HashedString();
	~HashedString();
	
	HashedString( const char * string );
	HashedString( const HashedString & other );
	HashedString & operator=( const HashedString & other );

	unsigned int Get() const;

	bool operator==( const HashedString & other ) const;
	bool operator<( const HashedString & other ) const;

	static unsigned int Hash( const char * string );
	static unsigned int Hash( const void * i_bytes, size_t i_count );
private:
	unsigned int 	m_Hash;

#ifdef DEBUG_KEEP_STRING
	const char * 	m_pString;
#endif
} ;

} // namespace Engine

#include "HashedString-inl.h"

#endif // __HASHED_STRING_H