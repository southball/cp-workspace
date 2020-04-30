#!/bin/bash
mkdir -p res
touch template.cpp
for i in a b c d e f; do
	touch res/$i.cpp res/$i.in res/$i.out res/$i.ans res/$i.log;
done
vim -p a.cpp b.cpp c.cpp d.cpp e.cpp f.cpp template.cpp
