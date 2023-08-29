#!/bin/bash


if [ -d plugin/plugin-srcs ]
then
    :
else
    echo "ERROR: can not find submodule plugin"
    echo "git pull"
    echo "git submodule update --init --recursive"
    exit 1
fi

echo "INFO: DOWNLOADING EV3 MODEL"

if [ -d ev3/Assets/Model/Hakoniwa/Robots/Ev3 ]
then
    echo "INFO: EV3 MODEL IS ALREADY INSTALLED."
else
    mkdir ev3/Assets/Model
    mkdir ev3/Assets/Model/Hakoniwa
    mkdir ev3/Assets/Model/Hakoniwa/Robots
    wget https://github.com/toppers/hakoniwa-unity-ev3model/releases/download/model-v1.0.0/Ev3.zip
    mv Ev3.zip ev3/Assets/Model/Hakoniwa/Robots/
    ORG_DIR=`pwd`
    cd ev3/Assets/Model/Hakoniwa/Robots/
    unzip Ev3.zip
    cd ${ORG_DIR}
    echo "INFO: COPYING EV3Assets to hakoniwa plugin(plugin/plugin-srcs/Assets/)"
    cp -rp ev3/Assets/Model plugin/plugin-srcs/Assets/
fi

cp -rp ev3/Assets/* plugin/plugin-srcs/Assets/
cp -rp ev3/hakoniwa-base/* hakoniwa-base/
cp ev3/hakoniwa-base/workspace/dev/src/crossing_gate/target_virtual.h hakoniwa-base/workspace/dev/src/crossing_gate/target.h 

if [ ! -d hakoniwa-base/workspace/runtime/run/crossing_gate-1 ]
then
    mkdir hakoniwa-base/workspace/runtime/run/crossing_gate-1
fi

cd plugin

bash install.bash