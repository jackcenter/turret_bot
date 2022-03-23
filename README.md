# Setting up a Simple Actuator with ros2_control

## Introduction
Focus is getting config files and launch files set up

## Requriements

## Proceedure

### Part I: setting up the workspace
TODO: link to the readme for setting up a ros2_control workspace

Assume the name of your ros2_control workspace is $ROS2_CONTROL_WS

```
cd $ROS2_CONTROL_WS/src
mkdir turretbot
```

### Part II: creating the robot description files

First, we will create the package resposible for holding our robot's description: turretbot_description.

```bash
cd $ROS2_CONTROL_WS/src/turretbot
ros2 pkg create --build-type ament_cmake turretbot_description
```

This will create the turretbot_descroption package. You can delete the `src` and `inlcude` directories since we won't be creating any nodes here. Then add directories to get the following package structure:

turretbot_description <br>
    <code>&nbsp;&nbsp;</code> config/ <br>
    <code>&nbsp;&nbsp;</code> launch/ <br>
    <code>&nbsp;&nbsp;</code> ros2_control/ <br>
    <code>&nbsp;&nbsp;</code> urdf/ <br>
    <code>&nbsp;&nbsp;</code> CMakeLists.txt <br>
    <code>&nbsp;&nbsp;</code> package.xml <br>

**config**: a location to save the rviz configuration file after viewing the robot model.

**launch**: contains the launch file for viewing the URDF to ensure the model is setup as intented.

**ros2_control**: contains a description and location of the actuator attached to the turretbot. This file is explained in more detail below.

**urdf**: contains the URDF for the robot's links and joints (`turretbot_description.urdf.xacro`) and the primary URDF which loads all of the various description components (`turretbot.urdf.xacro`).

Create a description file for the robot system
Create an xacro to load the robot description
Create the launch file
Finish up by looking at the robot

### Part III: attaching a simulated actuator to the turret joint

```bash
ros2 pkg create --build-type ament_cmake turretbot_simulated_hardware
```

Create the plugin library
Create the header
create visability.h
Create the source file
Create a ros2_control joint description
Add xacro to robot urdf

### Part IV: launching the simulation

```bash
ros2 pkg create --build-type ament_cmake turretbot_bringup
```
Create the config folder and turretbot_controllers.yaml
Create the launch folder and turretbot_bringup.launch.py
