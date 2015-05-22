#ifndef GEM_REFLECTION_MEMBER_FLAGS_H
#define GEM_REFLECTION_MEMBER_FLAGS_H

namespace Gem
{
	namespace Reflection
	{
		/**
		* Defines flags for members.
		*/
		enum class MemberFlags
		{
			Empty = 0,
			Public = 1,
			Protected = 2,
			Private = 4
		};
	}
}

#endif