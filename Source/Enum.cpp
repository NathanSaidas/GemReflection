#include "Enum.h"

namespace Gem
{
	RDEFINE_ENUM(Enum)

	std::string Enum::GetName()
	{
		return "";
	}
	Array<std::string> Enum::GetNames()
	{
		return Array<std::string>();
	}
	SInt32 Enum::GetValue()
	{
		return 0;
	}
	Array<SInt32> Enum::GetValues()
	{
		return Array<SInt32>();
	}
	std::string Enum::GetName(Enum * aEnum)
	{
		if (aEnum != nullptr)
		{
			return aEnum->GetName();
		}
		return "";
	}
	Array<std::string> Enum::GetNames(Enum * aEnum)
	{
		if (aEnum != nullptr)
		{
			return aEnum->GetNames();
		}
		return Array<std::string>();
	}
	SInt32 Enum::GetValue(Enum * aEnum)
	{
		if (aEnum != nullptr)
		{
			return aEnum->GetValue();
		}
		return 0;
	}
	Array<SInt32> Enum::GetValues(Enum * aEnum)
	{
		if (aEnum != nullptr)
		{
			return aEnum->GetValues();
		}
		return Array<SInt32>();
	}

	bool Enum::IsValid(Enum * aEnum)
	{
		if (aEnum != nullptr)
		{
			return aEnum->GetValue() != InvalidEnum();
		}
		return false;
	}

	int Enum::InvalidEnum()
	{
		return -1;
	}

	std::string Enum::ToString()
	{
		return GetName();
	}

}