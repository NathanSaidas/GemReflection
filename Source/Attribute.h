#ifndef GAME_ENGINE_ATTRIBUTE_H
#define GAME_ENGINE_ATTRIBUTE_H


//============================================================
// Date:			May,	11,		2015
// Description:		Contains the Attribute class.
//============================================================

#pragma region CHANGE LOG
/// -- January, 29, 2015 - Nathan Hanlan - Added Attribute class/file
/// -- April, 1, 2015 - Nathan Hanlan - Added Doxygen Style Comments.
/// -- April, 1, 2015 - Nathan Hanlan - Defined a type trait for Attribute.
#pragma endregion

#include "GemAPI.h"
//Using cstring library for strcmp function
#include <cstring>
//Using TypeTrait to add some reflection information to this class.
#include "TypeTrait.h"

namespace Gem
{
    namespace Reflection
    {
		/**
		*	Attributes define raw meta data for class types. Attributes get compiled and linked into Type objects later using AttributeBinders.
		*/
        class GEM_API Attribute
        {
        public:
			/**
			* Constructor for Attribute. Attributes require a class name and an attribute name.
			* @param aClassName The name of the class to bind the attribute to.
			* @param aAttributeName The name of the attribute type. See MetaObjectLinker.h for reserved attribute types.
			*/
            Attribute(const char * aClassName, const char * aAttributeName)
            {
                m_ClassName = const_cast<char*>(aClassName);
                m_AttributeName = const_cast<char*>(aAttributeName);
            }

			/** 
			* Gets the name of the class.
			* @return Returns the name of the class.
			*/
            inline char * GetClassName()
            {
                return m_ClassName;
            }
			/**
			* Gets the name of the attribute type.
			* @return Returns the attribute type name.
			*/
            inline char * GetAttributeName()
            {
                return m_AttributeName;
            }
			/** 
			* Determines if the Attribute is equal
			* @param aAttribute The attribute to compare attribute type names with.
			* @return Returns true if they are equal, false otherwise.
			*/
            inline bool Is(const Attribute & aAttribute)
            {
                return strcmp(m_AttributeName, aAttribute.m_AttributeName) == 0;
            }
        private:
			/**
			* The name of the class to bind to during linking.
			*/
			char * m_ClassName;
			/**
			* The attribute type name for linking.
			*/
            char * m_AttributeName;
        };

		TYPE_DEFINE(Attribute)
    }
}

#endif