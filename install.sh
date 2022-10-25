#!/bin/bash

rm ~/.bashrc ~/.zshrc
# setup home directory files
stow --dir=. --target=/home/$USER home
# setup .config directory files
stow --dir=. --target=/home/$USER/.config config
