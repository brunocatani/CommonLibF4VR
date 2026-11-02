#pragma once

#include "RE/NetImmerse/NiBound.h"
#include "RE/NetImmerse/NiFlags.h"
#include "RE/NetImmerse/NiObjectNET.h"
#include "RE/NetImmerse/NiSmartPointer.h"
#include "RE/NetImmerse/NiTransform.h"

namespace RE
{
	class NiAlphaProperty;
	class NiCollisionObject;
	class NiCullingProcess;
	class NiNode;
	class NiUpdateData;
	class PerformOpFunc;

	class __declspec(novtable) NiAVObject :
		public NiObjectNET  // 000
	{
	public:
		static constexpr auto RTTI{ RTTI::NiAVObject };
		static constexpr auto VTABLE{ VTABLE::NiAVObject };
		static constexpr auto Ni_RTTI{ Ni_RTTI::NiAVObject };

		// FO4VR's vtable has three more entries than flat Fallout 4 before GetObjectByName, so
		// the slot numbers in the declarations below are flat ones. These are the FO4VR slots,
		// for REL::guarded_read_vfunc or REL::RelocateVirtual.
		static constexpr std::size_t VR_GetObjectByNameSlot{ 0x31 };
		static constexpr std::size_t VR_UpdateWorldDataSlot{ 0x37 };

		// Address Library IDs of NiAVObject's own implementations. Compare one with an
		// object's vtable entry to learn whether the object keeps the base behaviour.
		// FO4VR: GetObjectByName 0x141C233F0, UpdateWorldData 0x141C23740.
		static constexpr REL::ID GetObjectByNameID{ 1330146 };
		static constexpr REL::ID UpdateWorldDataID{ 850280 };

		/// True when FO4VR's NiAVObject GetObjectByName and UpdateWorldData start with the
		/// expected code.
		[[nodiscard]] static bool VRCodeMatches()
		{
			static constexpr std::uint8_t getObjectByName[]{ 0x48, 0x8B, 0x12, 0x33, 0xC0, 0x48 };
			static constexpr std::uint8_t updateWorldData[]{ 0x40, 0x53, 0x48, 0x83, 0xEC, 0x60 };
			return REL::code_matches(GetObjectByNameID.address(), getObjectByName) &&
			       REL::code_matches(UpdateWorldDataID.address(), updateWorldData);
		}

		NiAVObject();
		virtual ~NiAVObject();  // NOLINT(modernize-use-override) 00

		// add
		virtual void        UpdateControllers(NiUpdateData& a_data);                                                            // 28
		virtual void        PerformOp(PerformOpFunc& a_operation);                                                              // 29
		virtual void        AttachProperty([[maybe_unused]] NiAlphaProperty* a_prop) { return; }                                // 2A
		virtual void        SetMaterialNeedsUpdate(bool) { return; }                                                            // 2B
		virtual void        SetDefaultMaterialNeedsUpdateFlag(bool) { return; }                                                 // 2C
		virtual void        SetAppCulled(bool a_appCulled);                                                                     // 2D
		virtual NiAVObject* GetObjectByName(const BSFixedString& a_name) { return name == a_name ? this : nullptr; }            // 2E
		virtual void        SetSelectiveUpdateFlags(bool& a_selectiveUpdate, bool a_selectiveUpdateTransforms, bool& a_rigid);  // 2F
		virtual void        UpdateDownwardPass(NiUpdateData& a_data, std::uint32_t a_flags);                                    // 30
		virtual void        UpdateSelectedDownwardPass(NiUpdateData& a_data, std::uint32_t a_flags);                            // 31
		virtual void        UpdateRigidDownwardPass(NiUpdateData& a_data, std::uint32_t a_flags);                               // 32

		void UpdateWorldBound()  // 33
		{
			if (REL::Module::IsVR())
				REL::RelocateVirtual<decltype(&NiAVObject::UpdateWorldBound)>(0x33, 0x33, this);
		}

		void UpdateWorldData(NiUpdateData* a_data)  // 34
		{
			REL::RelocateVirtual<decltype(&NiAVObject::UpdateWorldData)>(0x34, 0x37, this, a_data);
		}

		void UpdateTransformAndBounds(NiUpdateData& a_data)  // 35
		{
			REL::RelocateVirtual<decltype(&NiAVObject::UpdateTransformAndBounds)>(0x35, 0x38, this, a_data);
		}

		void UpdateTransforms(NiUpdateData& a_data)  // 36
		{
			if (REL::Module::IsVR())
				REL::RelocateVirtual<decltype(&NiAVObject::UpdateTransforms)>(0x36, 0x39, this, a_data);
			else
				UpdateWorldData(std::addressof(a_data));
		}

		void PreAttachUpdate(NiNode* a_eventualParent, NiUpdateData& a_data)  // 37
		{
			REL::RelocateVirtual<decltype(&NiAVObject::PreAttachUpdate)>(0x3, 0x0, this, a_eventualParent, a_data);
		}

		void PostAttachUpdate()  // 38
		{
			REL::RelocateVirtual<decltype(&NiAVObject::PostAttachUpdate)>(0x3, 0x0, this);
		}

		void OnVisible([[maybe_unused]] NiCullingProcess& a_culler) { return; }  // 39

		F4_HEAP_REDEFINE_ALIGNED_NEW(NiAVObject);

		[[nodiscard]] bool          GetAppCulled() const noexcept { return flags.flags & 1; }
		[[nodiscard]] std::uint64_t GetFlags() const noexcept { return flags.flags; }
		[[nodiscard]] bool          ShadowCaster() const noexcept { return ~(flags.flags >> 40) & 1; }
		void                        CullGeometry(bool a_cull);
		void                        CullNode(bool a_cull);
		void                        Update(NiUpdateData& a_data);

		// members
		NiNode*                             parent{ nullptr };          // 027
		NiTransform                         local;                      // 030
		NiTransform                         world;                      // 070
		NiBound                             worldBound;                 // 0B0
		NiTransform                         previousWorld;              // 0C0
		NiPointer<NiCollisionObject>        collisionObject;            // 100
		NiTFlags<std::uint64_t, NiAVObject> flags;                      // 108
		std::uintptr_t                      userData{ 0 };              // 110
		float                               fadeAmount{ 1.0F };         // 118
		std::int8_t                         multType{ 0 };              // 11C
		std::int8_t                         meshLODFadingLevel{ 0 };    // 11D
		std::int8_t                         currentMeshLODLevel{ 0 };   // 11E
		std::int8_t                         previousMeshLODLevel{ 0 };  // 11F
	};
	static_assert(sizeof(NiAVObject) == 0x120);
}
