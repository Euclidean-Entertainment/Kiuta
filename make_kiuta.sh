#!/bin/bash

ncores=$(nproc --all)

make -j $ncores
