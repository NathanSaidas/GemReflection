#ifndef GAME_ENGINE_FUNCTION_ATTRIBUTE_H
#define GAME_ENGINE_FUNCTION_ATTRIBUTE_H

//============================================================
// Date:			May,	11,		2015
// Description:		Contains the FuncAttribute class.
//============================================================

#pragma region CHANGE LOG
/// -- January, 29, 2015 - Nathan Hanlan - Added FunctionAttribute class/file
/// -- April, 1, 2015 - Nathan Hanlan - Added Doxygen Style Comments.
/// -- April, 1, 2015 - Nathan Hanlan - Defined a type trait for FunctionAttribute.
#pragma endregion

//Using Attribute to inherit from.
#include "Attribute.h"
//Using Func to define Function objects.
#include "Func.h"
#include "GemAPI.h"

#include "Member.h"

template class GEM_API Gem::Func<void*, void*>;

namespace Gem
{
    namespace Reflection
    {
		/**
		* Defines the attribute for Func values.
		* Func has a void * return type and void * argument
		*/
        class GEM_API FunctionAttribute : public Attribute
        {
        public:
			/**
			* The constructor for FunctionAttribute, Requires the class name and attribute name of attribute as well as the value.
			* @param aClassName The name of the class to bind the attribute to.
			* @param aAttributeName The name of the attribute type. See MetaObjectLinker.h for reserved attribute types.
			* @param aValue The value of the attribute
			*/
            FunctionAttribute(const char * aClassName, const char * aAttributeName, Func<void*, void*> aValue)
                : Attribute(aClassName, aAttributeName)
            {
                m_Value = aValue;
            }

			FunctionAttribute(CString aClassName, CString aAttributeName, Member * aMethodInfo)
				: Attribute(aClassName, aAttributeName),
				m_MethodInfo(aMethodInfo)
			{

			}

			/**
			* Gets the value of the attribute
			* @return Returns the value.
			*/
            inline Func<void*, void*> GetValue()
            {
                return m_Value;
            }

			inline Member * GetMethodInfo()
			{
				return m_MethodInfo;
			}
        private:
			/**
			* The value of the attribute
			*/
            Func<void*, void*> m_Value;

			Member * m_MethodInfo; 
        };

		TYPE_DEFINE(FunctionAttribute);
    }
    
}

#endif