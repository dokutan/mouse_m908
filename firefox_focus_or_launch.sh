#!/bin/bash
# Focus existing Firefox window or launch a new Firefox instance if none exists
if pgrep -i "firefox" > /dev/null; then
    wmctrl -x -a "firefox.Firefox" 2>/dev/null || wmctrl -a "Firefox" 2>/dev/null || wmctrl -R "Firefox" 2>/dev/null
else
    firefox &
fi
