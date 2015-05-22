#ifndef GAME_ENGINE_FUNC_H
#define GAME_ENGINE_FUNC_H

#pragma region CHANGE LOG
/// -- January, 29, 2015 - Nathan Hanlan - Added Func classes
/// -- May,     12, 2015 - Nathan Hanlan - Refactored Func class to use variadic template parameter packing. Works as before.
/// -- May,     12, 2015 - Nathan Hanlan - Removed Action class use Func instead.
#pragma endregion

//#include "BasicTypes.h"

namespace Gem
{
    ///Func Class Description:
    ///(May,     12, 2015)
    ///
    /// The Func class encapsulates a function callback, (function pointer). This can be any C-style function or static class function.
	/// This func class can invoke the callback just as if it were calling the function normally.
	/// Note: GEM_API is not used on the Func Class. Instead each type being exported/imported using the Method class
	/// should use explicit import/export. See GemAPI.h for example on std::string and std::vector.

    ///Action Class Description:
    ///(May,     12, 2015)
    ///
    /// Action classes have been removed, used Func instead.

	template<typename RETURN, typename ... ARGS>
	class Func //: public object
	{
	public:
		typedef RETURN(*Delegate)(ARGS...);
		Func()
		{
			m_Function = nullptr;
		}
		Func(Delegate aFunction)
		{
			m_Function = aFunction;
		}
		~Func()
		{
	
		}

		inline bool operator==(Func aFunc)
		{
			return m_Function == aFunc.m_Function;
		}

		inline bool operator !=(Func aFunc)
		{
			return m_Function != aFunc.m_Function;
		}
	
		inline Delegate operator=(Delegate aFunction)
		{
			return m_Function = aFunction;
		}
	
		inline RETURN operator()(ARGS ... args) const
		{
			if (m_Function != nullptr)
			{
				return m_Function(args...);
			}
			return RETURN();
		}
	
		inline RETURN Invoke(ARGS ... args) const
		{
			if (m_Function != nullptr)
			{
				return m_Function(args...);
			}
			return RETURN();
		}
	
	private:
		Delegate m_Function;
	};

}

#endif