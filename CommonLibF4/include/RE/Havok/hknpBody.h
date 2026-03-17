#pragma once

// hknpBody — Havok 2014 (New Physics) rigid body descriptor
//
// Each body lives in a flat array inside hknpWorld (world+0x20, stride 0x90 per body).
// Bodies reference motions (separate array at world+0xE0, stride 0x80) via motionIndex.
//
// Key relationships:
//   hknpBody -> hknpMotion  (via motionIndex)
//   hknpBody -> hknpShape   (via shape pointer)
//   hknpBody -> NiAVObject  (via userData, when valid — see validation notes below)
//
// ┌─────────────────────────────────────────────────────────────────────────┐
// │  IMPORTANT: userData validation                                        │
// │  body.userData is NOT always a TESObjectREFR* or even a valid pointer. │
// │  FOIslandActivationListener dereferences it unconditionally, so if you │
// │  create bodies, set userData = 0 unless you have a valid pointer.      │
// │  Before dereferencing: check alignment (% 8 == 0), pointer range       │
// │  (0x10000..0x7FFFFFFFFFFF), and vtable validity.                       │
// └─────────────────────────────────────────────────────────────────────────┘
//
// Offsets RE'd via Ghidra on Fallout4VR.exe.unpacked.exe and confirmed in
// HIGGS-FO4VR contact detection (body scan of ~2047 bodies per cell).
//
// Usage:
//   // Access body array from hknpWorld
//   auto* bodyArray = *reinterpret_cast<RE::hknpBody**>(
//       reinterpret_cast<uintptr_t>(hknpWorld) + 0x20);
//   RE::hknpBody& body = bodyArray[bodyId.value];
//
//   // Read position from motion (NOT from body — body+0x00 is AABB data)
//   auto* motionArray = *reinterpret_cast<uint8_t**>(
//       reinterpret_cast<uintptr_t>(hknpWorld) + 0xE0);
//   float* pos = reinterpret_cast<float*>(motionArray + body.motionIndex * 0x80);
//   // pos[0]=x, pos[1]=y, pos[2]=z, pos[3]=w (Havok space, scale = 1/70)

#include "RE/Havok/hknpBodyId.h"
#include "RE/Havok/hknpMaterialId.h"

namespace RE
{
	class hknpShape;

	/// hknpBody — per-body data stored in the world's body array.
	///
	/// Memory layout: 0x90 bytes per body (stride confirmed via Ghidra).
	/// The body array is at hknpWorld+0x20 and indexed directly by hknpBodyId::value.
	///
	/// Bodies come in three motion types (controlled by motionPropertiesId):
	///   STATIC (0)    — never moves, motionIndex typically 0 (shared static motion)
	///   DYNAMIC (1)   — simulated by solver, affected by gravity and impulses
	///   KEYFRAMED (2) — position set externally (e.g., VR controller tracking)
	///
	/// To check if a body is dynamic: motionPropertiesId & 0xFF == 1
	/// To check if a body is static:  motionIndex == 0 (shared static motion slot)
	struct hknpBody
	{
	public:
		// +0x00: AABB min (NOT world position — common mistake!)
		// The actual world position is stored in the MOTION struct, not here.
		float aabbMin[4];  // 00 — axis-aligned bounding box minimum (Havok space)

		// +0x10: AABB max
		float aabbMax[4];  // 10 — axis-aligned bounding box maximum (Havok space)

		// +0x20: Broadphase handle / internal Havok data
		std::uint64_t broadphaseId;  // 20

		// +0x28: Shape pointer
		const hknpShape* shape;  // 28 — collision shape (hknpCapsuleShape, etc.)

		// +0x30: Collision filter info (layer bits, group, etc.)
		std::uint32_t collisionFilterInfo;  // 30

		// +0x34: Various packed flags
		std::uint16_t flags;       // 34
		std::uint16_t flagsHigh;   // 36

		// +0x38: Material ID for this body
		hknpMaterialId materialId;  // 38

		// +0x3A: Quality ID (affects solver iterations)
		std::uint8_t qualityId;    // 3A
		std::uint8_t pad3B;        // 3B
		std::uint32_t pad3C;       // 3C

		// +0x40: User data — often a TESObjectREFR* but MUST be validated before use.
		// Set to 0 for custom bodies (hand colliders, etc.) to avoid crashes in
		// FOIslandActivationListener which dereferences this unconditionally.
		std::uintptr_t userData;   // 40

		// +0x48..0x67: Internal Havok data (collision caches, etc.)
		std::uint8_t pad48[0x20];  // 48

		// +0x68: Motion index — indexes into the motion array (world+0xE0, stride 0x80).
		// motionIndex == 0 means "shared static motion" (body is static).
		// IMPORTANT: Must bounds-check (> 4096 likely invalid / garbage).
		// Compound objects share the same motionId (e.g., bodies 1593-1597 all use motionId=165).
		std::uint32_t motionIndex;  // 68

		// +0x6C: Body ID (matches the array index)
		hknpBodyId bodyId;          // 6C

		// +0x70: More internal data
		std::uint16_t pad70;        // 70

		// +0x72: Motion properties ID — determines physics behavior.
		// Changes dynamically at runtime (values seen: 259, 515, 770, 1282, etc.)
		// Lower byte is the preset: 0=STATIC, 1=DYNAMIC, 2=KEYFRAMED
		// Use (motionPropertiesId & 0xFF) to get the base preset.
		std::uint16_t motionPropertiesId;  // 72

		// +0x74..0x8F: Remaining internal fields
		std::uint8_t pad74[0x1C];  // 74
	};
	static_assert(sizeof(hknpBody) == 0x90);

	/// Helper to check if a body is dynamic (affected by physics simulation)
	inline bool IsBodyDynamic(const hknpBody& body)
	{
		return (body.motionPropertiesId & 0xFF) == 1;
	}

	/// Helper to check if a body is keyframed (position set externally)
	inline bool IsBodyKeyframed(const hknpBody& body)
	{
		return (body.motionPropertiesId & 0xFF) == 2;
	}

	/// Helper to check if a body is static (never moves)
	inline bool IsBodyStatic(const hknpBody& body)
	{
		return body.motionIndex == 0;
	}
}
