#!/bin/bash
ssh ubuntu@192.168.1.134 -L 1111:localhost:3306 -f -N
