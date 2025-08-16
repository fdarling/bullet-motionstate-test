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

# Output

```
Starting Bullet test program...
0	A	ball Y position: 0
0	B	starting bWorld.stepSimulation()...
	setWorldTransform() with origin at Y: 0
0	C	...finished bWorld.stepSimulation()!
0	D	ball Y position: -0.00272222
1	A	ball Y position: -0.00272222
1	B	starting bWorld.stepSimulation()...
	setWorldTransform() with origin at Y: -0.00272222
1	C	...finished bWorld.stepSimulation()!
1	D	ball Y position: -0.00816667
2	A	ball Y position: -0.00816667
2	B	starting bWorld.stepSimulation()...
	setWorldTransform() with origin at Y: -0.00816667
2	C	...finished bWorld.stepSimulation()!
2	D	ball Y position: -0.0163333
3	A	ball Y position: -0.0163333
3	B	starting bWorld.stepSimulation()...
	setWorldTransform() with origin at Y: -0.0163333
3	C	...finished bWorld.stepSimulation()!
3	D	ball Y position: -0.0272222
4	A	ball Y position: -0.0272222
4	B	starting bWorld.stepSimulation()...
	setWorldTransform() with origin at Y: -0.0272222
4	C	...finished bWorld.stepSimulation()!
4	D	ball Y position: -0.0408333
...Ending Bullet test program...
```
