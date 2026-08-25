#!/bin/bash
# Focus existing Firefox window or launch a new Firefox instance
wmctrl -x -a "firefox.Firefox" 2>/dev/null || wmctrl -a "Firefox" 2>/dev/null || firefox &
