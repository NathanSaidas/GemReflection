#ifndef GAME_ENGINE_METHOD_INFO_H
#define GAME_ENGINE_METHOD_INFO_H

#pragma region CHANGE LOG
/// -- January, 30, 2015 - Nathan Hanlan - Added MethodInfo file and MethodInfo / MethodActionInfo classes 
/// -- May,		12, 2015 - Nathan Hanlan - Refactored MethodInfo to use the new Method class with variadic templates. Works as before.
#pragma region

#include "GemAPI.h"
#include "Method.h"
#include "Member.h"

namespace Gem
{
    namespace Reflection
    {

		template<typename CLASS, typename RETURN, typename ... ARGS>
		class MethodInfo : public Member
		{
		public:
			MethodInfo() : Member(nullptr, nullptr, MemberFlags::Empty)
			{
				m_Method = nullptr;
			}
			MethodInfo(Method<CLASS,RETURN,ARGS...> aFunction, CString aClassTypename, CString aMemberName, const MemberFlags & aFlags)
				: Member(aClassTypename,aMemberName,aFlags)
			{
				m_Method = aFunction;
			}
			Method<CLASS, RETURN, ARGS...> GetMethod()
			{
				return m_Method;
			}
		private:
			Method<CLASS, RETURN, ARGS...> m_Method;
		};
    }
    
}

#endif