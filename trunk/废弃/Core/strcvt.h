//�ַ���ת������ ���� Ŀǰ��Ч
#include <cstring>
#include <string>
#include <sstream>
inline ::std::string& inttostr( const int value, ::std::string& str )
{
	_itoa( value, const_cast<char*> (str.c_str()), 10 );//����ת�� ��Ϊstring������С15�ַ� ������Ҫ
	return str;
}
inline ::std::string& dwordtostr( const DWORD value, ::std::string& str )
{
	::std::ostringstream oss;
	oss << value;
	oss.str( str );
	return str;
}
