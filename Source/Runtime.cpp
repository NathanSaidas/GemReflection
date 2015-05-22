#include "Runtime.h"
#include "MetaObjectLinker.h"

namespace Gem
{
    bool Type::s_IsCompiling = false;

    namespace Reflection
    {
        
        Runtime * Runtime::s_Instance = nullptr;
		Runtime::Runtime() : m_CompileErrorFlags(0)
        {

        }
        Runtime::~Runtime()
        {
            //for (std::map<std::string, Type>::iterator typeIt = m_CompiledTypes.begin(); typeIt != m_CompiledTypes.end(); ++typeIt)
            //{
            //    std::vector<ClassMember*> members = typeIt->second.m_Members;
            //    for (std::vector<ClassMember*>::iterator it = members.begin(); it != members.end(); ++it)
            //    {
            //        if ((*it) != nullptr)
            //        {
            //            delete (*it);
            //        }
            //    }
            //}

			//Free Memory :)
			for (std::map<std::string, Type>::iterator typeIt = m_CompiledTypes.begin(); typeIt != m_CompiledTypes.end(); ++typeIt)
			{
				std::vector<Member*> methods = typeIt->second.m_Methods;

				for (int i = (int)methods.size() - 1; i >= 0; i--)
				{
					delete methods[i];
				}
			}
        }

        void Runtime::Initialize()
        {
            if (s_Instance == nullptr)
            {
                s_Instance = new Runtime();
            }
        }
        void Runtime::Terminate()
        {
            if (s_Instance != nullptr)
            {
                delete s_Instance;
                s_Instance = nullptr;
            }
        }

        void Runtime::Compile(AttributeBinder * aContext)
        {
            Initialize();
            if (s_Instance->m_IsCompiled)
            {
                return;
            }
            s_Instance->m_IsCompiling = true;
            Type::s_IsCompiling = true;

            std::vector<char *> & types = MetaObjectLinker::GetTypes();
            IntAttribMap & intAttributes = MetaObjectLinker::GetIntAttributes();
            FloatAttribMap & floatAttributes = MetaObjectLinker::GetFloatAttributes();
            BoolAttribMap & boolAttributes = MetaObjectLinker::GetBooleanAttributes();
            StringAttribMap & stringAttributes = MetaObjectLinker::GetStringAttributes();
            FuncAttribMap & functionAttributes = MetaObjectLinker::GetFuncAttributes();
            MemberAttribMap & members = MetaObjectLinker::GetMemberAttributes();

            for (std::vector<char*>::iterator typeIter = types.begin(); typeIter != types.end(); ++typeIter)
            {
                IntAttribIterator intKeyIter = intAttributes.equal_range((*typeIter));
                FloatAttribIterator floatKeyIter = floatAttributes.equal_range((*typeIter));
                BoolAttribIterator boolKeyIter = boolAttributes.equal_range((*typeIter));
                StringAttribIterator stringKeyIter = stringAttributes.equal_range((*typeIter));
                FuncAttribIterator functionKeyIter = functionAttributes.equal_range((*typeIter));
                MemberAttribIterator memberKeyIter = members.equal_range((*typeIter));

                Type type;

                for (IntAttribMap::iterator it = intKeyIter.first; it != intKeyIter.second; ++it)
                {
                    if (aContext != nullptr)
                    {
                        aContext->BindInteger((*it).second, type);
                    }
                    s_Instance->BindIntegerAttributes((*it).second, type);
                }
                for (FloatAttribMap::iterator it = floatKeyIter.first; it != floatKeyIter.second; ++it)
                {
                    if (aContext != nullptr)
                    {
                        aContext->BindFloat((*it).second, type);
                    }
                    s_Instance->BindFloatAttributes((*it).second, type);
                }
                for (BoolAttribMap::iterator it = boolKeyIter.first; it != boolKeyIter.second; ++it)
                {
                    if (aContext != nullptr)
                    {
                        aContext->BindBool((*it).second, type);
                    }
                    s_Instance->BindBoolAttributes((*it).second, type);
                }
                for (StringAttribMap::iterator it = stringKeyIter.first; it != stringKeyIter.second; ++it)
                {
                    if (aContext != nullptr)
                    {
                        aContext->BindString((*it).second, type);
                    }
                    s_Instance->BindStringAttributes((*it).second, type);
                }
                for (FuncAttribMap::iterator it = functionKeyIter.first; it != functionKeyIter.second; ++it)
                {
                    if (aContext != nullptr)
                    {
                        aContext->BindFunction((*it).second, type);
                    }
                    s_Instance->BindFunctionAttributes((*it).second, type);
                }

                for (MemberAttribMap::iterator it = memberKeyIter.first; it != memberKeyIter.second; ++it)
                {
                    if (aContext != nullptr)
                    {

                    }
                    s_Instance->BindMemberInfoAttribute((*it).second, type);
                }

                //printf("Compiled Type: %s\n", type.GetName().c_str());
                s_Instance->m_CompiledTypes.insert(std::pair<std::string, Type>(type.GetName(), type));
            }

            types.clear();
            intAttributes.clear();
            floatAttributes.clear();
            boolAttributes.clear();
            stringAttributes.clear();
            functionAttributes.clear();

            if (aContext != nullptr)
            {
                delete aContext;
                aContext = nullptr;
            }

			//Go through each created type and inherit the members... (Functions / Members)

			int size = s_Instance->m_CompiledTypes.size();
			bool * typeLinkComplete = new bool[size];
			for (int i = 0; i < size; i++)
			{
				typeLinkComplete[i] = false;
			}


			for (std::map<std::string, Type>::iterator it = s_Instance->m_CompiledTypes.begin(); it != s_Instance->m_CompiledTypes.end(); it++)
			{
				//printf("Linking Type %s (%d)\n", (*it).second.GetName().c_str(), (*it).second.GetTypeID());

				s_Instance->LinkBaseClassMembers((*it).second, typeLinkComplete);
			}

			delete[] typeLinkComplete;

            s_Instance->m_IsCompiled = true;
            s_Instance->m_IsCompiling = false;
            Type::s_IsCompiling = false;
        }
        Type Runtime::TypeOf(const std::string & aName)
        {
            if (s_Instance == nullptr)
            {
                return Type();
            }
            std::map<std::string, Type>::iterator type = s_Instance->m_CompiledTypes.find(aName);
            if (type == s_Instance->m_CompiledTypes.end())
            {
                return Type();
            }
            return (*type).second;
        }
		Array<Type> Runtime::GetAllTypes()
		{
			if (s_Instance == nullptr)
			{
				return Array<Type>();
			}
			Array<Type> types = s_Instance->m_CompiledTypes.size();
			int index = 0;
			for (std::map<std::string, Type>::iterator it = s_Instance->m_CompiledTypes.begin();
				it != s_Instance->m_CompiledTypes.end();
				it++)
			{
				types[index] = (*it).second;
				index++;
			}
			return types;
		}
        bool Runtime::IsBaseOf(Type & aDerived, Type & aBaseClass)
        {
            Type type = aDerived;

            while (!IsBadType(type))
            {
				Array<Type> interfaces = type.GetInterfaces();

				for (int i = 0; i < interfaces.GetCount(); i++)
				{
					if (aBaseClass == interfaces[i])
					{
						return true;
					}
				}

                type = TypeOf(type.GetBaseClass());
                if (aBaseClass == type)
                {
                    return true;
                }

            }

            return false;
        }
        bool Runtime::IsBadType(const Type & aType)
        {
            return aType.GetName() == "";
        }
        bool Runtime::IsCompiling()
        {
            return s_Instance->m_IsCompiling;
        }
		bool Runtime::IsCompiled()
		{
			return s_Instance->m_IsCompiled;
		}
        void Runtime::BindIntegerAttributes(IntAttribute & aAttribute, Type & aType)
        {
            if (aAttribute.Is(Attribute("",MetaObjectLinker::ATTRIBUTE_TYPE_ALIGNMENT)))
            {
                aType.m_Alignment = aAttribute.GetValue();
            }
			else if (aAttribute.Is(Attribute("",MetaObjectLinker::ATTRIBUTE_TYPE_SIZE)))
            {
                aType.m_Size = aAttribute.GetValue();
            }
			else if (aAttribute.Is(Attribute("",MetaObjectLinker::ATTRIBUTE_TYPE_TYPE_ID)))
            {
                aType.m_TypeID = aAttribute.GetValue();
            }
        }
        void Runtime::BindFloatAttributes(FloatAttribute & aAttribute, Type & aType)
        {

        }
        void Runtime::BindBoolAttributes(BoolAttribute & aAttribute, Type & aType)
        {
			if (aAttribute.Is(Attribute("",MetaObjectLinker::ATTRIBUTE_TYPE_IS_ABSTRACT)))
            {
                aType.m_IsAbstract = aAttribute.GetValue();
            }
			else if (aAttribute.Is(Attribute("",MetaObjectLinker::ATTRIBUTE_TYPE_IS_CLASS)))
            {
                aType.m_IsClass = aAttribute.GetValue();
            }
			else if (aAttribute.Is(Attribute("",MetaObjectLinker::ATTRIBUTE_TYPE_IS_INTERFACE)))
            {
                aType.m_IsInterface = aAttribute.GetValue();
            }
			else if (aAttribute.Is(Attribute("", MetaObjectLinker::ATTRIBUTE_TYPE_IS_ENUM)))
			{
				aType.m_IsEnum = aAttribute.GetValue();
			}
        }
        void Runtime::BindStringAttributes(StringAttribute & aAttribute, Type & aType)
        {
			if (aAttribute.Is(Attribute("",MetaObjectLinker::ATTRIBUTE_TYPE_BASE_CLASS_NAME)))
            {
                aType.m_BaseClass = aAttribute.GetValue();
            }
			else if (aAttribute.Is(Attribute("",MetaObjectLinker::ATTRIBUTE_TYPE_NAME)))
            {
                aType.m_Name = aAttribute.GetValue();
            }
			else if (aAttribute.Is(Attribute("",MetaObjectLinker::ATTRIBUTE_TYPE_INTERFACE)))
            {
                aType.m_Interfaces.push_back(aAttribute.GetValue());
            }

        }
        void Runtime::BindFunctionAttributes(FunctionAttribute & aAttribute, Type & aType)
        {
			if (aAttribute.Is(Attribute("",MetaObjectLinker::ATTRIBUTE_TYPE_CREATE_FUNC)))
            {
                aType.m_Constructor = aAttribute.GetValue();
            }
			else if (aAttribute.Is(Attribute("",MetaObjectLinker::ATTRIBUTE_TYPE_DESTROY_FUNC)))
            {
                aType.m_Destructor = aAttribute.GetValue();
            }
			else if (aAttribute.Is(Attribute("", MetaObjectLinker::ATTRIBUTE_TYPE_METHOD_INFO)))
			{
				aType.m_Methods.push_back(aAttribute.GetMethodInfo());
			}
        }
        void Runtime::BindMemberInfoAttribute(MemberAttribute & aAttribute, Type & aType)
        {
            if (aAttribute.Is(Attribute("", MetaObjectLinker::ATTRIBUTE_TYPE_MEMBER_INFO)))
            {
                aType.m_Members.push_back(aAttribute.GetValue());
            }
        }

		void Runtime::LinkBaseClassMembers(Type & aChild, bool * typeLinkComplete)
		{
			//Get Baseclass Type...
			//Check if its been linked.
			//If not recursively call this method on that type.

			std::string baseclassName = aChild.GetBaseClass();
			if (baseclassName == "")
			{
				typeLinkComplete[aChild.GetTypeID() - 1] = true;
				return;
			}

			std::map<std::string, Type>::iterator typeIter = s_Instance->m_CompiledTypes.find(baseclassName);
			if (typeIter == s_Instance->m_CompiledTypes.end())
			{
				typeLinkComplete[aChild.GetTypeID() - 1] = true;
				//Error: Type doesnt exist.
				return;
			}

			Type & const baseClass = typeIter->second;

			//If the type is not linked, link it then grab its members.
			if (typeLinkComplete[baseClass.GetTypeID() - 1] == false)
			{
				LinkBaseClassMembers(baseClass, typeLinkComplete);
			}
			
			Array<MemberInfo> members = baseClass.GetMembers();
			Array<Member*> methods = baseClass.GetMethods();
			Array<std::string> interfaces = baseClass.m_Interfaces.size();
			Array<std::string>::Copy(baseClass.m_Interfaces, interfaces);

			//Add all members from the base class if they dont exist in the child class.
			for (int i = 0; i < members.GetCount(); i++)
			{
				if (std::find(aChild.m_Members.begin(), aChild.m_Members.end(), members[i]) == aChild.m_Members.end())
				{
					aChild.m_InheritedMembers.push_back(members[i]);
				}
			}

			//Add all methods from the base class if they dont exist in the child class.
			for (int i = 0; i < methods.GetCount(); i++)
			{
				bool exists = false;
				for (std::vector<Member*>::iterator it = aChild.m_Methods.begin();
					it != aChild.m_Methods.end();
					it++)
				{
					if (strcmp((*it)->GetMemberName(), methods[i]->GetMemberName()) == 0)
					{
						exists = true;
						break;
					}
				}
				if (!exists)
				{
					aChild.m_InheritedMethods.push_back(methods[i]);
				}
			}

			//Add all interfaces...
			for (int i = 0; i < interfaces.GetCount(); i++)
			{
				if(std::find(aChild.m_Interfaces.begin(), aChild.m_Interfaces.end(), interfaces[i]) == aChild.m_Interfaces.end())
				{
					aChild.m_Interfaces.push_back(interfaces[i]);
				}
			}

			//Type Link Complete
			typeLinkComplete[aChild.GetTypeID() - 1] = true;
		}
    }

}
