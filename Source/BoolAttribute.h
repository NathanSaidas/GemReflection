#ifndef GAME_ENGINE_BOOL_ATTRIBUTE_H
#define GAME_ENGINE_BOOL_ATTRIBUTE_H

//============================================================
// Date:			May,	11,		2015
// Description:		Contains the BoolAttribute class.
//============================================================

#pragma region CHANGE LOG
/// -- January, 29, 2015 - Nathan Hanlan - Added BoolAttribute class/file
/// -- April, 1, 2015 - Nathan Hanlan - Added Doxygen Style Comments.
/// -- April, 1, 2015 - Nathan Hanlan - Defined a type trait for BoolAttribute.
#pragma endregion

//Using Attribute to inherit from.
#include "Attribute.h"
#include "GemAPI.h"

namespace Gem
{
    namespace Reflection
    {
		/**
		* Defines the attribute for boolean values.
		*/
        class GEM_API BoolAttribute : public Attribute
        {
        public:
			/**
			* The constructor for BoolAttribute, Requires the class name and attribute name of attribute as well as the value.
			* @param aClassName The name of the class to bind the attribute to.
			* @param aAttributeName The name of the attribute type. See MetaObjectLinker.h for reserved attribute types.
			* @param aValue The value of the attribute
			*/
            BoolAttribute(const char * aClassName, const char * aAttributeName, bool aValue)
                : Attribute(aClassName, aAttributeName)
            {
                m_Value = aValue;
            }
			/**
			* Gets the value of the attribute
			* @return Returns the value.
			*/
            inline bool GetValue()
            {
                return m_Value;
            }
        private:
			/**
			* The value of the attribute
			*/
            bool m_Value;
        };

		TYPE_DEFINE(BoolAttribute)

    }
    
}

#endif