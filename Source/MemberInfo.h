#ifndef GAME_ENGINE_MEMBER_INFO_H
#define GAME_ENGINE_MEMBER_INFO_H

//============================================================
// Date:			May,	11,		2015
// Description:		Contains the MemberInfo class.
//============================================================

#pragma region CHANGE LOG
// -- Nathan Hanlan, Added Member as base class. Refactored to use CString typedef as opposed to char *.
// -- Nathan Hanlan, Inlined some members to make the class more clear.
#pragma endregion

#include <string>
#include "Member.h"

namespace Gem
{
    class object;

    namespace Reflection
    {
		/**
		* This class provides information on a member of a class.
		*/
        class GEM_API MemberInfo : public Member
        {
        public:
			MemberInfo(CString aClassName, CString aMemberName, const MemberFlags & aFlags, CString aMemberTypename, size_t aOffset);
            MemberInfo();
            ~MemberInfo();

			/** 
			* @return Returns the name of the member type.
			*/
			inline CString GetMemberTypename() const
			{
				return m_MemberTypename;
			}
			/**
			* @return Returns the offset of the member in memory.
			*/
			inline size_t GetOffset() const
			{
				return m_Offset;
			}

			inline bool operator==(const MemberInfo & aInfo) const
			{
				return strcmp(GetMemberName(), aInfo.GetMemberName()) == 0;
			}

			/**
			* @param aObject The object to use for the adjustment
			* @return Returns a pointer of where this member would be located from the specified object.
			*/
            object * GetOffsetPointer(object * aObject);

        private:
			/** The name of the member type*/
            CString m_MemberTypename;
			/** The offset of the member in memory from the class*/
            size_t m_Offset;
        };
    }
}

#endif