#ifndef GAME_ENGINE_TYPE_TRAIT_H
#define GAME_ENGINE_TYPE_TRAIT_H

#pragma region CHANGE LOG
/// -- January, 29, 2015 - Nathan Hanlan - Added TypeTrait class/file
#pragma endregion

#include "GemAPI.h"

namespace Gem
{
	namespace Reflection
	{
		template<typename T>
		struct TypeTrait
		{
		public:
			static inline const char * Name()
			{
				return "unknown";
			}
			static const bool IS_POINTER = false;
		};


	#define TYPE_DEFINE(TYPE)										\
		template<>													\
		struct Gem::Reflection::TypeTrait < TYPE >					\
		{															\
		public:														\
		static inline const char * Name()							\
		{															\
		return #TYPE;												\
		}															\
		static const bool IS_POINTER = false;						\
		};															\
		template<>													\
		struct Gem::Reflection::TypeTrait< TYPE ## *>				\
		{															\
		public:														\
		static inline const char * Name()							\
		{															\
		return #TYPE;												\
		}															\
		static const bool IS_POINTER = true;						\
		};															\
		template<>													\
		struct Gem::Reflection::TypeTrait< TYPE ## **>				\
		{															\
		public:														\
		static inline const char * Name()							\
		{															\
		return #TYPE;												\
		}															\
		static const bool IS_POINTER = true;						\
		};															\



#define TYPE_DEFINE_NAMED(TYPE, NAME)								\
	template<>														\
		struct Gem::Reflection::TypeTrait < TYPE >					\
		{															\
		public:														\
		static inline const char * Name()							\
		{															\
		return NAME;												\
		}															\
		static const bool IS_POINTER = false;						\
		};															\
		template<>													\
		struct Gem::Reflection::TypeTrait< TYPE ## *>				\
		{															\
		public:														\
		static inline const char * Name()							\
		{															\
		return NAME;												\
		}															\
		static const bool IS_POINTER = true;						\
		};															\
		template<>													\
		struct Gem::Reflection::TypeTrait< TYPE ## **>				\
		{															\
		public:														\
		static inline const char * Name()							\
		{															\
		return NAME;												\
		}															\
		static const bool IS_POINTER = true;						\
		};															\

	}
}


#endif