#pragma once

#include "RE/Havok/hkVector4.h"
#include "RE/Havok/hknpBodyId.h"
#include "RE/Havok/hknpBodyCinfo.h"
#include "RE/Havok/hknpCollisionResult.h"
#include "RE/Havok/hknpMaterialId.h"
#include "RE/Bethesda/bhkCharacterController.h"

namespace RE
{
	class hknpBody;
	class hknpCollisionQueryCollector;
	class hknpShape;
	struct hknpConstraintId;
	struct hknpConstraintCinfo;

	struct hknpWorldCinfo;

	struct hknpStepInput
	{
	public:
		// members
		std::byte pad[0x20];  // TODO
	};

	struct hknpEventType
	{
	public:
		enum Enum
		{
			kContact = 3,
			kIslandActivation = 0xB,
			kBroadPhaseExit = 0xC,
			kBreakableConstraintForceExceeded = 0x16
		};
	};
	static_assert(std::is_empty_v<hknpEventType>);

	class hknpWorld
	{
	public:
		// Construction
		hknpWorld(hknpWorldCinfo& a_cinfo)
		{
			typedef hknpWorld* func_t(hknpWorld*, hknpWorldCinfo&);
			static REL::Relocation<func_t> func{ REL::ID(864328) };
			func(this, a_cinfo);
		}

		~hknpWorld()
		{
			typedef void func_t(hknpWorld*);
			static REL::Relocation<func_t> func{ REL::ID(748654) };
			func(this);
		}

		void GetCinfo(hknpWorldCinfo& a_cinfo)
		{
			using func_t = decltype(&hknpWorld::GetCinfo);
			static REL::Relocation<func_t> func{ REL::ID(624763) };
			return func(this, a_cinfo);
		}

		// Collision Queries
		void CastRay(void* a_query, hknpCollisionQueryCollector* a_collector)
		{
			using func_t = decltype(&hknpWorld::CastRay);
			static REL::Relocation<func_t> func{ REL::ID(1440166) };
			return func(this, a_query, a_collector);
		}

		void CastShape(void* a_query, void* a_queryShapeInfo, hknpCollisionQueryCollector* a_collector, hknpCollisionQueryCollector* a_startPointCollector)
		{
			using func_t = decltype(&hknpWorld::CastShape);
			static REL::Relocation<func_t> func{ REL::ID(110287) };
			return func(this, a_query, a_queryShapeInfo, a_collector, a_startPointCollector);
		}

		void GetClosestPoints(void* a_query, hkTransformf& a_transform, hknpCollisionQueryCollector* a_collector)
		{
			using func_t = decltype(&hknpWorld::GetClosestPoints);
			static REL::Relocation<func_t> func{ REL::ID(1053489) };
			return func(this, a_query, a_transform, a_collector);
		}

		void QueryAabb(void* a_query, hknpCollisionQueryCollector* a_collector)
		{
			using func_t = decltype(&hknpWorld::QueryAabb);
			static REL::Relocation<func_t> func{ REL::ID(990501) };
			return func(this, a_query, a_collector);
		}

		// Body Management
		hknpBodyId CreateBody(hknpBodyCinfo& a_cinfo, std::int32_t a_additionMode = 1, std::uint8_t a_flags = 0)
		{
			typedef hknpBodyId* func_t(hknpWorld*, hknpBodyId*, hknpBodyCinfo&, std::int32_t, std::uint8_t);
			static REL::Relocation<func_t> func{ REL::ID(72830) };
			hknpBodyId bodyId;
			func(this, &bodyId, a_cinfo, a_additionMode, a_flags);
			return bodyId;
		}

		void RemoveBodies(hknpBodyId* a_bodyIds, std::int32_t a_count, std::int32_t a_activationMode = 0)
		{
			typedef void func_t(hknpWorld*, hknpBodyId*, std::int32_t, std::int32_t);
			static REL::Relocation<func_t> func{ REL::ID(201384) };
			func(this, a_bodyIds, a_count, a_activationMode);
		}

		void DestroyBodies(hknpBodyId* a_bodyIds, std::int32_t a_count, std::int32_t a_activationMode = 0)
		{
			typedef void func_t(hknpWorld*, hknpBodyId*, std::int32_t, std::int32_t);
			static REL::Relocation<func_t> func{ REL::ID(1037327) };
			func(this, a_bodyIds, a_count, a_activationMode);
		}

		void CommitAddBodies()
		{
			using func_t = decltype(&hknpWorld::CommitAddBodies);
			static REL::Relocation<func_t> func{ REL::ID(121748) };
			return func(this);
		}

		// Body Properties
		void SetBodyTransform(hknpBodyId a_bodyId, hkTransformf& a_transform, std::int32_t a_activationBehavior = 0)
		{
			typedef void func_t(hknpWorld*, hknpBodyId, hkTransformf&, std::int32_t);
			static REL::Relocation<func_t> func{ REL::ID(367136) };
			func(this, a_bodyId, a_transform, a_activationBehavior);
		}

		void SetBodyShape(hknpBodyId a_bodyId, const hknpShape* a_shape)
		{
			typedef void func_t(hknpWorld*, hknpBodyId, const hknpShape*);
			static REL::Relocation<func_t> func{ REL::ID(531033) };
			func(this, a_bodyId, a_shape);
		}

		void SetBodyMaterial(hknpBodyId a_bodyId, hknpMaterialId a_materialId, std::int32_t a_rebuildCachesMode = 0)
		{
			typedef void func_t(hknpWorld*, hknpBodyId, hknpMaterialId, std::int32_t);
			static REL::Relocation<func_t> func{ REL::ID(50770) };
			func(this, a_bodyId, a_materialId, a_rebuildCachesMode);
		}

		void SetBodyMotionProperties(hknpBodyId a_bodyId, hknpMotionPropertiesId_Handle a_motionPropertiesId)
		{
			typedef void func_t(hknpWorld*, hknpBodyId, hknpMotionPropertiesId_Handle);
			static REL::Relocation<func_t> func{ REL::ID(275629) };
			func(this, a_bodyId, a_motionPropertiesId);
		}

		void GetBodyAabb(hknpBodyId a_bodyId, void* a_aabbOut)
		{
			typedef void func_t(hknpWorld*, hknpBodyId, void*);
			static REL::Relocation<func_t> func{ REL::ID(249572) };
			func(this, a_bodyId, a_aabbOut);
		}

		// Velocity & Impulse
		void SetBodyLinearVelocity(hknpBodyId a_bodyId, hkVector4f& a_velocity)
		{
			typedef void func_t(hknpWorld*, hknpBodyId, hkVector4f&);
			static REL::Relocation<func_t> func{ REL::ID(1082668) };
			func(this, a_bodyId, a_velocity);
		}

		void SetBodyAngularVelocity(hknpBodyId a_bodyId, hkVector4f& a_velocity)
		{
			typedef void func_t(hknpWorld*, hknpBodyId, hkVector4f&);
			static REL::Relocation<func_t> func{ REL::ID(1068862) };
			func(this, a_bodyId, a_velocity);
		}

		void SetBodyVelocity(hknpBodyId a_bodyId, hkVector4f& a_linearVelocity, hkVector4f& a_angularVelocity)
		{
			typedef void func_t(hknpWorld*, hknpBodyId, hkVector4f&, hkVector4f&);
			static REL::Relocation<func_t> func{ REL::ID(868461) };
			func(this, a_bodyId, a_linearVelocity, a_angularVelocity);
		}

		void GetBodyAngularVelocity(hknpBodyId a_bodyId, hkVector4f& a_velocityOut)
		{
			typedef void func_t(hknpWorld*, hknpBodyId, hkVector4f&);
			static REL::Relocation<func_t> func{ REL::ID(405369) };
			func(this, a_bodyId, a_velocityOut);
		}

		void ApplyBodyLinearImpulse(hknpBodyId a_bodyId, hkVector4f& a_impulse)
		{
			typedef void func_t(hknpWorld*, hknpBodyId, hkVector4f&);
			static REL::Relocation<func_t> func{ REL::ID(654985) };
			func(this, a_bodyId, a_impulse);
		}

		void ApplyBodyAngularImpulse(hknpBodyId a_bodyId, hkVector4f& a_impulse)
		{
			typedef void func_t(hknpWorld*, hknpBodyId, hkVector4f&);
			static REL::Relocation<func_t> func{ REL::ID(1345477) };
			func(this, a_bodyId, a_impulse);
		}

		void ApplyBodyImpulseAt(hknpBodyId a_bodyId, hkVector4f& a_impulse, hkVector4f& a_point)
		{
			typedef void func_t(hknpWorld*, hknpBodyId, hkVector4f&, hkVector4f&);
			static REL::Relocation<func_t> func{ REL::ID(800106) };
			func(this, a_bodyId, a_impulse, a_point);
		}

		void ComputeHardKeyFrame(hknpBodyId a_bodyId, float* a_targetPos, float* a_targetRot, float a_invDeltaTime, float* a_linVelOut, float* a_angVelOut)
		{
			typedef void func_t(hknpWorld*, hknpBodyId, float*, float*, float, float*, float*);
			static REL::Relocation<func_t> func{ REL::ID(865502) };
			func(this, a_bodyId, a_targetPos, a_targetRot, a_invDeltaTime, a_linVelOut, a_angVelOut);
		}

		// Activation
		void ActivateBody(hknpBodyId a_bodyId)
		{
			typedef void func_t(hknpWorld*, hknpBodyId);
			static REL::Relocation<func_t> func{ REL::ID(904571) };
			func(this, a_bodyId);
		}

		// Constraints
		std::uint32_t CreateConstraint(hknpConstraintCinfo& a_cinfo)
		{
			typedef std::uint32_t func_t(hknpWorld*, hknpConstraintCinfo&);
			static REL::Relocation<func_t> func{ REL::ID(441087) };
			return func(this, a_cinfo);
		}

		void DestroyConstraints(std::uint32_t* a_constraintIds, std::int32_t a_count)
		{
			typedef void func_t(hknpWorld*, std::uint32_t*, std::int32_t);
			static REL::Relocation<func_t> func{ REL::ID(334340) };
			func(this, a_constraintIds, a_count);
		}

		void DisableConstraint(std::uint32_t a_constraintId)
		{
			typedef void func_t(hknpWorld*, std::uint32_t);
			static REL::Relocation<func_t> func{ REL::ID(320495) };
			func(this, a_constraintId);
		}

		void EnableConstraint(std::uint32_t a_constraintId, std::int32_t a_activationMode = 0)
		{
			typedef void func_t(hknpWorld*, std::uint32_t, std::int32_t);
			static REL::Relocation<func_t> func{ REL::ID(399921) };
			func(this, a_constraintId, a_activationMode);
		}

		// Events
		void* GetEventSignal(hknpEventType::Enum a_eventType)
		{
			typedef void* func_t(hknpWorld*, std::int16_t);
			static REL::Relocation<func_t> func{ REL::ID(1029853) };
			return func(this, static_cast<std::int16_t>(a_eventType));
		}

		void* GetEventSignalForBody(hknpEventType::Enum a_eventType, hknpBodyId a_bodyId)
		{
			typedef void* func_t(hknpWorld*, std::int32_t, std::uint32_t);
			static REL::Relocation<func_t> func{ REL::ID(497909) };
			return func(this, static_cast<std::int32_t>(a_eventType), a_bodyId.value);
		}

		// Simulation
		void StepCollide(hknpStepInput& a_input, void* a_taskQueue, void*& a_solverData)
		{
			typedef void func_t(hknpWorld*, hknpStepInput&, void*, void*&);
			static REL::Relocation<func_t> func{ REL::ID(687604) };
			func(this, a_input, a_taskQueue, a_solverData);
		}

		void ShiftBroadPhase(hkVector4f& a_offset, hkVector4f& a_offset2, void* a_bodyIdArray)
		{
			typedef void func_t(hknpWorld*, hkVector4f&, hkVector4f&, void*);
			static REL::Relocation<func_t> func{ REL::ID(218299) };
			func(this, a_offset, a_offset2, a_bodyIdArray);
		}

		// Key offsets (use reinterpret_cast from 'this' to access):
		// +0x20  = body array pointer (hknpBody*, stride 0x90)
		// +0xE0  = motion array pointer (stride 0x80)
		// +0x128 = constraint array pointer (stride 0x38)
		// +0x178 = collision query dispatcher
		// +0x5C8 = simulation island manager
		// +0x648 = event dispatcher (hknpEventDispatcher*)
		// +0x690 = read/write lock (critical section)
	};
}
