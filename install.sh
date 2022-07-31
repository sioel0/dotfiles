#!/bin/bash

# get current directory
PWD=$(pwd)

# store launch command to get the build full path
NAME=$0

# build full path
SOURCE=${NAME//install.sh/}

# check if it has been launched using the full path
if [[ NAME != ^/* ]];then
  SOURCE=$(cut -d. -f2 <<< $SOURCE)
  SOURCE=$PWD/$SOURCE
fi

# setup home directory files
stow --dir=$SOURCE --target=/home/$USER home

# setup .config directory
stow --dir=$SOURCE --target=/home/$USER/.config config
