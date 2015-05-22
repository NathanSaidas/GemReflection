#include "Type.h"
#include "Reflection.h"

namespace Gem
{
    Array<Type> Type::GetInterfaces() const
    {
        Array<Type> types(m_Interfaces.size());
        
        int index = 0;
        for (std::vector<std::string>::const_iterator it = m_Interfaces.begin(); it != m_Interfaces.end(); it++)
        {
            Type type = Reflection::Runtime::TypeOf(*it);
            types[index] = type;
            index++;
        }
        return types;
    }

    Type Type::GetInterface(const std::string & aName) const
    {
        for (std::vector<std::string>::const_iterator it = m_Interfaces.begin(); it != m_Interfaces.end(); it++)
        {
            if ((*it) == aName)
            {
                return Reflection::Runtime::TypeOf(*it);
            }
        }
        return Type();
    }

    Array<Reflection::MemberInfo> Type::GetMembers() const
    {
        Array<Reflection::MemberInfo> members;
        Array<Reflection::MemberInfo>::Copy(m_Members, members);
		Array<Reflection::MemberInfo>::CopyAppend(m_InheritedMembers, members);
        return members;
    }

	
    Reflection::MemberInfo Type::GetMember(const std::string & aName) const
    {
        for (std::vector<Reflection::MemberInfo>::const_iterator it = m_Members.begin(); it != m_Members.end(); it++)
        {
            if (aName == (*it).GetMemberName())
            {
                return (*it);
            }
        }
		for (std::vector<Reflection::MemberInfo>::const_iterator it = m_InheritedMembers.begin(); it != m_InheritedMembers.end(); it++)
		{
			if (aName == (*it).GetMemberName())
			{
				return (*it);
			}
		}

        return Reflection::MemberInfo();
    }

	Array<Reflection::Member*> Type::GetMethods() const
	{
		Array<Reflection::Member*> methods;
		Array<Reflection::Member*>::Copy(m_Methods, methods);
		Array<Reflection::Member*>::CopyAppend(m_InheritedMethods, methods);
		return methods;
	}

	Reflection::Member * Type::GetMethodInfo(const std::string & aName) const
	{
		for (std::vector<Reflection::Member*>::const_iterator it = m_Methods.begin(); it != m_Methods.end(); it++)
		{
			if (aName == (*it)->GetMemberName())
			{
				return *it;
			}
		}
		for (std::vector<Reflection::Member*>::const_iterator it = m_InheritedMethods.begin(); it != m_InheritedMethods.end(); it++)
		{
			if (aName == (*it)->GetMemberName())
			{
				return *it;
			}
		}
		return nullptr;
	}
}