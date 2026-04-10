#!/bin/bash

partekatu=$1
#ip=$2

shared=/home/manex/virtualBox/Shared

while true; do

  rm -rf $shared/$partekatu
  cp -r $partekatu $shared

  sleep 5
done
