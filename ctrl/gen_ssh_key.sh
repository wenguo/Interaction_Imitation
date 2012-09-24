#!/bin/bash
ssh-keygen
sleep 1
ssh-copy-id -i ~/.ssh/id_rsa.pub root@192.168.0.$1
