#!/usr/bin/env python3
import subprocess
import os

COLORS = ["00FF00", "FF0000", "0000FF", "FFFF00", "00FFFF", "FF00FF", "FFFFFF"]
STATE_FILE = "/tmp/redragon_color_index.txt"
SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
EXECUTABLE_PATH = os.path.join(SCRIPT_DIR, "mouse_m908")

idx = 0
if os.path.exists(STATE_FILE):
    try:
        with open(STATE_FILE, "r") as f:
            idx = int(f.read().strip())
    except Exception:
        pass

next_idx = (idx + 1) % len(COLORS)
color = COLORS[next_idx]

with open(STATE_FILE, "w") as f:
    f.write(str(next_idx))

lines = []
for p in range(1, 6):
    lines.append(f"[profile{p}]")
    lines.append("lightmode=static")
    lines.append(f"color={color.lower()}")
    lines.append("brightness=3")
    lines.append("")

tmp_path = "/tmp/temp_color.ini"
with open(tmp_path, "w") as f:
    f.write("\n".join(lines))

subprocess.run([EXECUTABLE_PATH, "-c", tmp_path, "-M", "711"])
if os.path.exists(tmp_path):
    os.remove(tmp_path)
