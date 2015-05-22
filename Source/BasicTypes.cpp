#include "BasicTypes.h"

namespace Gem
{
	RDEFINE_CLASS(object,)
	RDEFINE_CLASS(Object,object)
	RDEFINE_PRIVATE_MEMBER(Object,m_Name,std::string)

	object::object()
	{

	}
	object::~object()
	{

	}
	RDEFINE_PUBLIC_FUNCTION(object, ToString, std::string)
	std::string object::ToString()
	{
        return GetType().GetName();
	}

	Object::Object() : object()
	{

	}
	Object::~Object()
	{

	}

	RDEFINE_PUBLIC_FUNCTION(Object,ToString,std::string)
	std::string Object::ToString()
	{
        return GetType().GetName();
	}

	RDEFINE_PUBLIC_FUNCTION(Object,GetName,std::string)
	std::string Object::GetName()
	{
		return m_Name;
	}

	RDEFINE_PUBLIC_FUNCTION(Object,SetName,void, const std::string&)
	void Object::SetName(const std::string & aName)
	{
		m_Name = aName;
	}

	void Object::SetName(const char * aName)
	{
		m_Name = aName;
	}


}