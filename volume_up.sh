#!/bin/bash
wpctl set-volume -l 1.5 @DEFAULT_AUDIO_SINK@ 5%+ 2>/dev/null || pactl set-sink-volume @DEFAULT_SINK@ +5% 2>/dev/null || amixer -q sset Master 5%+
