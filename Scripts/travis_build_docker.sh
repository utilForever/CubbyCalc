#!/usr/bin/env bash

set -e

if [ $# -eq 0 ]
  then
    docker build -t utilforever/cubbycalc .
else
    docker build -f $1 -t utilforever/cubbycalc:$2 .
fi