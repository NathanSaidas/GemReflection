#ifndef GAME_ENGINE_ATTRIBUTE_BINDER_H
#define GAME_ENGINE_ATTRIBUTE_BINDER_H

//============================================================
// Date:			May,	11,		2015
// Description:		Contains the AttributeBinder class.
//============================================================

#pragma region CHANGE LOG
/// -- January, 30, 2015 - Nathan Hanlan - Added AttributeBinder class/file 
/// -- April, 1, 2015 - Nathan Hanlan - Added Doxygen Style Comments.
/// -- April, 1, 2015 - Nathan Hanlan - Defined a type trait for AttributeBinder.
#pragma endregion

//Included Attributes that are allowed to get bound.
#include "IntAttribute.h"
#include "FloatAttribute.h"
#include "BoolAttribute.h"
#include "StringAttribute.h"
#include "FunctionAttribute.h"
#include "MemberAttribute.h"
//Included Type class to add type. 
#include "Type.h"
#include "GemAPI.h"


namespace Gem
{
    namespace Reflection
    {
		/**
		* AttributeBinder is the base class which handles binding attributes. 
		* Use AttributeBinder with Runtime::Compile() function.
		* Inherit from this class to define a custom AttributeBinder.
		*/
        class GEM_API AttributeBinder
        {
        public:
			/**
			* Gets called when binding an integer attribute.
			* @param aAttribute The attribute getting bound. 
			* @param aType The type receiving information.
			*/
            virtual void BindInteger(IntAttribute & aAttribute, Type & aType) = 0;
			/**
			* Gets called when binding a float attribute.
			* @param aAttribute The attribute getting bound.
			* @param aType The type receiving information.
			*/
            virtual void BindFloat(FloatAttribute & aAttribute, Type & aType) = 0;
			/**
			* Gets called when binding a bool attribute
			* @param aAttribute The attribute getting bound.
			* @param aType The type receiving information.
			*/
            virtual void BindBool(BoolAttribute & aAttribute, Type & aType) = 0;
			/**
			* Gets called when binding a string attribute
			* @param aAttribute The attribute getting bound.
			* @param aType The type receiving information.
			*/
            virtual void BindString(StringAttribute & aAttribute, Type & aType) = 0;
			/**
			* Gets called when binding a function attribute
			* @param aAttribute The attribute getting bound.
			* @param aType The type receiving information.
			*/
            virtual void BindFunction(FunctionAttribute & aAttribute, Type & aType) = 0;
            /**
            * Gets called when binding a function attribute
            * @param aAttribute The attribute getting bound.
            * @param aType The type receiving information.
            */
            virtual void BindMember(MemberAttribute & aAttribute, Type & aType) = 0;

        };

		TYPE_DEFINE(AttributeBinder)
    }
	
}

#endif