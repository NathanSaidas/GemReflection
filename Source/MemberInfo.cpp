#include "MemberInfo.h"

namespace Gem
{
    namespace Reflection
    {
		MemberInfo::MemberInfo(CString aClassName, CString aMemberName, const MemberFlags & aFlags, CString aMemberTypename, size_t aOffset)
			: Member(aClassName, aMemberName, aFlags),
			m_MemberTypename(aMemberTypename),
			m_Offset(aOffset)
		{

		}
		MemberInfo::MemberInfo() : Member(nullptr,nullptr,MemberFlags::Empty),
			m_MemberTypename(nullptr),
			m_Offset(0)
        {

        }

        MemberInfo::~MemberInfo()
        {

        }

        object * MemberInfo::GetOffsetPointer(object * aObject)
        {
			return (object*)(reinterpret_cast<uintptr_t>(aObject)+m_Offset);
        }
    }
    
}