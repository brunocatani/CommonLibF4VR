#pragma once

#include "RE/Havok/hkRefPtr.h"
#include "RE/Havok/hkVector4.h"
#include "RE/Havok/hknpBodyId.h"
#include "RE/Havok/hknpMaterialId.h"
#include "RE/Havok/hknpShape.h"
#include "RE/Bethesda/bhkCharacterController.h"

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

		// members
		hkRefPtr<const hknpShape>  shape;                // 00
		hknpBodyId                 bodyId;                // 08 - 0x7FFFFFFF = auto-assign
		hknpMotionId               motionId;              // 0C - 0x7FFFFFFF = auto-assign
		hknpMotionPropertiesId_Handle motionPropertiesId; // 10 - 0xFF = default -> DYNAMIC
		hknpMaterialId             materialId;            // 12
		std::uint32_t              collisionFilterInfo;   // 14
		std::uint32_t              pad18;                 // 18
		std::uint32_t              pad1C;                 // 1C
		hkTransformf              transform;              // 20
		std::uintptr_t             userData;              // 50
		std::uint64_t              pad58;                 // 58
	};
	static_assert(sizeof(hknpBodyCinfo) == 0x60);
}
