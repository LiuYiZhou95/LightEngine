#pragma once
#include "..\pch.h"

struct ActorMotionState;
struct MaterialData;

class BulletPhysics : public IGamePhysics, public Singleton<BulletPhysics>
{
	friend class CharacterControllerComponent;
	// use auto pointers to automatically call delete on these objects
	//   during ~BulletPhysics

	// these are all of the objects that Bullet uses to do its work.
	//   see BulletPhysics::VInitialize() for some more info.
	btDynamicsWorld*                 m_dynamicsWorld;
	btBroadphaseInterface*           m_broadphase;
	btCollisionDispatcher*           m_dispatcher;
	btConstraintSolver*              m_solver;
	btDefaultCollisionConfiguration* m_collisionConfiguration;
	BulletDebugDrawer*               m_debugDrawer;

	// tables read from the XML
	typedef std::map<std::string, float> DensityTable;
	typedef std::map<std::string, MaterialData> MaterialTable;
	DensityTable m_densityTable;
	MaterialTable m_materialTable;

	void LoadXml();
	float LookupSpecificGravity(const std::string& densityStr);
	MaterialData LookupMaterialData(const std::string& materialStr);

	// keep track of the existing rigid bodies:  To check them for updates
	//   to the actors' positions, and to remove them when their lives are over.
	typedef std::map<ActorId, btRigidBody*> ActorIDToBulletRigidBodyMap;
	ActorIDToBulletRigidBodyMap m_actorIdToRigidBody;
	btRigidBody * FindBulletRigidBody(ActorId id) const;

	// also keep a map to get the actor id from the btRigidBody*
	typedef std::map<btRigidBody const *, ActorId> BulletRigidBodyToActorIDMap;
	BulletRigidBodyToActorIDMap m_rigidBodyToActorId;
	ActorId FindActorID(btRigidBody const *) const;

	// data used to store which collision pair (bodies that are touching) need
	//   Collision events sent.  When a new pair of touching bodies are detected,
	//   they are added to m_previousTickCollisionPairs and an event is sent.
	//   When the pair is no longer detected, they are removed and another event
	//   is sent.
	typedef std::pair< btRigidBody const *, btRigidBody const * > CollisionPair;
	typedef std::set< CollisionPair > CollisionPairs;
	CollisionPairs m_previousTickCollisionPairs;

	// helpers for sending events relating to collision pairs
	void SendCollisionPairAddEvent(btPersistentManifold const * manifold, btRigidBody const * body0, btRigidBody const * body1);
	void SendCollisionPairRemoveEvent(btRigidBody const * body0, btRigidBody const * body1);

	// common functionality used by VAddSphere, VAddBox, etc
	void AddShape(Actor* pGameActor, btCollisionShape* shape, float mass, const std::string& physicsMaterial);

	// helper for cleaning up objects
	void RemoveCollisionObject(btCollisionObject * removeMe);

	// callback from bullet for each physics time step.  set in VInitialize
	static void BulletInternalTickCallback(btDynamicsWorld * const world, btScalar const timeStep);
protected:
	
public:
	BulletPhysics();				// [mrmike] This was changed post-press to add event registration!
	virtual ~BulletPhysics();

	virtual void onStartUp();
	virtual void onShutDown();

	// Initialiazation and Maintenance of the Physics World
	virtual bool VInitialize() override;
	virtual void VSyncVisibleScene() override;
	virtual void VOnUpdate(float deltaSeconds) override;

	// Initialization of Physics Objects
	virtual void VAddSphere(float radius, Actor* pGameActor, const std::string& densityStr, const std::string& physicsMaterial) override;
	virtual void VAddBox(const vec3& dimensions, Actor* pGameActor, const std::string& densityStr, const std::string& physicsMaterial) override;
	virtual void VAddPointCloud(vec3 *verts, int numPoints, Actor* pGameActor, const std::string& densityStr, const std::string& physicsMaterial) override;
	virtual void VRemoveActor(ActorId id) override;
	virtual void VAddCharacter(const vec3& dimensions, Actor* gameActor);
	// Debugging
	virtual void VRenderDiagnostics() override;

	// Physics world modifiers
	virtual void VCreateTrigger(Actor* pGameActor, const vec3 &pos, const float dim) override;
	virtual void VApplyForce(const vec3 &dir, float newtons, ActorId aid) override;
	virtual void VApplyTorque(const vec3 &dir, float newtons, ActorId aid) override;
	virtual bool VKinematicMove(const mat4 &mat, ActorId aid) override;

	virtual void VRotateY(ActorId actorId, float angleRadians, float time);
	virtual float VGetOrientationY(ActorId actorId);
	virtual void VStopActor(ActorId actorId);
	virtual vec3 VGetVelocity(ActorId actorId);
	virtual void VSetVelocity(ActorId actorId, const vec3& vel);
	virtual vec3 VGetAngularVelocity(ActorId actorId);
	virtual void VSetAngularVelocity(ActorId actorId, const vec3& vel);
	virtual void VTranslate(ActorId actorId, const vec3& vec);

	virtual void VSetTransform(const ActorId id, const mat4& mat);

	virtual mat4 VGetTransform(const ActorId id);
	
	// test
	virtual void VClearForce(ActorId id);
};


IGamePhysics *gPhysic();