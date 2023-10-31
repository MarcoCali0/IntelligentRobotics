#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <project_name>"
    exit 1
fi

project_name=$1

# Create the workspace directory
mkdir -p ${project_name}_ws/src

# Change to the src directory
cd ${project_name}_ws/src

# Initialize the Catkin workspace
catkin_init_workspace

# Move back to the workspace directory
cd ..

# Build the Catkin workspace
catkin build

# Add the source setup to the .bashrc file
echo "source /home/marco/IntelligentRobotics/${project_name}_ws/devel/setup.bash" >> ~/.bashrc

# Reload the .bashrc to apply the changes
source ~/.bashrc

# Change to the src directory
cd src

# Create a package using catkin_create_pkg
catkin_create_pkg ${project_name} std_msgs roscpp

# Move back to the workspace directory
cd ..

# Build the Catkin workspace again
catkin build

echo "ROS project '${project_name}' has been created."
