#!/bin/bash
DIR=$(dirname $0)
pushd $DIR
nvim -u ./init.vim
popd $DIR
