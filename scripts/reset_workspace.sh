#!/bin/bash
source ./config.sh;
for i in $files; do
	cat template.cpp > $i.cpp;
done;
