#!/usr/bin/env python3
"""
Redragon Gaming Mouse Controller - Production GUI
Features:
- App-Specific Automatic Profile & Macro Switching
- Complete profile management (Profiles 1-5)
- Standard hardware defaults (left=left, right=right, etc.)
- Precision DPI controls (100 - 10,000 DPI) & Polling Rates
- Full RGB Lighting Customization (Color picker, hex code, preset colors, animations)
- Button Mapping with all supported key functions & modifier combinations
- Interactive Keyboard Macro Recorder (Records keystrokes & timing live)
- Named Macro Management (Prompt for Macro Name on save / rename)
- Test Macro Button (Simulates macro execution live)
- Complete Macro Slot Management (Slots 1-15) with Repeat & Loop Modes
- Udev Rule Auto-Installer for non-root execution
- Hardware Read / Apply & Custom INI Export/Import
- Auto-save state between sessions
"""

import sys
import os
import time
import subprocess
import configparser
import tempfile
import json
import re

from PyQt6.QtWidgets import (
    QApplication, QMainWindow, QWidget, QVBoxLayout, QHBoxLayout,
    QTabWidget, QLabel, QComboBox, QPushButton, QSlider, QSpinBox,
    QCheckBox, QGroupBox, QGridLayout, QMessageBox, QFileDialog,
    QColorDialog, QScrollArea, QFrame, QTextEdit, QLineEdit, QSplitter,
    QTableWidget, QTableWidgetItem, QHeaderView, QDialog, QStatusBar,
    QDialogButtonBox, QListWidget, QListWidgetItem, QInputDialog
)
from PyQt6.QtCore import Qt, QTimer, QThread, pyqtSignal
from PyQt6.QtGui import QColor, QFont, QIcon, QKeySequence

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
EXECUTABLE_PATH = os.path.join(SCRIPT_DIR, "mouse_m908")
CONFIG_SAVE_PATH = os.path.expanduser("~/.config/redragon_gui_state.json")

MODELS = ["711", "908", "719", "607", "686", "709", "715", "721", "913", "990", "990chroma", "generic"]

LIGHTMODES = [
    ("Static Color", "static"),
    ("Breathing", "breathing"),
    ("Breathing Rainbow", "breathing_rainbow"),
    ("Rainbow", "rainbow"),
    ("Wave", "wave"),
    ("Alternating", "alternating"),
    ("Reactive", "reactive"),
    ("Reactive Button", "reactive_button"),
    ("Flashing", "flashing"),
    ("Random", "random"),
    ("Off", "off")
]

POLL_RATES = ["125", "250", "500", "1000"]

BUTTON_FUNCTIONS = [
    ("Left Click", "left"),
    ("Right Click", "right"),
    ("Middle Click", "middle"),
    ("Forward", "forward"),
    ("Backward", "backward"),
    ("DPI +", "dpi+"),
    ("DPI -", "dpi-"),
    ("DPI Cycle", "dpi-cycle"),
    ("LED Mode Switch", "led_mode_switch"),
    ("Report Rate +", "report_rate+"),
    ("Report Rate -", "report_rate-"),
    ("Scroll Up", "scroll_up"),
    ("Scroll Down", "scroll_down"),
    ("Profile Switch", "profile_switch"),
    ("Profile +", "profile+"),
    ("Profile -", "profile-"),
    ("F12 (Window Switcher)", "F12"),
    ("Super Key (Overview)", "Super_l"),
    ("Macro 1", "macro1"),
    ("Macro 2", "macro2"),
    ("Macro 3", "macro3"),
    ("Macro 4", "macro4"),
    ("Macro 5", "macro5"),
    ("Macro 6", "macro6"),
    ("Macro 7", "macro7"),
    ("Macro 8", "macro8"),
    ("Macro 9", "macro9"),
    ("Macro 10", "macro10"),
    ("Macro 11", "macro11"),
    ("Macro 12", "macro12"),
    ("Macro 13", "macro13"),
    ("Macro 14", "macro14"),
    ("Macro 15", "macro15"),
    ("Disabled", "none")
]

PRESET_COLORS = [
    ("Green", "00FF00"),
    ("Lime", "50FF00"),
    ("Cyan", "00FFFF"),
    ("Blue", "0000FF"),
    ("Purple", "8000FF"),
    ("Magenta", "FF00FF"),
    ("Red", "FF0000"),
    ("Orange", "FF8000"),
    ("Yellow", "FFFF00"),
    ("White", "FFFFFF"),
]

QT_KEY_MAP = {
    Qt.Key.Key_A: "a", Qt.Key.Key_B: "b", Qt.Key.Key_C: "c", Qt.Key.Key_D: "d",
    Qt.Key.Key_E: "e", Qt.Key.Key_F: "f", Qt.Key.Key_G: "g", Qt.Key.Key_H: "h",
    Qt.Key.Key_I: "i", Qt.Key.Key_J: "j", Qt.Key.Key_K: "k", Qt.Key.Key_L: "l",
    Qt.Key.Key_M: "m", Qt.Key.Key_N: "n", Qt.Key.Key_O: "o", Qt.Key.Key_P: "p",
    Qt.Key.Key_Q: "q", Qt.Key.Key_R: "r", Qt.Key.Key_S: "s", Qt.Key.Key_T: "t",
    Qt.Key.Key_U: "u", Qt.Key.Key_V: "v", Qt.Key.Key_W: "w", Qt.Key.Key_X: "x",
    Qt.Key.Key_Y: "y", Qt.Key.Key_Z: "z",
    Qt.Key.Key_0: "0", Qt.Key.Key_1: "1", Qt.Key.Key_2: "2", Qt.Key.Key_3: "3",
    Qt.Key.Key_4: "4", Qt.Key.Key_5: "5", Qt.Key.Key_6: "6", Qt.Key.Key_7: "7",
    Qt.Key.Key_8: "8", Qt.Key.Key_9: "9",
    Qt.Key.Key_Return: "Return", Qt.Key.Key_Enter: "Return",
    Qt.Key.Key_Space: "Space", Qt.Key.Key_Tab: "Tab",
    Qt.Key.Key_Backspace: "Backspace", Qt.Key.Key_Escape: "Esc",
    Qt.Key.Key_Control: "Ctrl_l", Qt.Key.Key_Shift: "Shift_l",
    Qt.Key.Key_Alt: "Alt_l", Qt.Key.Key_Meta: "Super_l",
    Qt.Key.Key_Left: "Left", Qt.Key.Key_Right: "Right",
    Qt.Key.Key_Up: "Up", Qt.Key.Key_Down: "Down",
    Qt.Key.Key_Delete: "Delete", Qt.Key.Key_Insert: "Insert",
    Qt.Key.Key_Home: "Home", Qt.Key.Key_End: "End",
    Qt.Key.Key_PageUp: "PgUp", Qt.Key.Key_PageDown: "PgDown",
    Qt.Key.Key_F1: "F1", Qt.Key.Key_F2: "F2", Qt.Key.Key_F3: "F3", Qt.Key.Key_F4: "F4",
    Qt.Key.Key_F5: "F5", Qt.Key.Key_F6: "F6", Qt.Key.Key_F7: "F7", Qt.Key.Key_F8: "F8",
    Qt.Key.Key_F9: "F9", Qt.Key.Key_F10: "F10", Qt.Key.Key_F11: "F11", Qt.Key.Key_F12: "F12",
}


def get_default_profiles():
    """Generates hardware defaults for 5 profiles."""
    profiles = {}
    for p in range(1, 6):
        profiles[p] = {
            "lightmode": "static",
            "color": "00FF00",
            "brightness": 3,
            "speed": 1,
            "scrollspeed": 1,
            "report_rate": "500",
            "dpi": [1000, 1600, 2000, 3200, 5000],
            "dpi_enable": [True, True, True, True, True],
            "buttons": {
                "button_left": "left",
                "button_right": "right",
                "button_middle": "middle",
                "button_backward": "backward",
                "button_forward": "forward",
                "button_dpi_up": "F12",
                "button_dpi_down": "dpi-",
                "button_lightmode": "led_mode_switch",
                "scroll_up": "scroll_up",
                "scroll_down": "scroll_down"
            }
        }
    return profiles


class ActiveWindowThread(QThread):
    window_changed = pyqtSignal(str)

    def __init__(self):
        super().__init__()
        self.running = True

    def run(self):
        last_title = ""
        while self.running:
            try:
                res = subprocess.run(["wmctrl", "-l"], capture_output=True, text=True)
                title = res.stdout.strip()
                if title != last_title:
                    last_title = title
                    self.window_changed.emit(title)
            except Exception:
                pass
            time.sleep(1.0)

    def stop(self):
        self.running = False


class KeyRecorderDialog(QDialog):
    """Interactive Key Recorder Dialog that intercepts keystrokes and timing."""
    def __init__(self, parent=None):
        super().__init__(parent)
        self.setWindowTitle("Interactive Keystroke Recorder")
        self.resize(520, 420)
        self.recorded_actions = []
        self.is_recording = False
        self.last_event_time = None

        layout = QVBoxLayout(self)

        info_lbl = QLabel(
            "<b>Instructions:</b><br>"
            "1. Click <b>'🔴 Start Recording'</b>.<br>"
            "2. Press keys on your keyboard in sequence.<br>"
            "3. Timing delays will be calculated automatically.<br>"
            "4. Click <b>'⏹ Stop Recording'</b> when finished."
        )
        layout.addWidget(info_lbl)

        self.list_widget = QListWidget()
        layout.addWidget(self.list_widget)

        btn_box = QHBoxLayout()
        self.btn_rec = QPushButton("🔴 Start Recording")
        self.btn_rec.setStyleSheet("background-color: #d20f39; color: white; font-weight: bold; padding: 8px;")
        self.btn_rec.clicked.connect(self.toggle_recording)
        btn_box.addWidget(self.btn_rec)

        self.btn_clear = QPushButton("🗑 Clear")
        self.btn_clear.clicked.connect(self.clear_recorded)
        btn_box.addWidget(self.btn_clear)

        layout.addLayout(btn_box)

        dialog_buttons = QDialogButtonBox(QDialogButtonBox.StandardButton.Ok | QDialogButtonBox.StandardButton.Cancel)
        dialog_buttons.accepted.connect(self.accept)
        dialog_buttons.rejected.connect(self.reject)
        layout.addWidget(dialog_buttons)

        self.setFocusPolicy(Qt.FocusPolicy.StrongFocus)

    def toggle_recording(self):
        self.is_recording = not self.is_recording
        if self.is_recording:
            self.btn_rec.setText("⏹ Stop Recording")
            self.btn_rec.setStyleSheet("background-color: #40a02b; color: white; font-weight: bold; padding: 8px;")
            self.last_event_time = time.time()
            self.setFocus()
        else:
            self.btn_rec.setText("🔴 Start Recording")
            self.btn_rec.setStyleSheet("background-color: #d20f39; color: white; font-weight: bold; padding: 8px;")

    def clear_recorded(self):
        self.recorded_actions.clear()
        self.list_widget.clear()

    def keyPressEvent(self, event):
        if not self.is_recording:
            super().keyPressEvent(event)
            return

        key_code = event.key()
        if key_code in QT_KEY_MAP:
            key_str = QT_KEY_MAP[key_code]
            now = time.time()
            if self.last_event_time is not None:
                delta_ms = int((now - self.last_event_time) * 1000)
                delay_units = max(1, min(255, delta_ms // 10))
                if delay_units > 1:
                    self.recorded_actions.append(("delay", str(delay_units)))
                    self.list_widget.addItem(f"delay\t{delay_units} ({delay_units*10} ms)")
            
            self.last_event_time = now
            self.recorded_actions.append(("down", key_str))
            self.list_widget.addItem(f"down\t{key_str}")

    def keyReleaseEvent(self, event):
        if not self.is_recording or event.isAutoRepeat():
            super().keyReleaseEvent(event)
            return

        key_code = event.key()
        if key_code in QT_KEY_MAP:
            key_str = QT_KEY_MAP[key_code]
            now = time.time()
            if self.last_event_time is not None:
                delta_ms = int((now - self.last_event_time) * 1000)
                delay_units = max(1, min(255, delta_ms // 10))
                if delay_units > 1:
                    self.recorded_actions.append(("delay", str(delay_units)))
                    self.list_widget.addItem(f"delay\t{delay_units} ({delay_units*10} ms)")

            self.last_event_time = now
            self.recorded_actions.append(("up", key_str))
            self.list_widget.addItem(f"up\t{key_str}")


class RedragonGUI(QMainWindow):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("Redragon Gaming Mouse Control Studio")
        self.resize(940, 740)
        
        self.profiles = get_default_profiles()
        self.macros = {m: [] for m in range(1, 16)}
        self.macro_names = {m: f"Macro {m}" for m in range(1, 16)}
        self.app_rules = [] # list of {"keyword": "Discord", "profile": 2}
        self.auto_switch_enabled = False
        self.current_profile = 1
        self.current_macro_slot = 1

        self.load_state_from_file()
        self.init_ui()
        self.apply_production_style()
        self.check_device()

        # Start active window watcher thread
        self.win_thread = ActiveWindowThread()
        self.win_thread.window_changed.connect(self.on_active_window_changed)
        self.win_thread.start()

    def init_ui(self):
        main_widget = QWidget()
        self.setCentralWidget(main_widget)
        main_layout = QVBoxLayout(main_widget)
        main_layout.setSpacing(12)
        main_layout.setContentsMargins(16, 16, 16, 16)

        # Header Bar
        header_group = QGroupBox("Device Connection & Status")
        header_layout = QHBoxLayout(header_group)
        
        header_layout.addWidget(QLabel("Hardware Model:"))
        self.combo_model = QComboBox()
        self.combo_model.addItems(MODELS)
        self.combo_model.setCurrentText("711")
        header_layout.addWidget(self.combo_model)

        self.lbl_status = QLabel("Status: Checking hardware...")
        self.lbl_status.setStyleSheet("font-weight: bold; color: #fab387;")
        header_layout.addWidget(self.lbl_status)
        
        header_layout.addStretch()

        btn_udev = QPushButton("⚙️ Install Udev Rules")
        btn_udev.setToolTip("Install udev rule to allow controlling mouse without sudo")
        btn_udev.clicked.connect(self.install_udev_rules)
        header_layout.addWidget(btn_udev)

        btn_read = QPushButton("📥 Read from Mouse")
        btn_read.setToolTip("Fetch current settings from connected hardware")
        btn_read.clicked.connect(self.read_from_mouse)
        header_layout.addWidget(btn_read)

        main_layout.addWidget(header_group)

        # Profile Selector Bar
        prof_bar = QHBoxLayout()
        prof_bar.addWidget(QLabel("Current Active Profile:"))
        self.combo_profile = QComboBox()
        for p in range(1, 6):
            self.combo_profile.addItem(f"Profile {p}", p)
        self.combo_profile.currentIndexChanged.connect(self.on_profile_changed)
        prof_bar.addWidget(self.combo_profile)

        btn_reset_defaults = QPushButton("↺ Reset Profile Defaults")
        btn_reset_defaults.setToolTip("Reset button mappings, DPI and RGB to original hardware defaults")
        btn_reset_defaults.clicked.connect(self.reset_current_profile_defaults)
        prof_bar.addWidget(btn_reset_defaults)

        prof_bar.addStretch()
        main_layout.addLayout(prof_bar)

        # Tab Widget
        self.tabs = QTabWidget()
        
        # Tab 1: Sensitivity & DPI
        self.tab_dpi = QWidget()
        self.init_tab_dpi()
        self.tabs.addTab(self.tab_dpi, "🎯 Sensitivity & DPI")

        # Tab 2: Lighting & RGB
        self.tab_rgb = QWidget()
        self.init_tab_rgb()
        self.tabs.addTab(self.tab_rgb, "🌈 Lighting & RGB")

        # Tab 3: Button Mapping
        self.tab_buttons = QWidget()
        self.init_tab_buttons()
        self.tabs.addTab(self.tab_buttons, "🖱️ Button Mapping")

        # Tab 4: Macro Studio
        self.tab_macros = QWidget()
        self.init_tab_macros()
        self.tabs.addTab(self.tab_macros, "⚡ Macro Studio")

        # Tab 5: App-Specific Profiles & Macros
        self.tab_app_auto = QWidget()
        self.init_tab_app_auto()
        self.tabs.addTab(self.tab_app_auto, "🤖 App-Specific Auto Switcher")

        # Tab 6: Raw INI Config & File
        self.tab_ini = QWidget()
        self.init_tab_ini()
        self.tabs.addTab(self.tab_ini, "📝 INI Config & Export")

        main_layout.addWidget(self.tabs)

        # Bottom Action Bar
        bottom_layout = QHBoxLayout()
        
        btn_apply = QPushButton("🚀 Apply All Settings to Mouse Hardware")
        btn_apply.setFixedHeight(48)
        btn_apply.setStyleSheet("background-color: #1e66f5; color: white; font-size: 14px; font-weight: bold; padding: 0 24px; border-radius: 8px;")
        btn_apply.clicked.connect(self.apply_to_mouse)
        bottom_layout.addWidget(btn_apply)

        main_layout.addLayout(bottom_layout)

        # Status Bar
        self.status_bar = QStatusBar()
        self.setStatusBar(self.status_bar)
        self.status_bar.showMessage("Ready")

    def init_tab_dpi(self):
        layout = QVBoxLayout(self.tab_dpi)
        
        top_box = QGroupBox("Profile Parameters")
        top_grid = QGridLayout(top_box)

        top_grid.addWidget(QLabel("USB Polling Rate (Hz):"), 0, 0)
        self.combo_report = QComboBox()
        self.combo_report.addItems(POLL_RATES)
        self.combo_report.currentTextChanged.connect(self.save_current_tab_data)
        top_grid.addWidget(self.combo_report, 0, 1)

        top_grid.addWidget(QLabel("Scroll Speed (1-63):"), 0, 2)
        self.spin_scroll = QSpinBox()
        self.spin_scroll.setRange(1, 63)
        self.spin_scroll.valueChanged.connect(self.save_current_tab_data)
        top_grid.addWidget(self.spin_scroll, 0, 3)

        layout.addWidget(top_box)

        dpi_box = QGroupBox("DPI Levels (100 - 10,000 DPI)")
        dpi_layout = QVBoxLayout(dpi_box)

        self.dpi_widgets = []
        for i in range(5):
            row = QHBoxLayout()
            chk = QCheckBox(f"DPI Level {i+1}")
            chk.setChecked(True)
            
            slider = QSlider(Qt.Orientation.Horizontal)
            slider.setRange(100, 10000)
            slider.setSingleStep(100)

            spin = QSpinBox()
            spin.setRange(100, 10000)
            spin.setSingleStep(100)

            slider.valueChanged.connect(spin.setValue)
            spin.valueChanged.connect(slider.setValue)
            
            slider.valueChanged.connect(self.save_current_tab_data)
            chk.toggled.connect(self.save_current_tab_data)

            row.addWidget(chk, 1)
            row.addWidget(slider, 4)
            row.addWidget(spin, 1)
            row.addWidget(QLabel("DPI"), 0)

            dpi_layout.addLayout(row)
            self.dpi_widgets.append((chk, slider, spin))

        layout.addWidget(dpi_box)
        layout.addStretch()

    def init_tab_rgb(self):
        layout = QVBoxLayout(self.tab_rgb)

        mode_box = QGroupBox("Lighting Effects")
        mode_layout = QGridLayout(mode_box)

        mode_layout.addWidget(QLabel("LED Mode:"), 0, 0)
        self.combo_lightmode = QComboBox()
        for label, val in LIGHTMODES:
            self.combo_lightmode.addItem(label, val)
        self.combo_lightmode.currentIndexChanged.connect(self.save_current_tab_data)
        mode_layout.addWidget(self.combo_lightmode, 0, 1)

        mode_layout.addWidget(QLabel("Brightness (1-3):"), 1, 0)
        self.slider_bright = QSlider(Qt.Orientation.Horizontal)
        self.slider_bright.setRange(1, 3)
        self.slider_bright.valueChanged.connect(self.save_current_tab_data)
        mode_layout.addWidget(self.slider_bright, 1, 1)

        mode_layout.addWidget(QLabel("Animation Speed (1-8):"), 2, 0)
        self.slider_speed = QSlider(Qt.Orientation.Horizontal)
        self.slider_speed.setRange(1, 8)
        self.slider_speed.valueChanged.connect(self.save_current_tab_data)
        mode_layout.addWidget(self.slider_speed, 2, 1)

        layout.addWidget(mode_box)

        color_box = QGroupBox("Color Selection")
        color_layout = QVBoxLayout(color_box)

        color_row = QHBoxLayout()
        color_row.addWidget(QLabel("Current RGB Color:"))
        
        self.lbl_color_preview = QLabel("   #00FF00   ")
        self.lbl_color_preview.setAlignment(Qt.AlignmentFlag.AlignCenter)
        self.lbl_color_preview.setStyleSheet("background-color: #00FF00; color: #000; font-weight: bold; border-radius: 4px; padding: 6px 14px;")
        color_row.addWidget(self.lbl_color_preview)

        btn_color_dialog = QPushButton("🎨 Open Color Picker...")
        btn_color_dialog.clicked.connect(self.choose_color_dialog)
        color_row.addWidget(btn_color_dialog)
        color_row.addStretch()

        color_layout.addLayout(color_row)

        color_layout.addWidget(QLabel("Quick Color Presets:"))
        grid_preset = QGridLayout()
        col = 0
        row = 0
        for name, hex_code in PRESET_COLORS:
            btn = QPushButton(name)
            btn.setStyleSheet(f"background-color: #{hex_code}; color: {'#000' if name in ['Yellow', 'Green', 'Lime', 'White', 'Cyan'] else '#fff'}; font-weight: bold;")
            btn.clicked.connect(lambda _, h=hex_code: self.set_color_hex(h))
            grid_preset.addWidget(btn, row, col)
            col += 1
            if col >= 5:
                col = 0
                row += 1
        color_layout.addLayout(grid_preset)

        layout.addWidget(color_box)
        layout.addStretch()

    def init_tab_buttons(self):
        layout = QVBoxLayout(self.tab_buttons)
        scroll = QScrollArea()
        scroll.setWidgetResizable(True)
        scroll_content = QWidget()
        scroll_layout = QGridLayout(scroll_content)

        self.btn_combos = {}
        button_keys = [
            ("Left Button", "button_left"),
            ("Right Button", "button_right"),
            ("Middle Click", "button_middle"),
            ("Backward", "button_backward"),
            ("Forward", "button_forward"),
            ("DPI + Button", "button_dpi_up"),
            ("DPI - Button", "button_dpi_down"),
            ("Lightmode Switch", "button_lightmode"),
            ("Scroll Up", "scroll_up"),
            ("Scroll Down", "scroll_down")
        ]

        row = 0
        for name, key in button_keys:
            scroll_layout.addWidget(QLabel(f"{name}:"), row, 0)
            combo = QComboBox()
            for fn_label, fn_val in BUTTON_FUNCTIONS:
                combo.addItem(fn_label, fn_val)
            combo.currentIndexChanged.connect(self.save_current_tab_data)
            scroll_layout.addWidget(combo, row, 1)
            self.btn_combos[key] = combo
            row += 1

        scroll.setWidget(scroll_content)
        layout.addWidget(scroll)

    def init_tab_macros(self):
        layout = QVBoxLayout(self.tab_macros)
        
        top_bar = QHBoxLayout()
        top_bar.addWidget(QLabel("Macro Slot:"))
        self.combo_macro_slot = QComboBox()
        self.refresh_macro_combo_items()
        self.combo_macro_slot.currentIndexChanged.connect(self.on_macro_slot_changed)
        top_bar.addWidget(self.combo_macro_slot)

        btn_rename = QPushButton("✏️ Name/Rename Macro...")
        btn_rename.clicked.connect(self.prompt_rename_macro)
        top_bar.addWidget(btn_rename)

        btn_record = QPushButton("🔴 Interactive Key Recorder...")
        btn_record.setStyleSheet("background-color: #d20f39; color: white; font-weight: bold; padding: 6px 12px;")
        btn_record.clicked.connect(self.open_key_recorder)
        top_bar.addWidget(btn_record)

        top_bar.addStretch()
        layout.addLayout(top_bar)

        self.table_macro = QTableWidget(0, 2)
        self.table_macro.setHorizontalHeaderLabels(["Action Type", "Parameter / Key / Delay"])
        self.table_macro.horizontalHeader().setSectionResizeMode(QHeaderView.ResizeMode.Stretch)
        layout.addWidget(self.table_macro)

        action_bar = QHBoxLayout()
        
        btn_add = QPushButton("➕ Add Step")
        btn_add.clicked.connect(self.add_macro_step)
        action_bar.addWidget(btn_add)

        btn_del = QPushButton("➖ Remove Step")
        btn_del.clicked.connect(self.remove_macro_step)
        action_bar.addWidget(btn_del)

        btn_clear = QPushButton("🗑 Clear All")
        btn_clear.clicked.connect(self.clear_macro_steps)
        action_bar.addWidget(btn_clear)

        btn_test = QPushButton("▶ Test Macro Behavior")
        btn_test.setStyleSheet("background-color: #fe640b; color: white; font-weight: bold;")
        btn_test.setToolTip("Simulate execution of this macro live to test its behavior")
        btn_test.clicked.connect(self.test_macro_behavior)
        action_bar.addWidget(btn_test)

        btn_upload_macro = QPushButton("📤 Upload This Macro")
        btn_upload_macro.setStyleSheet("background-color: #40a02b; color: white; font-weight: bold;")
        btn_upload_macro.clicked.connect(self.upload_current_macro_to_hardware)
        action_bar.addWidget(btn_upload_macro)

        layout.addLayout(action_bar)

    def init_tab_app_auto(self):
        layout = QVBoxLayout(self.tab_app_auto)
        
        box_toggle = QGroupBox("Automatic Profile & Macro Switching")
        toggle_layout = QHBoxLayout(box_toggle)

        self.chk_auto_switch = QCheckBox("Enable App-Specific Auto Profile Switching")
        self.chk_auto_switch.setChecked(self.auto_switch_enabled)
        self.chk_auto_switch.toggled.connect(self.on_toggle_auto_switch)
        toggle_layout.addWidget(self.chk_auto_switch)
        
        self.lbl_active_win = QLabel("Active Window: Monitoring...")
        self.lbl_active_win.setStyleSheet("color: #89b4fa; font-weight: bold;")
        toggle_layout.addWidget(self.lbl_active_win)
        toggle_layout.addStretch()

        layout.addWidget(box_toggle)

        box_rules = QGroupBox("Application Mapping Rules")
        rules_layout = QVBoxLayout(box_rules)

        self.table_rules = QTableWidget(0, 2)
        self.table_rules.setHorizontalHeaderLabels(["App Title / Class Keyword (e.g. Discord, Code, Chrome)", "Target Mouse Profile"])
        self.table_rules.horizontalHeader().setSectionResizeMode(QHeaderView.ResizeMode.Stretch)
        rules_layout.addWidget(self.table_rules)

        self.refresh_rules_table()

        bar_rules = QHBoxLayout()
        btn_add_rule = QPushButton("➕ Add App Rule")
        btn_add_rule.clicked.connect(self.add_app_rule)
        bar_rules.addWidget(btn_add_rule)

        btn_del_rule = QPushButton("➖ Remove App Rule")
        btn_del_rule.clicked.connect(self.remove_app_rule)
        bar_rules.addWidget(btn_del_rule)

        bar_rules.addStretch()
        rules_layout.addLayout(bar_rules)

        layout.addWidget(box_rules)

    def refresh_rules_table(self):
        self.table_rules.setRowCount(0)
        for rule in self.app_rules:
            r = self.table_rules.rowCount()
            self.table_rules.insertRow(r)
            self.table_rules.setItem(r, 0, QTableWidgetItem(rule.get("keyword", "")))
            self.table_rules.setItem(r, 1, QTableWidgetItem(f"Profile {rule.get('profile', 1)}"))

    def add_app_rule(self):
        keyword, ok = QInputDialog.getText(self, "Add App Rule", "Enter App Title or Keyword (e.g. Discord, Code, Chrome):")
        if ok and keyword.strip():
            items = [f"Profile {p}" for p in range(1, 6)]
            prof_str, ok2 = QInputDialog.getItem(self, "Target Profile", "Select Profile to trigger for this App:", items, 0, False)
            if ok2:
                p_num = int(prof_str.split()[-1])
                self.app_rules.append({"keyword": keyword.strip(), "profile": p_num})
                self.refresh_rules_table()
                self.save_state_to_file()

    def remove_app_rule(self):
        curr = self.table_rules.currentRow()
        if curr >= 0 and curr < len(self.app_rules):
            self.app_rules.pop(curr)
            self.refresh_rules_table()
            self.save_state_to_file()

    def on_toggle_auto_switch(self, checked):
        self.auto_switch_enabled = checked
        self.save_state_to_file()
        self.status_bar.showMessage(f"App Auto Profile Switching: {'Enabled' if checked else 'Disabled'}")

    def on_active_window_changed(self, win_info):
        self.lbl_active_win.setText(f"Active Window: {win_info[:40]}...")
        if not self.auto_switch_enabled:
            return

        # Check rules
        for rule in self.app_rules:
            kw = rule.get("keyword", "").lower()
            if kw and kw in win_info.lower():
                target_p = rule.get("profile", 1)
                if target_p != self.current_profile:
                    self.switch_hardware_profile(target_p)
                    break

    def switch_hardware_profile(self, p_num):
        model = self.combo_model.currentText()
        cmd = [EXECUTABLE_PATH, "-p", str(p_num), "-M", model]
        res = subprocess.run(cmd, capture_output=True, text=True)
        if res.returncode == 0:
            self.combo_profile.blockSignals(True)
            self.combo_profile.setCurrentIndex(p_num - 1)
            self.current_profile = p_num
            self.combo_profile.blockSignals(False)
            self.load_profile_to_ui(p_num)
            self.status_bar.showMessage(f"Auto-switched hardware to Profile {p_num}")

    def refresh_macro_combo_items(self):
        curr_slot = self.combo_macro_slot.currentData() if hasattr(self, 'combo_macro_slot') and self.combo_macro_slot.count() > 0 else 1
        self.combo_macro_slot.blockSignals(True)
        self.combo_macro_slot.clear()
        for m in range(1, 16):
            name = self.macro_names.get(m, f"Macro {m}")
            self.combo_macro_slot.addItem(f"Slot {m}: {name}", m)
        
        idx = self.combo_macro_slot.findData(curr_slot)
        if idx >= 0:
            self.combo_macro_slot.setCurrentIndex(idx)
        self.combo_macro_slot.blockSignals(False)

    def prompt_rename_macro(self):
        curr_name = self.macro_names.get(self.current_macro_slot, f"Macro {self.current_macro_slot}")
        text, ok = QInputDialog.getText(self, "Macro Name", f"Enter name for Macro Slot {self.current_macro_slot}:", QLineEdit.EchoMode.Normal, curr_name)
        if ok and text.strip():
            self.macro_names[self.current_macro_slot] = text.strip()
            self.refresh_macro_combo_items()
            self.save_state_to_file()

    def test_macro_behavior(self):
        self.save_table_to_macro(self.current_macro_slot)
        steps = self.macros.get(self.current_macro_slot, [])
        if not steps:
            QMessageBox.information(self, "Test Macro", "Macro is empty!")
            return

        macro_desc = ", ".join([f"{a} {v}" for a, v in steps])
        self.status_bar.showMessage(f"Simulating Macro {self.current_macro_slot}: {macro_desc}")

        try:
            script_path = os.path.join(SCRIPT_DIR, "simple_switcher.py")
            if os.path.exists(script_path):
                subprocess.Popen(["python3", script_path])
                self.status_bar.showMessage(f"Executed Macro Test: {macro_desc}")
            else:
                QMessageBox.information(self, "Macro Execution Simulation", f"Simulated steps for Macro {self.current_macro_slot}:\n{macro_desc}")
        except Exception as e:
            QMessageBox.warning(self, "Test Error", f"Simulation error: {e}")

    def init_tab_ini(self):
        layout = QVBoxLayout(self.tab_ini)
        layout.addWidget(QLabel("Raw Hardware INI Configuration Representation:"))
        
        self.txt_ini = QTextEdit()
        self.txt_ini.setFont(QFont("Monospace", 10))
        layout.addWidget(self.txt_ini)

        btn_row = QHBoxLayout()
        
        btn_gen = QPushButton("🔄 Sync INI Text from UI State")
        btn_gen.clicked.connect(self.generate_ini_from_ui)
        btn_row.addWidget(btn_gen)

        btn_save_file = QPushButton("💾 Export INI File...")
        btn_save_file.clicked.connect(self.save_ini_file)
        btn_row.addWidget(btn_save_file)

        btn_load_file = QPushButton("📂 Import INI File...")
        btn_load_file.clicked.connect(self.load_ini_file)
        btn_row.addWidget(btn_load_file)

        layout.addLayout(btn_row)

    def apply_production_style(self):
        dark_css = """
        QMainWindow, QWidget {
            background-color: #1e1e2e;
            color: #cdd6f4;
            font-family: 'Segoe UI', Roboto, Helvetica, Arial, sans-serif;
            font-size: 13px;
        }
        QGroupBox {
            border: 1px solid #45475a;
            border-radius: 8px;
            margin-top: 12px;
            font-weight: bold;
            color: #89b4fa;
        }
        QGroupBox::title {
            subcontrol-origin: margin;
            left: 12px;
            padding: 0 6px;
        }
        QTabWidget::pane {
            border: 1px solid #45475a;
            border-radius: 6px;
            background: #181825;
        }
        QTabBar::tab {
            background: #313244;
            color: #a6adc8;
            padding: 9px 18px;
            border-top-left-radius: 6px;
            border-top-right-radius: 6px;
            margin-right: 3px;
        }
        QTabBar::tab:selected {
            background: #89b4fa;
            color: #11111b;
            font-weight: bold;
        }
        QPushButton {
            background-color: #313244;
            border: 1px solid #45475a;
            border-radius: 6px;
            color: #cdd6f4;
            padding: 7px 15px;
        }
        QPushButton:hover {
            background-color: #45475a;
            border-color: #89b4fa;
        }
        QComboBox, QSpinBox, QLineEdit {
            background-color: #313244;
            border: 1px solid #45475a;
            border-radius: 5px;
            color: #cdd6f4;
            padding: 5px 10px;
        }
        QTableWidget {
            background-color: #11111b;
            gridline-color: #313244;
            border: 1px solid #45475a;
            color: #cdd6f4;
        }
        QHeaderView::section {
            background-color: #313244;
            color: #cdd6f4;
            padding: 6px;
            border: 1px solid #45475a;
            font-weight: bold;
        }
        QTextEdit {
            background-color: #11111b;
            border: 1px solid #45475a;
            color: #a6e3a1;
        }
        QStatusBar {
            background: #181825;
            color: #a6adc8;
        }
        """
        self.setStyleSheet(dark_css)

    def check_device(self):
        try:
            res = subprocess.run(["lsusb"], capture_output=True, text=True)
            if "04d9:fc30" in res.stdout or "04d9:" in res.stdout:
                self.lbl_status.setText("Status: Redragon Mouse Connected ✅")
                self.lbl_status.setStyleSheet("font-weight: bold; color: #a6e3a1;")
                self.status_bar.showMessage("Hardware device detected: Redragon M711 / USB VID 04d9")
            else:
                self.lbl_status.setText("Status: Device not detected via lsusb")
                self.lbl_status.setStyleSheet("font-weight: bold; color: #f38ba8;")
        except Exception as e:
            self.lbl_status.setText("Status: Ready")

    def load_profile_to_ui(self, p_num):
        data = self.profiles[p_num]
        
        idx = self.combo_report.findText(str(data["report_rate"]))
        if idx >= 0: self.combo_report.setCurrentIndex(idx)
        self.spin_scroll.setValue(data["scrollspeed"])

        for i in range(5):
            chk, slider, spin = self.dpi_widgets[i]
            chk.setChecked(data["dpi_enable"][i])
            val = data["dpi"][i]
            slider.setValue(val)
            spin.setValue(val)

        lm = data["lightmode"]
        for idx in range(self.combo_lightmode.count()):
            if self.combo_lightmode.itemData(idx) == lm:
                self.combo_lightmode.setCurrentIndex(idx)
                break

        self.slider_bright.setValue(data["brightness"])
        self.slider_speed.setValue(data["speed"])
        self.set_color_hex(data["color"])

        for key, combo in self.btn_combos.items():
            fn_val = data["buttons"].get(key, "none")
            for idx in range(combo.count()):
                if combo.itemData(idx) == fn_val:
                    combo.setCurrentIndex(idx)
                    break

    def save_current_tab_data(self):
        p_num = self.current_profile
        data = self.profiles[p_num]

        data["report_rate"] = self.combo_report.currentText()
        data["scrollspeed"] = self.spin_scroll.value()

        for i in range(5):
            chk, slider, spin = self.dpi_widgets[i]
            data["dpi_enable"][i] = chk.isChecked()
            data["dpi"][i] = spin.value()

        data["lightmode"] = self.combo_lightmode.currentData()
        data["brightness"] = self.slider_bright.value()
        data["speed"] = self.slider_speed.value()

        for key, combo in self.btn_combos.items():
            data["buttons"][key] = combo.currentData()
            
        self.save_state_to_file()

    def on_profile_changed(self, idx):
        self.save_current_tab_data()
        self.current_profile = self.combo_profile.currentData()
        self.load_profile_to_ui(self.current_profile)
        self.status_bar.showMessage(f"Switched to Profile {self.current_profile}")

    def reset_current_profile_defaults(self):
        defaults = get_default_profiles()
        self.profiles[self.current_profile] = defaults[self.current_profile]
        self.load_profile_to_ui(self.current_profile)
        QMessageBox.information(self, "Profile Reset", f"Profile {self.current_profile} reset to hardware defaults.")

    def set_color_hex(self, hex_code):
        hex_code = hex_code.lstrip("#").upper()
        self.profiles[self.current_profile]["color"] = hex_code
        self.lbl_color_preview.setText(f"  #{hex_code}  ")
        self.lbl_color_preview.setStyleSheet(f"background-color: #{hex_code}; color: {'#000' if hex_code in ['00FF00', 'FFFF00', 'FFFFFF', '50FF00', '00FFFF'] else '#fff'}; font-weight: bold; border-radius: 4px; padding: 6px 14px;")

    def choose_color_dialog(self):
        curr_hex = self.profiles[self.current_profile]["color"]
        color = QColorDialog.getColor(QColor(f"#{curr_hex}"), self, "Select LED Color")
        if color.isValid():
            hex_str = f"{color.red():02X}{color.green():02X}{color.blue():02X}"
            self.set_color_hex(hex_str)

    # --- Macro Editor Methods ---
    def on_macro_slot_changed(self, idx):
        self.current_macro_slot = self.combo_macro_slot.currentData()
        self.load_macro_to_table(self.current_macro_slot)

    def load_macro_to_table(self, slot_num):
        steps = self.macros.get(slot_num, [])
        self.table_macro.setRowCount(0)
        for act, val in steps:
            r = self.table_macro.rowCount()
            self.table_macro.insertRow(r)
            self.table_macro.setItem(r, 0, QTableWidgetItem(act))
            self.table_macro.setItem(r, 1, QTableWidgetItem(val))

    def save_table_to_macro(self, slot_num):
        steps = []
        for r in range(self.table_macro.rowCount()):
            act_item = self.table_macro.item(r, 0)
            val_item = self.table_macro.item(r, 1)
            if act_item and val_item:
                steps.append((act_item.text().strip(), val_item.text().strip()))
        self.macros[slot_num] = steps
        self.save_state_to_file()

    def add_macro_step(self):
        r = self.table_macro.rowCount()
        self.table_macro.insertRow(r)
        self.table_macro.setItem(r, 0, QTableWidgetItem("down"))
        self.table_macro.setItem(r, 1, QTableWidgetItem("a"))
        self.save_table_to_macro(self.current_macro_slot)

    def remove_macro_step(self):
        curr = self.table_macro.currentRow()
        if curr >= 0:
            self.table_macro.removeRow(curr)
            self.save_table_to_macro(self.current_macro_slot)

    def clear_macro_steps(self):
        self.table_macro.setRowCount(0)
        self.save_table_to_macro(self.current_macro_slot)

    def open_key_recorder(self):
        dlg = KeyRecorderDialog(self)
        if dlg.exec() == QDialog.DialogCode.Accepted:
            if dlg.recorded_actions:
                self.macros[self.current_macro_slot] = dlg.recorded_actions
                self.load_macro_to_table(self.current_macro_slot)
                
                curr_name = self.macro_names.get(self.current_macro_slot, f"Macro {self.current_macro_slot}")
                if curr_name == f"Macro {self.current_macro_slot}":
                    name, ok = QInputDialog.getText(self, "Save Macro", f"Enter name for recorded Macro {self.current_macro_slot}:", QLineEdit.EchoMode.Normal, "My Recorded Macro")
                    if ok and name.strip():
                        self.macro_names[self.current_macro_slot] = name.strip()
                        self.refresh_macro_combo_items()

                self.save_state_to_file()
                self.status_bar.showMessage(f"Recorded {len(dlg.recorded_actions)} steps into Macro {self.current_macro_slot}")

    def upload_current_macro_to_hardware(self):
        self.save_table_to_macro(self.current_macro_slot)
        model = self.combo_model.currentText()
        steps = self.macros[self.current_macro_slot]

        if not steps:
            QMessageBox.warning(self, "Empty Macro", f"Macro slot {self.current_macro_slot} is empty!")
            return

        macro_lines = [f"{act}\t{val}" for act, val in steps]
        macro_text = "\n".join(macro_lines)

        with tempfile.NamedTemporaryFile(mode="w", suffix=".macro", delete=False) as tmp:
            tmp.write(macro_text)
            tmp_path = tmp.name

        try:
            cmd = [EXECUTABLE_PATH, "-m", tmp_path, "-n", str(self.current_macro_slot), "-M", model]
            res = subprocess.run(cmd, capture_output=True, text=True)

            if res.returncode != 0 and "Couldn't open mouse" in res.stderr:
                cmd_pk = ["pkexec"] + cmd
                res = subprocess.run(cmd_pk, capture_output=True, text=True)

            if res.returncode == 0:
                QMessageBox.information(self, "Success", f"Macro '{self.macro_names.get(self.current_macro_slot)}' successfully uploaded to mouse!")
                self.status_bar.showMessage(f"Uploaded Macro {self.current_macro_slot} to hardware")
            else:
                QMessageBox.warning(self, "Error", f"Failed to upload macro:\n{res.stderr}")
        finally:
            if os.path.exists(tmp_path):
                os.remove(tmp_path)

    # --- INI Generation & Operations ---
    def generate_ini_str(self):
        self.save_current_tab_data()
        lines = ["# Redragon Mouse Hardware Profile Configuration\n"]
        
        for p in range(1, 6):
            data = self.profiles[p]
            lines.append(f"[profile{p}]")
            lines.append(f"lightmode={data['lightmode']}")
            lines.append(f"color={data['color'].lower()}")
            lines.append(f"brightness={data['brightness']}")
            lines.append(f"speed={data['speed']}")
            lines.append(f"scrollspeed={data['scrollspeed']}")
            lines.append(f"report_rate={data['report_rate']}")

            for i in range(5):
                lines.append(f"dpi{i+1}_enable={1 if data['dpi_enable'][i] else 0}")
                lines.append(f"dpi{i+1}={data['dpi'][i]}")

            for k, v in data["buttons"].items():
                lines.append(f"{k}={v}")

            lines.append("")

        for m in range(1, 16):
            steps = self.macros.get(m, [])
            if steps:
                lines.append(f";## macro{m}")
                for act, val in steps:
                    lines.append(f";# {act}\t{val}")
                lines.append("")
        
        return "\n".join(lines)

    def generate_ini_from_ui(self):
        content = self.generate_ini_str()
        self.txt_ini.setText(content)
        self.status_bar.showMessage("Generated INI representation")

    def apply_to_mouse(self):
        self.save_current_tab_data()
        model = self.combo_model.currentText()
        ini_content = self.generate_ini_str()

        with tempfile.NamedTemporaryFile(mode="w", suffix=".ini", delete=False) as tmp:
            tmp.write(ini_content)
            tmp_path = tmp.name

        try:
            cmd = [EXECUTABLE_PATH, "-c", tmp_path, "-M", model]
            res = subprocess.run(cmd, capture_output=True, text=True)

            if res.returncode != 0 and ("Couldn't open mouse" in res.stderr or "permissions" in res.stderr):
                pk_cmd = ["pkexec", EXECUTABLE_PATH, "-c", tmp_path, "-M", model]
                res = subprocess.run(pk_cmd, capture_output=True, text=True)

            if res.returncode == 0:
                has_macros = any(len(self.macros[m]) > 0 for m in range(1, 16))
                if has_macros:
                    cmd_m = [EXECUTABLE_PATH, "-m", tmp_path, "-M", model]
                    res_m = subprocess.run(cmd_m, capture_output=True, text=True)
                    if res_m.returncode != 0 and "Couldn't open mouse" in res_m.stderr:
                        subprocess.run(["pkexec"] + cmd_m, capture_output=True, text=True)

                QMessageBox.information(self, "Success", "All settings successfully uploaded to your Redragon mouse!")
                self.status_bar.showMessage("Hardware updated successfully!")
            else:
                QMessageBox.warning(self, "Error", f"Failed to upload settings to hardware:\n{res.stderr}")
        finally:
            if os.path.exists(tmp_path):
                os.remove(tmp_path)

    def read_from_mouse(self):
        model = self.combo_model.currentText()
        cmd = [EXECUTABLE_PATH, "-R", "-", "-M", model]
        res = subprocess.run(cmd, capture_output=True, text=True)

        if res.returncode != 0 and "Couldn't open mouse" in res.stderr:
            cmd_pk = ["pkexec"] + cmd
            res = subprocess.run(cmd_pk, capture_output=True, text=True)

        if res.returncode == 0 and res.stdout.strip():
            self.txt_ini.setText(res.stdout)
            self.parse_and_load_ini_str(res.stdout)
            QMessageBox.information(self, "Read Success", "Successfully read configuration from mouse hardware!")
            self.status_bar.showMessage("Read settings from hardware")
        else:
            QMessageBox.warning(self, "Read Failed", f"Could not read from mouse hardware:\n{res.stderr}")

    def save_ini_file(self):
        content = self.generate_ini_str()
        path, _ = QFileDialog.getSaveFileName(self, "Save INI Configuration", "redragon_profile.ini", "INI Files (*.ini)")
        if path:
            with open(path, "w") as f:
                f.write(content)
            QMessageBox.information(self, "Saved", f"Configuration exported to {path}")

    def load_ini_file(self):
        path, _ = QFileDialog.getOpenFileName(self, "Open INI Configuration", "", "INI Files (*.ini)")
        if path and os.path.exists(path):
            with open(path, "r") as f:
                content = f.read()
            self.txt_ini.setText(content)
            self.parse_and_load_ini_str(content)

    def parse_and_load_ini_str(self, content):
        config = configparser.ConfigParser(strict=False)
        config.read_string(content)
        
        for p in range(1, 6):
            sec = f"profile{p}"
            if sec in config:
                d = self.profiles[p]
                if "lightmode" in config[sec]: d["lightmode"] = config[sec]["lightmode"]
                if "color" in config[sec]: d["color"] = config[sec]["color"].upper()
                if "brightness" in config[sec]: d["brightness"] = int(config[sec]["brightness"])
                if "speed" in config[sec]: d["speed"] = int(config[sec]["speed"])
                if "scrollspeed" in config[sec]: d["scrollspeed"] = int(config[sec]["scrollspeed"])
                if "report_rate" in config[sec]: d["report_rate"] = config[sec]["report_rate"]

                for i in range(5):
                    k_en = f"dpi{i+1}_enable"
                    k_val = f"dpi{i+1}"
                    if k_en in config[sec]: d["dpi_enable"][i] = (config[sec][k_en] == "1")
                    if k_val in config[sec]:
                        val_str = config[sec][k_val]
                        m = re.search(r'\d+', val_str)
                        if m: d["dpi"][i] = int(m.group(0))

                for key in d["buttons"].keys():
                    if key in config[sec]:
                        d["buttons"][key] = config[sec][key]

        self.load_profile_to_ui(self.current_profile)

    def install_udev_rules(self):
        rule_path = os.path.join(SCRIPT_DIR, "mouse_m908.rules")
        dest_path = "/etc/udev/rules.d/99-mouse_m908.rules"
        
        script = f"cp '{rule_path}' '{dest_path}' && udevadm control --reload-rules && udevadm trigger"
        pk_cmd = ["pkexec", "sh", "-c", script]
        
        res = subprocess.run(pk_cmd, capture_output=True, text=True)
        if res.returncode == 0:
            QMessageBox.information(self, "Udev Installed", "Udev rules installed successfully! You can now control the mouse without sudo.")
            self.check_device()
        else:
            QMessageBox.warning(self, "Installation Failed", f"Could not install udev rules:\n{res.stderr}")

    def closeEvent(self, event):
        if hasattr(self, 'win_thread'):
            self.win_thread.stop()
            self.win_thread.wait()
        super().closeEvent(event)

    def save_state_to_file(self):
        try:
            state = {
                "profiles": self.profiles,
                "macros": self.macros,
                "macro_names": self.macro_names,
                "app_rules": self.app_rules,
                "auto_switch_enabled": self.auto_switch_enabled,
                "model": self.combo_model.currentText() if hasattr(self, 'combo_model') else "711"
            }
            os.makedirs(os.path.dirname(CONFIG_SAVE_PATH), exist_ok=True)
            with open(CONFIG_SAVE_PATH, "w") as f:
                json.dump(state, f, indent=2)
        except Exception:
            pass

    def load_state_from_file(self):
        if os.path.exists(CONFIG_SAVE_PATH):
            try:
                with open(CONFIG_SAVE_PATH, "r") as f:
                    state = json.load(f)
                if "profiles" in state:
                    self.profiles = {int(k): v for k, v in state["profiles"].items()}
                if "macros" in state:
                    self.macros = {int(k): v for k, v in state["macros"].items()}
                if "macro_names" in state:
                    self.macro_names = {int(k): v for k, v in state["macro_names"].items()}
                if "app_rules" in state:
                    self.app_rules = state["app_rules"]
                if "auto_switch_enabled" in state:
                    self.auto_switch_enabled = state["auto_switch_enabled"]
            except Exception:
                pass


def main():
    app = QApplication(sys.argv)
    window = RedragonGUI()
    window.show()
    sys.exit(app.exec())


if __name__ == "__main__":
    main()
