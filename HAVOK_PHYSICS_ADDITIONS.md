# Havok Physics API Additions for CommonLibF4VR

All addresses confirmed via Ghidra RE on `Fallout4VR.exe.unpacked.exe`. REL::IDs verified against `fo4_database.csv`.

## New Headers Created

### `RE/Havok/hknpWorld.h`
Complete hknpWorld class with 30+ methods wrapping REL::ID-based relocations:

**Collision Queries:**
- `CastRay(query, collector)` — REL::ID(1440166) — ray cast against world
- `CastShape(query, shapeInfo, collector, startCollector)` — REL::ID(110287) — shape sweep (= linearCast in Havok 2014)
- `GetClosestPoints(query, transform, collector)` — REL::ID(1053489)
- `QueryAabb(query, collector)` — REL::ID(990501)

**Body Management:**
- `CreateBody(cinfo, additionMode, flags)` — REL::ID(72830) — returns hknpBodyId
- `RemoveBodies(bodyIds, count, activationMode)` — REL::ID(201384)
- `DestroyBodies(bodyIds, count, activationMode)` — REL::ID(1037327)
- `CommitAddBodies()` — REL::ID(121748)

**Body Properties:**
- `SetBodyTransform(bodyId, transform, activationBehavior)` — REL::ID(367136)
- `SetBodyShape(bodyId, shape)` — REL::ID(531033)
- `SetBodyMaterial(bodyId, materialId, rebuildMode)` — REL::ID(50770)
- `SetBodyMotionProperties(bodyId, motionPropertiesId)` — REL::ID(275629)
- `GetBodyAabb(bodyId, aabbOut)` — REL::ID(249572)

**Velocity & Impulse:**
- `SetBodyLinearVelocity(bodyId, velocity)` — REL::ID(1082668)
- `SetBodyAngularVelocity(bodyId, velocity)` — REL::ID(1068862)
- `SetBodyVelocity(bodyId, linVel, angVel)` — REL::ID(868461)
- `GetBodyAngularVelocity(bodyId, velocityOut)` — REL::ID(405369)
- `ApplyBodyLinearImpulse(bodyId, impulse)` — REL::ID(654985)
- `ApplyBodyAngularImpulse(bodyId, impulse)` — REL::ID(1345477)
- `ApplyBodyImpulseAt(bodyId, impulse, point)` — REL::ID(800106) — point impulse for throw
- `ComputeHardKeyFrame(bodyId, targetPos, targetRot, invDt, linVelOut, angVelOut)` — REL::ID(865502) — sync keyframed body to VR controller

**Activation:**
- `ActivateBody(bodyId)` — REL::ID(904571)

**Constraints:**
- `CreateConstraint(cinfo)` — REL::ID(441087)
- `DestroyConstraints(constraintIds, count)` — REL::ID(334340)
- `DisableConstraint(constraintId)` — REL::ID(320495)
- `EnableConstraint(constraintId, activationMode)` — REL::ID(399921)

**Events:**
- `GetEventSignal(eventType)` — REL::ID(1029853) — event type 3 = contact events
- `GetEventSignalForBody(eventType, bodyId)` — REL::ID(497909) — per-body events

**Simulation:**
- `StepCollide(input, taskQueue, solverData)` — REL::ID(687604)
- `ShiftBroadPhase(offset, offset2, bodyIdArray)` — REL::ID(218299)
- Constructor REL::ID(864328), Destructor REL::ID(748654), GetCinfo REL::ID(624763)

**Key structural offsets (documented in comments):**
- `+0x20` = body array (hknpBody*, stride 0x90)
- `+0xE0` = motion array (stride 0x80)
- `+0x128` = constraint array (stride 0x38)
- `+0x178` = collision query dispatcher (vtable: +0x60=castRay, +0x68=castShape, +0x70=queryPoint, +0x78=getClosestPoints)
- `+0x648` = event dispatcher (hknpEventDispatcher*)
- `+0x690` = read/write lock

### `RE/Havok/hknpBodyCinfo.h`
Body creation info struct (0x60 bytes), confirmed via Ghidra decompilation of constructor at REL::ID(718403):

```
+0x00 = hkRefPtr<const hknpShape> shape
+0x08 = hknpBodyId bodyId (0x7FFFFFFF = auto-assign)
+0x0C = hknpMotionId motionId (0x7FFFFFFF = auto-assign)
+0x10 = hknpMotionPropertiesId_Handle motionPropertiesId (0xFF = default -> DYNAMIC)
+0x12 = hknpMaterialId materialId
+0x14 = uint32_t collisionFilterInfo
+0x20 = hkTransformf transform
+0x50 = uintptr_t userData
```

Also defines: `hknpMotionId`, `hknpMotionPropertiesId_Handle`, `hknpBodyQualityId`.

### `RE/Havok/hknpCapsuleShape.h`
Capsule shape for hand colliders (0x70 bytes), inherits hknpConvexShape -> hknpShape:

- `CreateCapsuleShape(start, end, radius)` — REL::ID(1316723) — static factory, allocates 0x70 bytes
- `Init(start, end)` — REL::ID(647475) — sets type=0x1C3, builds 8-vertex convex hull

```
+0x14 = float radius
+0x50 = hkVector4f a (start point)
+0x60 = hkVector4f b (end point)
```

Bethesda wrapper with auto-scaling + 10-entry cache: `bhkCharacterControllerShapeManager::GetCapsuleShape` REL::ID(1526865).

## Extended Existing Headers

### `RE/Bethesda/BSHavok.h` — bhkWorld
Added 7 methods to the existing stub:

- `PickObject(bhkPickData&)` — REL::ID(547249) — main raycast entry, calls hknpWorld::castRay internally
- `AddPhysicsStepListener(bhkIWorldStepListener&)` — REL::ID(137330) — listener array at bhkWorld+0x18
- `SetDeltaTime(float, bool, bool)` — REL::ID(12890)
- `GetGravity()` — REL::ID(386279)
- `SetMotion(NiAVObject*, Preset, bool, bool, bool)` — REL::ID(357289)
- `EnableCollision(NiAVObject*, bool, bool, bool)` — REL::ID(50037)
- `SetOrigin(NiPoint3&)` — REL::ID(54519)

### `RE/Bethesda/bhkCharacterController.h` — bhkNPCollisionObject
Added 9 methods:

- `SetLinearVelocity(hkVector4f&)` — REL::ID(301531)
- `SetAngularVelocity(hkVector4f&)` — REL::ID(287752)
- `SetVelocity(hkVector4f&, hkVector4f&)` — REL::ID(713376) — linear + angular
- `GetPreviousLinearVelocity(hkVector4f&)` — REL::ID(353575)
- `ApplyLinearImpulse(hkVector4f&)` — REL::ID(858124)
- `ApplyPointImpulseAt(hkVector4f&, hkVector4f&)` — REL::ID(844417)
- `SetMass(float)` — REL::ID(70998)
- `GetCollisionFilterInfo()` — REL::ID(229984) — returns uint32_t
- `GetCenterOfMassInWorld(hkVector4f&)` — REL::ID(122876)

## Registration

New headers added to:
- `cmake/sourcelist.cmake` — 3 entries (hknpBodyCinfo.h, hknpCapsuleShape.h, hknpWorld.h)
- `include/RE/Fallout.h` — 3 #include lines

## Key Constants

- **Havok scale factor**: 69.99125 (~70.0). 1 Havok unit = ~70 Bethesda game units. Stored at DAT_143718110 (REL::ID 771023). Reciprocal ~0.01429.
- **Contact event type**: `hknpEventType::Enum` value 3 for contact/collision events.
- **Contact modifier flag**: 0x20000 for contact callbacks via `hknpModifierManager::addModifier` REL::ID(1455691).
- **Signal subscribe**: `hkSignal2::subscribe<GlobalSlot>` REL::ID(277607), `<MemberSlot>` REL::ID(427291).

## Contact Event Struct (0x40 bytes)

```
+0x00 = hkVector4f contactPoint (world-space)
+0x10 = hkVector4f normal
+0x20 = uint32_t bodyIdA
+0x24 = float separatingVelocity
+0x28 = uint32_t bodyIdB (0x7FFFFFFF = invalid)
+0x2C = uint32_t additionalInfo
+0x30 = uint8_t flags
+0x31 = uint8_t flags2
+0x32 = padding (14 bytes)
```

## hknpEventType::Enum Values

| Value | Event |
|---|---|
| 3 | Contact / Collision (FOCollisionListener) |
| 0xB | Island activation |
| 0xC | Broadphase exit |
| 0x16 | Breakable constraint force exceeded |

## Additional Addresses Not Yet in Headers

These are mapped in `E:/fo4dev/.claude/skills/fo4vr-havok-physics/GHIDRA_CONFIRMED_ADDRESSES.md` but not yet wrapped in CommonLibF4VR headers:

**hknpBSWorld (Bethesda world wrapper):**
- `setBodyCollisionFilterInfo(bodyId, filterInfo, rebuildMode)` — REL::ID(101950)
- `setBodyKeyframed(bodyId, rebuildMode)` — REL::ID(527037) — critical for HIGGS hand colliders
- `setBodyStatic(bodyId, rebuildMode)` — REL::ID(1058828)

**bhkPhysicsSystem:**
- `CreateInstance(bhkWorld&, hkTransformf&)` — REL::ID(1245299)
- `HasInstanceInWorld(bhkWorld&)` — REL::ID(792872)
- `GetBodyId(uint)` — REL::ID(526734)
- `ContainsBodyId(hknpBodyId)` — REL::ID(260599)
- `AddToWorld()` — REL::ID(512878)

**Ragdoll (for PLANCK port):**
- `hknpRagdoll::hknpRagdoll(data, world, ...)` — REL::ID(921077)
- `hknpRagdollKeyFrameHierarchyController::ctor` — REL::ID(210136)
- `hkbRagdollDriver::addRagdollToWorld` — REL::ID(150630)

**Motion:**
- `hknpMotion::setFromMassProperties` — REL::ID(335193)
- `hknpMotion::setPointVelocity` — REL::ID(79963)
- `hknpMotion::buildEffMassMatrixAt` — REL::ID(24447)

## Heisenberg Compatibility Notes

Heisenberg (closed-source FO4VR mod) already implements:
- Pre/PostPhysicsCallback — working, exposed via API
- 6-DOF constraint grab — HIGGS-style (object DYNAMIC, hand KEYFRAMED)
- CollisionCallback with mass + separating velocity
- Contact detection via native CONTACT_STARTED events (event type 3)

Heisenberg does NOT have:
- linearCast / capsule shapes / collision layer setup
- Working physics hand bodies (coded but disabled, "may cause crashes")

## How to Use (Quick Example)

```cpp
#include "RE/Havok/hknpWorld.h"
#include "RE/Havok/hknpBodyCinfo.h"
#include "RE/Havok/hknpCapsuleShape.h"
#include "RE/Bethesda/BSHavok.h"
#include "RE/Bethesda/bhkPickData.h"

// Raycast from hand
RE::bhkPickData pick;
pick.SetStartEnd(handPos, handPos + handForward * maxDist);
pick.collisionFilter.filter = 0x02420028; // ItemPicker layer
bhkWorld->PickObject(pick);
if (pick.HasHit()) {
    RE::hknpBody* body = pick.GetBody();
    float dist = pick.GetHitFraction() * maxDist;
}

// Apply throw impulse
hkVector4f impulse = { throwDir.x * force, throwDir.y * force, throwDir.z * force, 0 };
hkVector4f point = { hitPoint.x, hitPoint.y, hitPoint.z, 0 };
hknpWorld->ApplyBodyImpulseAt(bodyId, impulse, point);

// Create capsule hand collider
hkVector4f start = { 0, 0, -0.02f, 0 };
hkVector4f end = { 0, 0, 0.02f, 0 };
auto* capsule = RE::hknpCapsuleShape::CreateCapsuleShape(start, end, 0.015f);

// Create body
RE::hknpBodyCinfo cinfo;
cinfo.shape = capsule;
cinfo.collisionFilterInfo = myCollisionLayer;
cinfo.motionPropertiesId = { 2 }; // KEYFRAMED
RE::hknpBodyId handBodyId = hknpWorld->CreateBody(cinfo);

// Sync to VR controller each frame
hknpWorld->ComputeHardKeyFrame(handBodyId, &targetPos, &targetRot, invDt, &linVel, &angVel);
hknpWorld->SetBodyVelocity(handBodyId, linVel, angVel);

// Register contact listener
void* signal = hknpWorld->GetEventSignal(RE::hknpEventType::kContact);
// subscribe callback to signal via REL::ID(277607)
```

## Full Address Reference

See `E:/fo4dev/.claude/skills/fo4vr-havok-physics/GHIDRA_CONFIRMED_ADDRESSES.md` for 120+ confirmed function addresses with REL::IDs, organized by category.
