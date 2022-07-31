# Dotfiles

This is a collection of my detfiles used on any linux distro of choice. To
make this work it is necessary to install `stow` installed.

## Directory structure

The directory structure is based on the "package" environment, the main
idea is to create a directory for each stow destination needed.
- *home*: stores the file that will be symlynked inside the home directory.
- *config*: stores all the directory that will be symlinked to the 
`.config` directory.

# How to use it

To install all the configuration on a new machine just run:
```sh
git clone --depth=1 https://github.com:sioel0/dotfiles
./dotfiles/install.sh
```

**N.B.** *Make sure to have Gnu Stow installed on the system.*

**\*Warning\*** *Remember to launch the* `install.sh` *script when you pull from
remote or change the directory location.*

# Config files
- i3
- i3status
- nvim
- dunst
- Xresources(tokyonight storm)
- Xmodmap(switch caps with right ctrl)
- bash
- gdb(launch pwndbg)
- rofi
