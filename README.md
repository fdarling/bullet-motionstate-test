# Overview

A minimal example showing an off-by-one issue with `btMotionState::setWorldTransform()` and `btCollisionObject::getWorldTransform()`.

`btMotionState::setWorldTransform()` is triggered from `btDynamicsWorld::stepSimulation()`, but it is given the old transformation that was already present prior to the `stepSimulation()` call. This means btMotionState is always one cycle "out of date" compared to transform retrieved from `btCollisionObject::getWorldTransform()`.

# Dependencies

* CMake
* GCC
* Bullet v3.24+

On Debian based Linux:

```
sudo apt install cmake
sudo apt install build-essential
sudo apt install libbullet-dev
```

# Compiling

```
cd bullet-motionstate-test
mkdir build
cd build
cmake ..
cmake --build .
```

# Running

```
./bullet-motionstate-test
```
