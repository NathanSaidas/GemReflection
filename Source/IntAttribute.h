#ifndef GAME_ENGINE_INT_ATTRIBUTE_H
#define GAME_ENGINE_INT_ATTRIBUTE_H

//============================================================
// Date:			May,	11,		2015
// Description:		Contains the IntAttribute class.
//============================================================

#pragma region CHANGE LOG
/// -- January, 29, 2015 - Nathan Hanlan - Added IntAttribute class/file
#pragma endregion

//Using Attribute to inherit from.
#include "Attribute.h"
#include "GemAPI.h"

namespace Gem
{
    namespace Reflection
    {
		/**
		* Defines the attribute for integer values.
		*/
        class GEM_API IntAttribute : public Attribute
        {
        public:
			/**
			* The constructor for IntAttribute, Requires the class name and attribute name of attribute as well as the value.
			* @param aClassName The name of the class to bind the attribute to.
			* @param aAttributeName The name of the attribute type. See MetaObjectLinker.h for reserved attribute types.
			* @param aValue The value of the attribute
			*/
            IntAttribute(const char * aClassName, const char * aAttributeName, int aValue)
                : Attribute(aClassName, aAttributeName)
            {
                m_Value = aValue;
            }
			/**
			* Gets the value of the attribute
			* @return Returns the value.
			*/
            inline int GetValue()
            {
                return m_Value;
            }
        private:
			/**
			* The value of the attribute
			*/
            int m_Value;
        };

		TYPE_DEFINE(IntAttribute)

    }
    
}

#endif