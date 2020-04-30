#!/bin/bash
make $1
./$1 <res/$1.in >res/$1.out 2>res/$1.log
diff -s res/$1.out res/$1.ans >>res/$1.log
