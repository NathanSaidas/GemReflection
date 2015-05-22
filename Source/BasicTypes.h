#ifndef GAME_ENGINE_BASIC_TYPES_H
#define GAME_ENGINE_BASIC_TYPES_H

#include "GemAPI.h"
#include "ValueTypes.h"
#include "Reflection.h"

namespace Gem
{    
	//Explicit Export of Types.
	FORCE_EXPORT_META(object);
	FORCE_EXPORT_META(Object);

	/// <summary>
	/// This is the base class of all objects within the reflection framework.
	/// </summary>
	class GEM_API object
	{
		RDECLARE_CLASS(object);
	public:
		object();
		~object();

		RDECLARE_PUBLIC_FUNCTION(object,ToString)
		virtual std::string ToString();
	};

	/// <summary>
	/// An extended version of the object class to include naming of objects.
	/// </summary>
	class GEM_API Object : public object
	{ 
		RDECLARE_CLASS(Object)
	public:
		Object();
		~Object();

		RDECLARE_PUBLIC_FUNCTION(Object, GetName)
		string GetName();
		RDECLARE_PUBLIC_FUNCTION(Object, SetName)
		void SetName(const std::string & aName);
		void SetName(const char * aName);

		RDECLARE_PUBLIC_FUNCTION(Object, ToString)
		std::string ToString();
	private:
		RDECLARE_PRIVATE_MEMBER(Object,m_Name)
		std::string m_Name;

	};

	
	TYPE_DEFINE(object)
	TYPE_DEFINE(Object)

	
	




}

#endif