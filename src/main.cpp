#include <btBulletDynamicsCommon.h>

#include <iostream> // for std::cout and std::endl
#include <cstdlib> // for EXIT_SUCCESS and EXIT_FAILURE

static const btScalar BALL_RADIUS = 0.25;
static const btScalar BALL_MASS = 5.0;
static const btScalar TIME_DELTA = 1.0/60.0; // 60 Hz
static const int SIMULATION_DURATION_TICKS = 5;

static btDbvtBroadphase bBroadphase;
static btDefaultCollisionConfiguration bCollisionConfig;
static btCollisionDispatcher bDispatcher{&bCollisionConfig};
static btSequentialImpulseConstraintSolver bSolver;
static btDiscreteDynamicsWorld bWorld{&bDispatcher, &bBroadphase, &bSolver, &bCollisionConfig};

static btVector3 generateInertia(btScalar mass, const btCollisionShape *bShape)
{
    btVector3 bInertia{0.0, 0.0, 0.0};
    if (mass != 0.0)
        bShape->calculateLocalInertia(mass, bInertia);
    return bInertia;
}

class CustomMotionState : public btMotionState
{
public:
    void getWorldTransform(btTransform &worldTrans) const override
    {
        worldTrans.setIdentity();
    }
    void setWorldTransform(const btTransform &worldTrans) override
    {
        std::cout << "\tsetWorldTransform() with origin at Y: " << worldTrans.getOrigin().y() << std::endl;
    }
};

static btSphereShape ballShape{BALL_RADIUS}; // can't be const unfortunately...
static CustomMotionState ballMotionState;
static const btRigidBody::btRigidBodyConstructionInfo ballBodyInfo{BALL_MASS, &ballMotionState, &ballShape, generateInertia(BALL_MASS, &ballShape)};
static btRigidBody ballBody{ballBodyInfo};

int main(int argc, char **argv)
{
    std::cout << "Starting Bullet test program..." << std::endl;

    bWorld.setGravity({0.0f, -9.8f, 0.0f});

    // ballBody.setDamping(0.0, 0.2);
    // ballBody.setRestitution(0.8);
    bWorld.addRigidBody(&ballBody);

    btScalar t = 0.0;
    for (int i = 0; i < SIMULATION_DURATION_TICKS; i++)
    {
        std::cout << i << "\tA\tball Y position: " << ballBody.getWorldTransform().getOrigin().y() << std::endl;
        t += TIME_DELTA;
        std::cout << i << "\tB\tstarting bWorld.stepSimulation()..." << std::endl;
        bWorld.stepSimulation(TIME_DELTA, 10);
        std::cout << i << "\tC\t...finished bWorld.stepSimulation()!" << std::endl;
        std::cout << i << "\tD\tball Y position: " << ballBody.getWorldTransform().getOrigin().y() << std::endl;
    }

    bWorld.removeRigidBody(&ballBody);

    std::cout << "...Ending Bullet test program..." << std::endl;
    return EXIT_SUCCESS;
}
