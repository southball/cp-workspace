#!/bin/bash
pushd $(dirname $0)
source ./config.sh
touch template.cpp
mkdir -p res
files_list=""
for i in $files; do
	files_list+="$i.cpp "
	touch $i.cpp res/$i.in res/$i.out res/$i.ans res/$i.log;
done
vim -p $files_list template.cpp
popd
