#ifndef GAME_ENGINE_META_OBJECT__H
#define GAME_ENGINE_META_OBJECT__H

//============================================================
// Date:			May,	11,		2015
// Description:		Contains the MetaObject class.
//============================================================

#pragma region CHANGE LOG
/// -- January, 29, 2015 - Nathan Hanlan - Added MetaObject file.
/// -- Janaury, 29, 2015 - Nathan Hanlan - Added DefineInterface, DefineClassInterface and DefineMember methods to MetaObject class.
#pragma endregion


#include <limits>
#include <type_traits>
#include "GemAPI.h"
#include "Method.h"
#include "TypeTrait.h"
#include "MetaObjectLinker.h"



namespace Gem
{
    namespace Reflection
    {
		/**
		* Defines meta data of a class which can be retrieved at runtime through reflection.
		*/
        template<class T>
        class MetaObject
        {
        public:
            static MetaObject DefineClass(const char * aClassName, const char * aBaseClass)
            {
                std::vector<char *> & types = MetaObjectLinker::GetTypes();
                BoolAttribMap & boolAttributes = MetaObjectLinker::GetBooleanAttributes();
                FloatAttribMap & floatAttributes = MetaObjectLinker::GetFloatAttributes();
                FuncAttribMap & funcAttributes = MetaObjectLinker::GetFuncAttributes();
                IntAttribMap & intAttributes = MetaObjectLinker::GetIntAttributes();
                StringAttribMap & stringAttributes = MetaObjectLinker::GetStringAttributes();

                types.push_back(const_cast<char*>(aClassName));

				//static_assert(!std::is_abstract<T>::value, "Abstract Type");


                ///Insert class name and base class attributes into the registry
                stringAttributes.insert(StringAttribPair(const_cast<char*>(aClassName), StringAttribute(aClassName, MetaObjectLinker::ATTRIBUTE_TYPE_NAME, aClassName)));
                stringAttributes.insert(StringAttribPair(const_cast<char*>(aClassName), StringAttribute(aClassName, MetaObjectLinker::ATTRIBUTE_TYPE_BASE_CLASS_NAME, aBaseClass)));
                ///Insert compile time class information such as size and alignment into the registry
                intAttributes.insert(IntAttribPair(const_cast<char*>(aClassName), IntAttribute(aClassName, MetaObjectLinker::ATTRIBUTE_TYPE_SIZE, sizeof(T))));
				intAttributes.insert(IntAttribPair(const_cast<char*>(aClassName), IntAttribute(aClassName, MetaObjectLinker::ATTRIBUTE_TYPE_ALIGNMENT, __alignof(T))));
                boolAttributes.insert(BoolAttribPair(const_cast<char*>(aClassName), BoolAttribute(aClassName, MetaObjectLinker::ATTRIBUTE_TYPE_IS_CLASS, true)));
                boolAttributes.insert(BoolAttribPair(const_cast<char*>(aClassName), BoolAttribute(aClassName, MetaObjectLinker::ATTRIBUTE_TYPE_IS_INTERFACE, false)));
                boolAttributes.insert(BoolAttribPair(const_cast<char*>(aClassName), BoolAttribute(aClassName, MetaObjectLinker::ATTRIBUTE_TYPE_IS_ABSTRACT, false)));
				boolAttributes.insert(BoolAttribPair(const_cast<char*>(aClassName), BoolAttribute(aClassName, MetaObjectLinker::ATTRIBUTE_TYPE_IS_ENUM, false)));
                ///Create an ID and assign it into the registry as well.
                intAttributes.insert(IntAttribPair(const_cast<char*>(aClassName), IntAttribute(aClassName, MetaObjectLinker::ATTRIBUTE_TYPE_TYPE_ID, MetaObjectLinker::GetID())));

                ///Constructor / Destructor callbacks
                funcAttributes.insert(FuncAttribPair(const_cast<char*>(aClassName), FunctionAttribute(aClassName, MetaObjectLinker::ATTRIBUTE_TYPE_CREATE_FUNC, CreateObject)));
                funcAttributes.insert(FuncAttribPair(const_cast<char*>(aClassName), FunctionAttribute(aClassName, MetaObjectLinker::ATTRIBUTE_TYPE_DESTROY_FUNC, DestroyObject)));

                return GetInstance();
            }

            static MetaObject DefineAbstractClass(const char * aClassName, const char * aBaseClass)
            {
                std::vector<char *> & types = MetaObjectLinker::GetTypes();
                BoolAttribMap & boolAttributes = MetaObjectLinker::GetBooleanAttributes();
                FloatAttribMap & floatAttributes = MetaObjectLinker::GetFloatAttributes();
                FuncAttribMap & funcAttributes = MetaObjectLinker::GetFuncAttributes();
                IntAttribMap & intAttributes = MetaObjectLinker::GetIntAttributes();
                StringAttribMap & stringAttributes = MetaObjectLinker::GetStringAttributes();

                types.push_back(const_cast<char*>(aClassName));


                ///Insert class name and base class attributes into the registry
                stringAttributes.insert(StringAttribPair(const_cast<char*>(aClassName), StringAttribute(aClassName, MetaObjectLinker::ATTRIBUTE_TYPE_NAME, aClassName)));
                stringAttributes.insert(StringAttribPair(const_cast<char*>(aClassName), StringAttribute(aClassName, MetaObjectLinker::ATTRIBUTE_TYPE_BASE_CLASS_NAME, aBaseClass)));
                ///Insert compile time class information such as size and alignment into the registry
                intAttributes.insert(IntAttribPair(const_cast<char*>(aClassName), IntAttribute(aClassName, MetaObjectLinker::ATTRIBUTE_TYPE_SIZE, sizeof(T))));
                intAttributes.insert(IntAttribPair(const_cast<char*>(aClassName), IntAttribute(aClassName, MetaObjectLinker::ATTRIBUTE_TYPE_ALIGNMENT, 0)));
                boolAttributes.insert(BoolAttribPair(const_cast<char*>(aClassName), BoolAttribute(aClassName, MetaObjectLinker::ATTRIBUTE_TYPE_IS_CLASS, true)));
                boolAttributes.insert(BoolAttribPair(const_cast<char*>(aClassName), BoolAttribute(aClassName, MetaObjectLinker::ATTRIBUTE_TYPE_IS_INTERFACE, false)));
                boolAttributes.insert(BoolAttribPair(const_cast<char*>(aClassName), BoolAttribute(aClassName, MetaObjectLinker::ATTRIBUTE_TYPE_IS_ABSTRACT, true)));
				boolAttributes.insert(BoolAttribPair(const_cast<char*>(aClassName), BoolAttribute(aClassName, MetaObjectLinker::ATTRIBUTE_TYPE_IS_ENUM, false)));
                ///Create an ID and assign it into the registry as well.
                intAttributes.insert(IntAttribPair(const_cast<char*>(aClassName), IntAttribute(aClassName, MetaObjectLinker::ATTRIBUTE_TYPE_TYPE_ID, MetaObjectLinker::GetID())));

                ///Constructor / Destructor callbacks
                funcAttributes.insert(FuncAttribPair(const_cast<char*>(aClassName), FunctionAttribute(aClassName, MetaObjectLinker::ATTRIBUTE_TYPE_CREATE_FUNC, nullptr)));
                funcAttributes.insert(FuncAttribPair(const_cast<char*>(aClassName), FunctionAttribute(aClassName, MetaObjectLinker::ATTRIBUTE_TYPE_DESTROY_FUNC, nullptr)));

                return GetInstance();
            }


            static MetaObject DefineInterface(const char * aInterfaceName)
            {
                std::vector<char *> & types = MetaObjectLinker::GetTypes();
                BoolAttribMap & boolAttributes = MetaObjectLinker::GetBooleanAttributes();
                FloatAttribMap & floatAttributes = MetaObjectLinker::GetFloatAttributes();
                FuncAttribMap & funcAttributes = MetaObjectLinker::GetFuncAttributes();
                IntAttribMap & intAttributes = MetaObjectLinker::GetIntAttributes();
                StringAttribMap & stringAttributes = MetaObjectLinker::GetStringAttributes();

                types.push_back(const_cast<char*>(aInterfaceName));

                stringAttributes.insert(StringAttribPair(const_cast<char*>(aInterfaceName), StringAttribute(aInterfaceName, MetaObjectLinker::ATTRIBUTE_TYPE_NAME, aInterfaceName)));

                intAttributes.insert(IntAttribPair(const_cast<char*>(aInterfaceName), IntAttribute(aInterfaceName, MetaObjectLinker::ATTRIBUTE_TYPE_SIZE, sizeof(T))));
                intAttributes.insert(IntAttribPair(const_cast<char*>(aInterfaceName), IntAttribute(aInterfaceName, MetaObjectLinker::ATTRIBUTE_TYPE_ALIGNMENT, 0)));
                boolAttributes.insert(BoolAttribPair(const_cast<char*>(aInterfaceName), BoolAttribute(aInterfaceName, MetaObjectLinker::ATTRIBUTE_TYPE_IS_CLASS, false)));
                boolAttributes.insert(BoolAttribPair(const_cast<char*>(aInterfaceName), BoolAttribute(aInterfaceName, MetaObjectLinker::ATTRIBUTE_TYPE_IS_INTERFACE, true)));
                boolAttributes.insert(BoolAttribPair(const_cast<char*>(aInterfaceName), BoolAttribute(aInterfaceName, MetaObjectLinker::ATTRIBUTE_TYPE_IS_ABSTRACT, true)));
				boolAttributes.insert(BoolAttribPair(const_cast<char*>(aInterfaceName), BoolAttribute(aInterfaceName, MetaObjectLinker::ATTRIBUTE_TYPE_IS_ENUM, false)));

                intAttributes.insert(IntAttribPair(const_cast<char*>(aInterfaceName), IntAttribute(aInterfaceName, MetaObjectLinker::ATTRIBUTE_TYPE_TYPE_ID, MetaObjectLinker::GetID())));

                ///Constructor / Destructor callbacks
                funcAttributes.insert(FuncAttribPair(const_cast<char*>(aInterfaceName), FunctionAttribute(aInterfaceName, MetaObjectLinker::ATTRIBUTE_TYPE_CREATE_FUNC, nullptr)));
                funcAttributes.insert(FuncAttribPair(const_cast<char*>(aInterfaceName), FunctionAttribute(aInterfaceName, MetaObjectLinker::ATTRIBUTE_TYPE_DESTROY_FUNC, nullptr)));


                return GetInstance();
            }

			static MetaObject DefineEnum(const char * aEnum)
			{
				std::vector<char *> & types = MetaObjectLinker::GetTypes();
				BoolAttribMap & boolAttributes = MetaObjectLinker::GetBooleanAttributes();
				FloatAttribMap & floatAttributes = MetaObjectLinker::GetFloatAttributes();
				FuncAttribMap & funcAttributes = MetaObjectLinker::GetFuncAttributes();
				IntAttribMap & intAttributes = MetaObjectLinker::GetIntAttributes();
				StringAttribMap & stringAttributes = MetaObjectLinker::GetStringAttributes();

				types.push_back(const_cast<char*>(aEnum));


				///Insert class name and base class attributes into the registry
				stringAttributes.insert(StringAttribPair(const_cast<char*>(aEnum), StringAttribute(aEnum, MetaObjectLinker::ATTRIBUTE_TYPE_NAME, aEnum)));
				stringAttributes.insert(StringAttribPair(const_cast<char*>(aEnum), StringAttribute(aEnum, MetaObjectLinker::ATTRIBUTE_TYPE_BASE_CLASS_NAME, "")));
				///Insert compile time class information such as size and alignment into the registry
				intAttributes.insert(IntAttribPair(const_cast<char*>(aEnum), IntAttribute(aEnum, MetaObjectLinker::ATTRIBUTE_TYPE_SIZE, sizeof(T))));
				intAttributes.insert(IntAttribPair(const_cast<char*>(aEnum), IntAttribute(aEnum, MetaObjectLinker::ATTRIBUTE_TYPE_ALIGNMENT, __alignof(T))));
				boolAttributes.insert(BoolAttribPair(const_cast<char*>(aEnum), BoolAttribute(aEnum, MetaObjectLinker::ATTRIBUTE_TYPE_IS_CLASS, false)));
				boolAttributes.insert(BoolAttribPair(const_cast<char*>(aEnum), BoolAttribute(aEnum, MetaObjectLinker::ATTRIBUTE_TYPE_IS_INTERFACE, false)));
				boolAttributes.insert(BoolAttribPair(const_cast<char*>(aEnum), BoolAttribute(aEnum, MetaObjectLinker::ATTRIBUTE_TYPE_IS_ABSTRACT, false)));
				boolAttributes.insert(BoolAttribPair(const_cast<char*>(aEnum), BoolAttribute(aEnum, MetaObjectLinker::ATTRIBUTE_TYPE_IS_ENUM, true)));
				///Create an ID and assign it into the registry as well.
				intAttributes.insert(IntAttribPair(const_cast<char*>(aEnum), IntAttribute(aEnum, MetaObjectLinker::ATTRIBUTE_TYPE_TYPE_ID, MetaObjectLinker::GetID())));

				///Constructor / Destructor callbacks
				funcAttributes.insert(FuncAttribPair(const_cast<char*>(aEnum), FunctionAttribute(aEnum, MetaObjectLinker::ATTRIBUTE_TYPE_CREATE_FUNC, CreateObject)));
				funcAttributes.insert(FuncAttribPair(const_cast<char*>(aEnum), FunctionAttribute(aEnum, MetaObjectLinker::ATTRIBUTE_TYPE_DESTROY_FUNC, DestroyObject)));

				return GetInstance();
			}

            //static MetaObject DefineMember(const char * aClassName, ClassMember * aMember)
            //{
            //    if (aMember != nullptr)
            //    {
            //        MemberMap & members = MetaObjectLinker::GetMembers();
            //        members.insert(MemberPair(const_cast<char*>(aClassName), aMember));
            //    }
            //    return GetInstance();
            //}

            static MetaObject DefineClassInterface(const char * aClassName, const char * aInterfaceName)
            {
                StringAttribMap & stringAttributes = MetaObjectLinker::GetStringAttributes();
                stringAttributes.insert(StringAttribPair(const_cast<char*>(aClassName), StringAttribute(aClassName, MetaObjectLinker::ATTRIBUTE_TYPE_INTERFACE, aInterfaceName)));
                return GetInstance();
            }

            static MetaObject DefineProperty(const char * aClassName, const char * aPropertyName, const char * aPropertyValue)
            {
                StringAttribMap & stringAttributes = MetaObjectLinker::GetStringAttributes();
                stringAttributes.insert(StringAttribPair(const_cast<char*>(aClassName), StringAttribute(aClassName, aPropertyName, aPropertyValue)));
                return GetInstance();
            }

            //static MetaObject DeclareMember(const char * aClassName, const char * aMemberName, size_t offset)
            //{
            //    char * classname = "TestComponent";
            //    char * memberName = "m_Material";
            //    //IntPtr offset = offsetof(TestComponent, m_Material);
            //    //Type type = m_Material->GetType();
            //
            //    return GetInstance();
            //}

            static MetaObject DeclareMemberType(const char * aClassName, const char * aMemberName, size_t aOffset, const char * aTypename, const MemberFlags & aFlags)
            {
                //MemberInfo info = MemberInfo(const_cast<char*>(aClassName), const_cast<char*>(aMemberName), const_cast<char*>(aTypename), aOffset, aPublic);

				MemberInfo info = MemberInfo(aClassName, aMemberName, aFlags, aTypename, aOffset);

                MemberAttribMap & memberAttributes = MetaObjectLinker::GetMemberAttributes();
                memberAttributes.insert(
                    MemberAttribPair(const_cast<char*>(aClassName),
                    MemberAttribute(aClassName, MetaObjectLinker::ATTRIBUTE_TYPE_MEMBER_INFO, info)));
              

                return GetInstance();
            }

			template<typename RETURN,typename ... ARGS>
			static MetaObject DeclareFunction(const char * aClassName, const char * aFunctionName, MemberFlags aFlags, Method<T,RETURN,ARGS...> aFunction)
			{

				MethodInfo<T, RETURN, ARGS...> * methodInfo = new MethodInfo<T, RETURN, ARGS...>(aFunction, aClassName, aFunctionName, aFlags);

				FuncAttribMap & functionAttributes = MetaObjectLinker::GetFuncAttributes();
				functionAttributes.insert(
					FuncAttribPair(const_cast<char*>(aClassName),
					FunctionAttribute(aClassName, MetaObjectLinker::ATTRIBUTE_TYPE_METHOD_INFO, methodInfo)));

				return GetInstance();
			}

			static MetaObject Empty()
			{
				return GetInstance();
			}

        private:
            static void * CreateObject(void * aMemoryAddress)
            {
                return new(aMemoryAddress)T();
            }
            static void * DestroyObject(void * aMemoryAddress)
            {
                T * obj = static_cast<T*>(aMemoryAddress);
                if (obj != nullptr)
                {
                    obj->~T();
                    return nullptr;
                }
                return aMemoryAddress;
            }

            static MetaObject & GetInstance()
            {
                static MetaObject<T> metaObject;
                return metaObject;
            }
            MetaObject()
            {

            }

        };




    }///End Reflection Namespace
}///End Engine Namespace

#endif