#ifndef GEM_REFLECTION_MEMBER_H
#define GEM_REFLECTION_MEMBER_H


#include "GemAPI.h"
#include "ValueTypes.h"
#include "MemberFlags.h"

namespace Gem
{
	namespace Reflection
	{
		/**
		* The base class for all member types, (Variables / Functions)
		*/
		class GEM_API Member
		{
		public:
			Member(CString aClassName, CString aMemberName) : m_ClassName(aClassName), m_MemberName(aMemberName) {}
			Member(CString aClassName, CString aMemberName, const MemberFlags & aFlags) : m_ClassName(aClassName),
				m_MemberName(aMemberName), m_MemberFlags(aFlags) {}
			Member() :m_ClassName(nullptr), m_MemberName(nullptr), m_MemberFlags(MemberFlags::Empty) {}
			virtual ~Member() {}

			inline CString GetClassName() const
			{
				return m_ClassName;
			}

			inline CString GetMemberName() const
			{
				return m_MemberName;
			}

			inline MemberFlags GetMemberFlags() const
			{
				return m_MemberFlags;
			}

		private:
			/** The name of the class the member belongs to*/
			CString m_ClassName;
			/** The name of the member */
			CString m_MemberName;
			/** The flags of the member */
			MemberFlags m_MemberFlags;
		};
	}
}

#endif