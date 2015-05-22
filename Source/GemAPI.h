#ifndef GEM_API_H
#define GEM_API_H

#ifdef GEM_FRAMEWORK_EXPORT
#define GEM_API _declspec(dllexport)
#define FORCE_EXPORT(TYPE) template class GEM_API TYPE
#define FORCE_EXPORT_META(TYPE) class TYPE; template class GEM_API Gem::Reflection::MetaObject<TYPE>
#elif GEM_FRAMEWORK_IMPORT
#define GEM_API _declspec(dllimport)
#define FORCE_EXPORT(TYPE) template class GEM_API TYPE
#define FORCE_EXPORT_META(TYPE) class TYPE; template class GEM_API Gem::Reflection::MetaObject<TYPE>
#else
#define GEM_API
#define FORCE_EXPORT(TYPE) template class GEM_API TYPE
#define FORCE_EXPORT_META(TYPE) class TYPE; template class GEM_API Gem::Reflection::MetaObject<TYPE>
#endif

#include <string>
#include <vector>

//std::string export
template class GEM_API std::basic_string<char, std::char_traits<char>, std::allocator<char>>;
//std::vector<string> export
template class GEM_API std::vector<std::string>;


#endif