#pragma once

#include "RE/NetImmerse/NiObject.h"
#include "RE/NetImmerse/NiPoint.h"

namespace RE
{
	struct bhkPickData;
	struct hknpWorldCinfo;
	class bhkIWorldStepListener;
	class hknpWorld;

	class bhkWorld :
		public NiObject  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI::bhkWorld };
		static constexpr auto VTABLE{ VTABLE::bhkWorld };
		static constexpr auto Ni_RTTI{ Ni_RTTI::bhkWorld };

		// add
		virtual bool Update(std::uint32_t a_updateFlags);  // 28
		virtual void Init(const hknpWorldCinfo& a_info);   // 29

		static bool RemoveObjects(NiAVObject* a_object, bool a_recurse, bool a_force)
		{
			using func_t = decltype(&RemoveObjects);
			static REL::Relocation<func_t> func{ REL::RelocationID(1514984, 2277721) };
			return func(a_object, a_recurse, a_force);
		}

		bool PickObject(bhkPickData& a_pickData)
		{
			using func_t = decltype(&bhkWorld::PickObject);
			static REL::Relocation<func_t> func{ REL::ID(547249) };
			return func(this, a_pickData);
		}

		void AddPhysicsStepListener(bhkIWorldStepListener& a_listener)
		{
			using func_t = decltype(&bhkWorld::AddPhysicsStepListener);
			static REL::Relocation<func_t> func{ REL::ID(137330) };
			return func(this, a_listener);
		}

		void SetDeltaTime(float a_deltaTime, bool a_param2, bool a_param3)
		{
			using func_t = decltype(&bhkWorld::SetDeltaTime);
			static REL::Relocation<func_t> func{ REL::ID(12890) };
			return func(this, a_deltaTime, a_param2, a_param3);
		}

		void GetGravity()
		{
			using func_t = decltype(&bhkWorld::GetGravity);
			static REL::Relocation<func_t> func{ REL::ID(386279) };
			return func(this);
		}

		void SetMotion(NiAVObject* a_object, hknpMotionPropertiesId::Preset a_type, bool a_param3, bool a_param4, bool a_param5)
		{
			using func_t = decltype(&bhkWorld::SetMotion);
			static REL::Relocation<func_t> func{ REL::ID(357289) };
			return func(this, a_object, a_type, a_param3, a_param4, a_param5);
		}

		void EnableCollision(NiAVObject* a_object, bool a_enable, bool a_param3, bool a_param4)
		{
			using func_t = decltype(&bhkWorld::EnableCollision);
			static REL::Relocation<func_t> func{ REL::ID(50037) };
			return func(this, a_object, a_enable, a_param3, a_param4);
		}

		void SetOrigin(NiPoint3& a_origin)
		{
			using func_t = decltype(&bhkWorld::SetOrigin);
			static REL::Relocation<func_t> func{ REL::ID(54519) };
			return func(this, a_origin);
		}

		// members
		std::byte pad[0x180 - 0x10];  // 0x10 - TODO: map remaining members
	};
	static_assert(sizeof(bhkWorld) == 0x180);
}
