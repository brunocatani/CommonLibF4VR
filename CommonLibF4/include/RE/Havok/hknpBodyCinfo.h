#pragma once

#include "RE/Havok/hkRefPtr.h"
#include "RE/Havok/hkVector4.h"
#include "RE/Havok/hknpBodyId.h"
#include "RE/Havok/hknpMaterialId.h"
#include "RE/Havok/hknpShape.h"

namespace RE
{
	struct hknpMotionIdDiscriminant;
	struct hknpMotionPropertiesIdDiscriminant;
	struct hknpBodyQualityIdDiscriminant;

	struct hknpMotionId :
		public hkHandle<std::uint32_t, 0x7FFF'FFFF, hknpMotionIdDiscriminant>
	{
	public:
	};
	static_assert(sizeof(hknpMotionId) == 0x4);

	struct hknpMotionPropertiesId_Handle :
		public hkHandle<std::uint16_t, 0xFF, hknpMotionPropertiesIdDiscriminant>
	{
	public:
	};
	static_assert(sizeof(hknpMotionPropertiesId_Handle) == 0x2);

	struct hknpBodyQualityId :
		public hkHandle<std::uint8_t, 0xFF, hknpBodyQualityIdDiscriminant>
	{
	public:
	};
	static_assert(sizeof(hknpBodyQualityId) == 0x1);

	struct hknpBodyCinfo
	{
	public:
		hknpBodyCinfo()
		{
			typedef hknpBodyCinfo* func_t(hknpBodyCinfo*);
			static REL::Relocation<func_t> func{ REL::ID(718403) };
			func(this);
		}

		// Layout verified via Ghidra decompilation of constructor (VR 0x141561dd0)
		// and crash analysis confirming name at +0x20, shape hkRefPtr at +0x58.
		// members
		std::uint64_t              reserved00;             // 00 - set to 0 by constructor
		hknpBodyId                 bodyId;                 // 08 - 0x7FFFFFFF = auto-assign
		hknpMotionId               motionId;               // 0C - 0x7FFFFFFF = auto-assign
		hknpMotionPropertiesId_Handle motionPropertiesId;  // 10 - 0xFF = default -> DYNAMIC
		hknpMaterialId             materialId;             // 12
		std::uint32_t              collisionFilterInfo;    // 14
		std::uint32_t              pad18;                  // 18
		std::uint32_t              collisionLookAheadDistance; // 1C
		const char*                name;                   // 20 - body name string (for debugging)
		std::uintptr_t             userData;               // 28
		hkVector4f                 position;               // 30 - world-space position
		hkVector4f                 orientation;             // 40 - quaternion {x,y,z,w}, identity = {0,0,0,1}
		std::uint8_t               qualityId;              // 50
		std::uint8_t               pad51[7];               // 51
		hkRefPtr<const hknpShape>  shape;                  // 58
	};
	static_assert(sizeof(hknpBodyCinfo) == 0x60);
}
