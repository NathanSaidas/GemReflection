#ifndef GAME_ENGINE_MEMBER_FUNC_H
#define GAME_ENGINE_MEMBER_FUNC_H

#pragma region CHANGE LOG
/// -- January, 29, 2015 - Nathan Hanlan - Added Func classes
/// -- May,		12, 2015 - Nathan Hanlan - Refactored Method class to use variadic template parameter packing. Works as before. 
/// -- May,     12, 2015 - Nathan Hanlan - Removed MethodAction class. Use method instead.
#pragma endregion

//#include "BasicTypes.h"

namespace Gem
{
    ///Func Class Description:
    ///(May,     12, 2015)
    ///
    /// The Method class encapsulates a method callback. (member function pointer)
	/// It can be used to invoke given a class instance to invoke from.
	/// Note: GEM_API is not used on the Method Class. Instead each type being exported/imported using the Method class
	/// should use explicit import/export. See GemAPI.h for example on std::string and std::vector.


    ///Action Class Description:
    ///(May,     12, 2015)
    ///
    /// MethodAction class has been removed use Method instead.
	///

	template<typename CLASS,typename RETURN, typename ... ARGS>
	class Method //: public object
	{
	public:
		typedef RETURN(CLASS::*Delegate)(ARGS...);
		typedef RETURN(CLASS::*ConstDelegate)(ARGS...) const;
		Method()
		{
			m_Function = nullptr;
			m_ConstFunction = nullptr;
		}
		Method(Delegate aFunction)
		{
			m_Function = aFunction;
			m_ConstFunction = nullptr;
		}
		Method(ConstDelegate aFunction)
		{
			m_ConstFunction = aFunction;
			m_Function = nullptr;
		}
		~Method()
		{

		}

		Delegate operator=(Delegate aFunction)
		{
			m_ConstFunction = nullptr;
			return m_Function = aFunction;
		}

		ConstDelegate operator=(ConstDelegate aFunction)
		{
			m_Function = nullptr;
			return m_ConstFunction = aFunction;
		}

		RETURN operator()(CLASS& aInstance, ARGS ... args)
		{
			if (aInstance != nullptr)
			{
				if (m_Function != nullptr)
				{
					return (aInstance.*m_Function)(args...);
				}
				else if (m_ConstFunction != nullptr)
				{
					return (aInstance.*m_ConstFunction)(args...);
				}
			}
			return RETURN();
		}

		RETURN operator()(CLASS* aInstance, ARGS ... args)
		{
			if (aInstance != nullptr)
			{
				if (m_Function != nullptr)
				{
					return (aInstance->*m_Function)(args...);
				}
				else if (m_ConstFunction != nullptr)
				{
					return (aInstance->*m_ConstFunction)(args...);
				}
			}
			return RETURN();
		}

		RETURN Invoke(CLASS& aInstance, ARGS ... args)
		{
			if (aInstance != nullptr)
			{
				if (m_Function != nullptr)
				{
					return (aInstance.*m_Function)(args...);
				}
				else if (m_ConstFunction != nullptr)
				{
					return (aInstance.*m_ConstFunction)(args...);
				}
			}
			return RETURN();
		}
		RETURN Invoke(CLASS* aInstance, ARGS ... args)
		{
			if (aInstance != nullptr)
			{
				if (m_Function != nullptr)
				{
					return (aInstance->*m_Function)(args...);
				}
				else if (m_ConstFunction != nullptr)
				{
					return (aInstance->*m_ConstFunction)(args...);
				}
			}
			
			return RETURN();
		}

	private:
		Delegate m_Function;
		ConstDelegate m_ConstFunction;
	};
}

#endif