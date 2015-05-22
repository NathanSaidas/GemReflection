#ifndef GEM_ENUM_H
#define GEM_ENUM_H

#pragma region CHANGE LOG
/// -- April	3, 2015 - Nathan Hanlan - Added class Enum. This will be the base class of all future enums.
#pragma endregion

//TODO(Nathan): Create proper name for enum DECLARE

#include "BasicTypes.h"
#include "Array.h"

namespace Gem
{

	FORCE_EXPORT_META(Enum);

	/**
	* Base class for enum types.
	*/
	class GEM_API Enum : public object
	{
		RDECLARE_ENUM(Enum)
	protected:
		/**
		* Override and implement to return a string version of the value.
		* @return Returns a string version of the value.
		*/
		virtual std::string GetName();
		/**
		* Override and implement to return an array of strings corresponding with the available values.
		* @return Returns an array of strings corresponding with the available values.
		*/
		virtual Array<std::string> GetNames();
		/**
		* Override and implement to return the current value in an integer format.
		* @return Returns the value in an integer format.
		*/
		virtual SInt32 GetValue();
		/**
		* Override and implement to return the available values
		* @return Returns the available values.
		*/
		virtual Array<SInt32> GetValues();

		
	public:
		/**
		* Returns the string version of the enum.
		* @param aEnum The enum to get the name from.
		* @return Returns a string version of the value.
		*/
		static std::string GetName(Enum * aEnum);
		/**
		* Returns the array of strings corresponding with the available values.
		* @param aEnum The enum to get the names from.
		* @return Returns an array of strings corresponding with the available values.
		*/
		static Array<std::string> GetNames(Enum * aEnum);
		/**
		* Returns the value of the enum in integer format.
		* @param aEnum The enum to get the value from.
		* @return Returns the value in an integer format.
		*/
		static SInt32 GetValue(Enum * aEnum);
		static SInt32 Enum::GetValue(const Enum * aEnum);
		/**
		* Returns the available values of the enum in integer format.
		* @param enum The enum to get the values from.
		* @return Returns the available values.
		*/
		static Array<SInt32> GetValues(Enum * aEnum);

		static bool IsValid(Enum * aEnum);
		
		static int InvalidEnum();

		/**
		* Returns the name of the enum. 
		* @return Returns the name of the enum.
		*/
		std::string ToString();
	};
}

#define RENUM_H(TYPE,VALUES,COUNT) private: VALUES m_Value;					\
	protected:																\
		std::string GetName();												\
		Gem::Array<std::string> GetNames();									\
		Gem::SInt32 GetValue();												\
		Gem::Array<Gem::SInt32> GetValues();								\
	public:																	\
		TYPE();																\
		TYPE(const TYPE::VALUES & aValue);									\
		TYPE(Gem::SInt32 aValue);											\
																			\
		inline TYPE operator=(const TYPE::VALUES & aValue)					\
		{																	\
			m_Value = aValue;												\
			return *this;													\
		}																	\
		inline TYPE operator=(int aValue)									\
		{																	\
			m_Value = (TYPE::VALUES)aValue;									\
			return *this;													\
		}																	\
		inline bool operator==(const TYPE::VALUES & aValue)					\
		{																	\
			return m_Value == aValue;										\
		}																	\
		inline bool operator==(const TYPE & aEnum)							\
		{																	\
			return m_Value == aEnum.m_Value;								\
		}																	\
		inline bool operator!=(const TYPE::VALUES & aValue)					\
		{																	\
			return m_Value != aValue;										\
		}																	\
		inline bool operator!=(const TYPE & aEnum)							\
		{																	\
			return m_Value != aEnum.m_Value;								\
		}																	\
		inline operator Gem::SInt32() const									\
		{																	\
			return m_Value;													\
		}																	\
		inline operator const char *() const								\
		{																	\
			return NAMES[(Gem::SInt32)m_Value].c_str();						\
		}																	\
		private:															\
			static const std::string NAMES[COUNT];							\


#define RENUM_CPP(TYPE,VALUES,COUNT)	TYPE::TYPE()								\
	{																				\
		m_Value = (VALUES)0;														\
	}																				\
	TYPE::TYPE(const TYPE::VALUES & aValue)											\
	{																				\
		m_Value = aValue;															\
	}																				\
	TYPE::TYPE(Gem::SInt32 aValue)													\
	{																				\
		m_Value = (VALUES)aValue;													\
	}																				\
	std::string TYPE::GetName()														\
	{																				\
		return NAMES[(Gem::SInt32)m_Value];											\
	}																				\
	Gem::Array<std::string> TYPE::GetNames()										\
	{																				\
		Gem::Array<std::string> names(COUNT);										\
		for (int i = 0; i < COUNT; i++)												\
		{																			\
			names[i] = NAMES[i];													\
		}																			\
		return names;																\
	}																				\
	Gem::SInt32 TYPE::GetValue()													\
	{																				\
		return (Gem::SInt32)m_Value;												\
	}																				\
	Gem::Array<Gem::SInt32> TYPE::GetValues()										\
	{																				\
		Gem::Array<Gem::SInt32> values(COUNT);										\
		for (int i = 0; i < COUNT; i++)												\
		{																			\
			values[i] = i;															\
		}																			\
		return values;																\
	}																				\
	const std::string TYPE::NAMES[COUNT] =											\

#endif // GEM_ENUM_H