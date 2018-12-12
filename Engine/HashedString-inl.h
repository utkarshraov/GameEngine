#include <assert.h>
#include <string.h>

namespace Engine
{
inline HashedString::HashedString( ) :
	m_Hash( Hash( "" ) )
{
}

inline HashedString::HashedString( const char * string ) :
	m_Hash( Hash( string ) )
#ifdef DEBUG_KEEP_STRING
	, m_pString( strdup( string ) )
#endif
{
}

inline HashedString::HashedString( const HashedString & other ) :
m_Hash( other.m_Hash )
#ifdef DEBUG_KEEP_STRING
	, m_pString( strdup( other.m_pString ) )
#endif
{
}

inline HashedString::~HashedString()
{
#ifdef DEBUG_KEEP_STRING
	if( m_pString )
		free( m_pString )
#endif
	
}

inline HashedString & HashedString::operator=( const HashedString & other )
{
	m_Hash = other.m_Hash;

#ifdef DEBUG_KEEP_STRING
	if( m_pString )
		free( m_pString )
	
	m_pString = other.m_pString;
#endif

	return *this;
}

inline unsigned int HashedString::Get( void ) const
{
	return m_Hash;
}

inline bool HashedString::operator==( const HashedString & other ) const
{
	return m_Hash == other.m_Hash;
}

inline bool HashedString::operator<( const HashedString & other ) const
{
	return m_Hash < other.m_Hash;
}
} // namespace Engine
