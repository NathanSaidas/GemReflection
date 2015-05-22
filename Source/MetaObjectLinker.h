#ifndef GAME_ENGINE_META_OBJECT_LINKER_H
#define GAME_ENGINE_META_OBJECT_LINKER_H

//============================================================
// Date:			May,	11,		2015
// Description:		Typedefs a bunch of multimap types and interators for atttributes.
//============================================================

#pragma region CHANGE LOG
/// -- January 29, 2015 - Nathan Hanlan - Added class/file MetaObjectLinker
/// -- April    3, 2015 - Nathan Hanlan - Added MetaObjectLinker::ATTRIBUTE_TYPE_IS_ENUM attribute type
#pragma endregion

#include <map>
#include <vector>

#include "GemAPI.h"

#include "BoolAttribute.h"
#include "FloatAttribute.h"
#include "FunctionAttribute.h"
#include "IntAttribute.h"
#include "StringAttribute.h"
#include "MemberAttribute.h"


namespace Gem
{
    namespace Reflection
    {
        typedef std::multimap<char *, BoolAttribute> BoolAttribMap;
        typedef std::multimap<char *, FloatAttribute> FloatAttribMap;
        typedef std::multimap<char *, FunctionAttribute> FuncAttribMap;
        typedef std::multimap<char *, IntAttribute> IntAttribMap;
        typedef std::multimap<char *, StringAttribute> StringAttribMap;
        typedef std::multimap<char *, MemberAttribute> MemberAttribMap;

        typedef std::pair<char*, BoolAttribute> BoolAttribPair;
        typedef std::pair<char*, FloatAttribute> FloatAttribPair;
        typedef std::pair<char*, FunctionAttribute> FuncAttribPair;
        typedef std::pair<char*, IntAttribute> IntAttribPair;
        typedef std::pair<char*, StringAttribute> StringAttribPair;
        typedef std::pair<char*, MemberAttribute> MemberAttribPair;

        typedef std::pair<BoolAttribMap::iterator, BoolAttribMap::iterator> BoolAttribIterator;
        typedef std::pair<FloatAttribMap::iterator, FloatAttribMap::iterator> FloatAttribIterator;
        typedef std::pair<FuncAttribMap::iterator, FuncAttribMap::iterator> FuncAttribIterator;
        typedef std::pair<IntAttribMap::iterator, IntAttribMap::iterator> IntAttribIterator;
        typedef std::pair<StringAttribMap::iterator, StringAttribMap::iterator> StringAttribIterator;
        typedef std::pair<MemberAttribMap::iterator, MemberAttribMap::iterator> MemberAttribIterator;


        ///MetaObjectLinker is a class which holds a set of attributes for the Runtime to Compile into useful MetaData Type objects.
        class GEM_API MetaObjectLinker
        {
        public:

            ///Type list stores a bunch of type names.
            inline static std::vector<char*> & GetTypes()
            {
                static std::vector<char*> types;
                return types;
            }

            ///////////////////////////////
            ///Collections of Attributes///
            ///////////////////////////////
            inline static BoolAttribMap & GetBooleanAttributes()
            {
                static BoolAttribMap attributes;
                return attributes;
            }

            inline static FloatAttribMap & GetFloatAttributes()
            {
                static FloatAttribMap attributes;
                return attributes;
            }

            inline static FuncAttribMap & GetFuncAttributes()
            {
                static FuncAttribMap attributes;
                return attributes;
            }

            inline static IntAttribMap & GetIntAttributes()
            {
                static IntAttribMap attributes;
                return attributes;
            }

            inline static StringAttribMap & GetStringAttributes()
            {
                static StringAttribMap attributes;
                return attributes;
            }

            //inline static MemberMap & GetMembers()
            //{
            //    static MemberMap members;
            //    return members;
            //}

            inline static MemberAttribMap & GetMemberAttributes()
            {
                static MemberAttribMap members;
                return members;
            }

            ///Get ID retrieves an integer ID. The ID starts at 0 and counts up.
            ///This number is guarenteed to be unique until highest int number (2,147,483,647)
            inline static int GetID()
            {
                static int id = 0;
                id++;
                return id;
            }

            ///////////////////////////////////////
            ///Reserved Attribute Name Constants///
            ///////////////////////////////////////
            static const char * ATTRIBUTE_TYPE_NAME;
            static const char * ATTRIBUTE_TYPE_BASE_CLASS_NAME;
            static const char * ATTRIBUTE_TYPE_SIZE;
            static const char * ATTRIBUTE_TYPE_ALIGNMENT;
            static const char * ATTRIBUTE_TYPE_TYPE_ID;
            static const char * ATTRIBUTE_TYPE_CREATE_FUNC;
            static const char * ATTRIBUTE_TYPE_DESTROY_FUNC;
            static const char * ATTRIBUTE_TYPE_INTERFACE;
            static const char * ATTRIBUTE_TYPE_IS_CLASS;
            static const char * ATTRIBUTE_TYPE_IS_INTERFACE;
            static const char * ATTRIBUTE_TYPE_IS_ABSTRACT;
			static const char * ATTRIBUTE_TYPE_IS_ENUM;

            static const char * ATTRIBUTE_TYPE_MEMBER_INFO;
			static const char * ATTRIBUTE_TYPE_METHOD_INFO;
        };

    }
    
}



#endif