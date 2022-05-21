# Install

## Base DWM

- Install [st](https://github.com/elendil95/st-build) and [dmenu](kek)
- Run `make` and ` sudo make install` and `make clean` to install DMW
- Copy *autostart.sh* to new direcoty ~/.dwm, and add all the programs you want to run at startup there (remember to make it executable first)
- If using a display manager like LightDM, copy dwm.desktop to /usr/share/xsessions/

## Bar

- install font-awesome to get icons in bar
- install xsetroot if not present
- modify *config.def.h* adding system specific info like what network interface you'd like to get data for, or the file to read CPU temperature from.
- Run `make` and ` sudo make install` and `make clean` to install.

**PS:** For more information on how to bind custom progrmans and commands, refer to my [original dwm build](https://github.com/elendil95/dwm-build)
