#!/bin/bash

# run_bochs.sh
# mounts the correct loopback device, runs bochs, then unmounts.

sudo bochs -f scripts/bochsrc.txt
