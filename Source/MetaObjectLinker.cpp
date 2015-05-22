#include "MetaObjectLinker.h"

namespace Gem
{
    namespace Reflection
    {
        const char * MetaObjectLinker::ATTRIBUTE_TYPE_NAME = "Name";
        const char * MetaObjectLinker::ATTRIBUTE_TYPE_BASE_CLASS_NAME = "BaseClass";
        const char * MetaObjectLinker::ATTRIBUTE_TYPE_SIZE = "Size";
        const char * MetaObjectLinker::ATTRIBUTE_TYPE_ALIGNMENT = "Alignment";
        const char * MetaObjectLinker::ATTRIBUTE_TYPE_TYPE_ID = "TypeID";
        const char * MetaObjectLinker::ATTRIBUTE_TYPE_CREATE_FUNC = "Create";
        const char * MetaObjectLinker::ATTRIBUTE_TYPE_DESTROY_FUNC = "Destroy";
        const char * MetaObjectLinker::ATTRIBUTE_TYPE_INTERFACE = "Interface";
        const char * MetaObjectLinker::ATTRIBUTE_TYPE_IS_CLASS = "IsClass";
        const char * MetaObjectLinker::ATTRIBUTE_TYPE_IS_INTERFACE = "IsInterface";
        const char * MetaObjectLinker::ATTRIBUTE_TYPE_IS_ABSTRACT = "IsAbstract";
		const char * MetaObjectLinker::ATTRIBUTE_TYPE_IS_ENUM = "IsEnum";
        const char * MetaObjectLinker::ATTRIBUTE_TYPE_MEMBER_INFO = "MemberInfo";
		const char * MetaObjectLinker::ATTRIBUTE_TYPE_METHOD_INFO = "MethodInfo";
    }
    
}