#ifndef GAME_ENGINE_FLOAT_ATTRIBUTE_H
#define GAME_ENGINE_FLOAT_ATTRIBUTE_H

//============================================================
// Date:			May,	11,		2015
// Description:		Contains the FloatAttribute class.
//============================================================

#pragma region CHANGE LOG
/// -- January, 29, 2015 - Nathan Hanlan - Added FloatAttribute class/file
/// -- April, 1, 2015 - Nathan Hanlan - Added Doxygen Style Comments.
/// -- April, 1, 2015 - Nathan Hanlan - Defined a type trait for FloatAttribute.
#pragma endregion

//Using Attribute to inherit from.
#include "Attribute.h"
#include "GemAPI.h"

namespace Gem
{
    namespace Reflection
    {
		/**
		* Defines the attribute for float values.
		*/
        class GEM_API FloatAttribute : public Attribute
        {
        public:
			/**
			* The constructor for FloatAttribute, Requires the class name and attribute name of attribute as well as the value.
			* @param aClassName The name of the class to bind the attribute to.
			* @param aAttributeName The name of the attribute type. See MetaObjectLinker.h for reserved attribute types.
			* @param aValue The value of the attribute
			*/
            FloatAttribute(const char * aClassName, const char * aAttributeName, float aValue)
                : Attribute(aClassName, aAttributeName)
            {
                m_Value = aValue;
            }
			/**
			* Gets the value of the attribute
			* @return Returns the value.
			*/
            inline float GetValue()
            {
                return m_Value;
            }
        private:
			/**
			* The value of the attribute
			*/
            float m_Value;
        };

		TYPE_DEFINE(FloatAttribute)
    }
    
}

#endif