#pragma once

// hknpMotion — Havok 2014 (New Physics) motion data
//
// Each motion lives in a flat array inside hknpWorld (world+0xE0, stride 0x80).
// Motions store the actual world-space position, orientation, and velocity of bodies.
// Multiple bodies can share one motion (compound objects).
//
// Key insight: body position is NOT at body+0x00 (that's AABB data).
// Real position lives here in the motion struct at offset +0x00.
//
// Motion index 0 is the "shared static motion" — all static bodies point here.
// Dynamic/keyframed bodies have their own motion slot (allocated via AllocateMotion()).
//
// Offsets RE'd via Ghidra on Fallout4VR.exe.unpacked.exe.
// Confirmed by reading actual motion data in HIGGS-FO4VR contact detection.
//
// Coordinate space: all positions/velocities are in Havok space (1 unit = 70 game units).
// Use HavokUtils::kHavokScale (1/70) to convert to game space.
//
// Usage:
//   // Get motion for a body
//   auto* motionArray = *reinterpret_cast<uint8_t**>(
//       reinterpret_cast<uintptr_t>(hknpWorld) + 0xE0);
//   auto* motion = reinterpret_cast<RE::hknpMotion*>(
//       motionArray + body.motionIndex * sizeof(RE::hknpMotion));
//
//   // Read world position (Havok space)
//   float worldX = motion->position.x;  // multiply by 70.0 for game units
//
//   // Read velocity
//   float speed = motion->linearVelocity.Length();
//
//   // Check if motion is active (not sleeping)
//   bool active = (motion->spaceSplitterWeight > 0.0f);

#include "RE/Havok/hkVector4.h"

namespace RE
{
	/// hknpMotion — per-motion data stored in the world's motion array.
	///
	/// Memory layout: 0x80 bytes per motion (stride confirmed via Ghidra).
	/// The motion array is at hknpWorld+0xE0.
	///
	/// Motion index 0 is reserved for the "shared static motion" (all static
	/// bodies reference this). Custom bodies need their own motion slot
	/// allocated with hknpWorld::AllocateMotion().
	struct hknpMotion
	{
	public:
		// +0x00: World-space position (Havok coordinates, divide by kHavokScale for game units).
		// This is the CENTER OF MASS position, not necessarily the visual origin.
		// w component may contain encoded data — treat as padding.
		hkVector4f position;          // 00

		// +0x10: Orientation quaternion (x, y, z, w).
		// Normalized quaternion representing the body's current rotation.
		hkVector4f orientation;       // 10

		// +0x20: Linear velocity in Havok space (units/second).
		// For keyframed bodies, this is set via ComputeHardKeyFrame() each frame.
		hkVector4f linearVelocity;    // 20

		// +0x30: Angular velocity in Havok space (radians/second).
		// For grabbed objects, set to zero to prevent gyroscope spinning.
		hkVector4f angularVelocity;   // 30

		// +0x40: Previous-frame position (for interpolation / CCD).
		hkVector4f previousPosition;  // 40

		// +0x50: Previous-frame orientation.
		hkVector4f previousOrientation;  // 50

		// +0x60: Inverse mass and inertia factors.
		// x = inverse mass (0 = infinite mass / static)
		// y,z,w = inverse inertia tensor diagonal elements
		hkVector4f inverseMassAndInertia;  // 60

		// +0x70: Additional motion properties
		float spaceSplitterWeight;     // 70 — island/deactivation weight (0 = sleeping)
		float maxLinearAccelerationDistancePerStep;  // 74
		float maxRotationToPreventTunneling;         // 78
		float timeFactor;              // 7C — time scale (1.0 = normal, 0.0 = frozen)
	};
	static_assert(sizeof(hknpMotion) == 0x80);

	/// Helper: stride between motions in the world's motion array.
	/// Use this when doing pointer arithmetic on the raw motion array.
	inline constexpr std::size_t kHknpMotionStride = 0x80;

	/// Helper: stride between bodies in the world's body array.
	inline constexpr std::size_t kHknpBodyStride = 0x90;
}
