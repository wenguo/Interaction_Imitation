#!/bin/bash
sshfs root@192.168.0.56:/root/CMVision/trunk/ctrl remote
cd remote
gvim *.cc *.hh *.c *.h
