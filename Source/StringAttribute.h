#ifndef GAME_ENGINE_STRING_ATTRIBUTE_H
#define GAME_ENGINE_STRING_ATTRIBUTE_H

#pragma region CHANGE LOG
/// -- January, 29, 2015 - Nathan Hanlan - Added StringAttribute class/header
/// -- April, 1, 2015 - Nathan Hanlan - Added Doxygen Style Comments.
/// -- April, 1, 2015 - Nathan Hanlan - Defined a type trait for BoolAttribute.
#pragma endregion

//Using string as the value of the attribute.
#include <string>
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
        class GEM_API StringAttribute : public Attribute
        {
        public:
			/**
			* The constructor for BoolAttribute, Requires the class name and attribute name of attribute as well as the value.
			* @param aClassName The name of the class to bind the attribute to.
			* @param aAttributeName The name of the attribute type. See MetaObjectLinker.h for reserved attribute types.
			* @param aValue The value of the attribute
			*/
            StringAttribute(const char * aClassName, const char * aAttributeName, std::string aValue)
                : Attribute(aClassName, aAttributeName)
            {
                m_Value = aValue;
            }
			/**
			* Gets the value of the attribute
			* @return Returns the value.
			*/
            inline std::string GetValue()
            {
                return m_Value;
            }
        private:
			/**
			* The value of the attribute
			*/
            std::string m_Value;
        };

		TYPE_DEFINE(StringAttribute)

    }
    
}

#endif