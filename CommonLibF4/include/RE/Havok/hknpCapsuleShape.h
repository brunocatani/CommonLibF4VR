#pragma once

#include "RE/Havok/hkVector4.h"
#include "RE/Havok/hknpShape.h"

namespace RE
{
	class hknpConvexShape :
		public hknpShape  // 00
	{
	public:
		// members
		std::uint32_t pad30;  // 30
		std::uint32_t pad34;  // 34
		std::uint32_t pad38;  // 38
		std::uint32_t pad3C;  // 3C
	};
	static_assert(sizeof(hknpConvexShape) == 0x40);

	class hknpCapsuleShape :
		public hknpConvexShape  // 00
	{
	public:
		static hknpCapsuleShape* CreateCapsuleShape(hkVector4f& a_start, hkVector4f& a_end, float a_radius)
		{
			using func_t = decltype(&hknpCapsuleShape::CreateCapsuleShape);
			static REL::Relocation<func_t> func{ REL::ID(1316723) };
			return func(a_start, a_end, a_radius);
		}

		void Init(hkVector4f& a_start, hkVector4f& a_end)
		{
			using func_t = decltype(&hknpCapsuleShape::Init);
			static REL::Relocation<func_t> func{ REL::ID(647475) };
			return func(this, a_start, a_end);
		}

		// members
		std::uint64_t pad40;  // 40
		std::uint64_t pad48;  // 48
		hkVector4f    a;      // 50 - start point
		hkVector4f    b;      // 60 - end point
	};
	static_assert(sizeof(hknpCapsuleShape) == 0x70);
}
