#!/usr/bin/env python3
"""
Simple Lightweight Window Switcher for Linux / GNOME
Uses wmctrl to list all active open windows in a lightweight, instant popup.
"""

import subprocess
import sys
from PyQt6.QtWidgets import QApplication, QWidget, QVBoxLayout, QPushButton, QLabel, QListWidget, QListWidgetItem
from PyQt6.QtCore import Qt, QPoint
from PyQt6.QtGui import QCursor

def get_open_windows():
    try:
        res = subprocess.run(["wmctrl", "-l"], capture_output=True, text=True)
        windows = []
        for line in res.stdout.strip().split("\n"):
            if not line.strip(): continue
            parts = line.split(maxsplit=3)
            if len(parts) >= 4:
                win_id = parts[0]
                desktop = parts[1]
                host = parts[2]
                title = parts[3]
                # Filter out desktop background
                if title and title != "Desktop":
                    windows.append((win_id, title))
        return windows
    except Exception:
        return []

class LightweightSwitcher(QWidget):
    def __init__(self):
        super().__init__()
        self.setWindowFlags(Qt.WindowType.FramelessWindowHint | Qt.WindowType.WindowStaysOnTopHint | Qt.WindowType.Tool)
        self.setAttribute(Qt.WidgetAttribute.WA_TranslucentBackground, False)
        
        self.windows = get_open_windows()
        if not self.windows:
            sys.exit(0)

        layout = QVBoxLayout(self)
        layout.setContentsMargins(10, 10, 10, 10)
        
        title_lbl = QLabel("Select Application Window:")
        title_lbl.setStyleSheet("font-weight: bold; color: #89b4fa; font-size: 14px; margin-bottom: 6px;")
        layout.addWidget(title_lbl)

        self.list_widget = QListWidget()
        self.list_widget.setStyleSheet("""
            QListWidget {
                background-color: #11111b;
                color: #cdd6f4;
                border: 1px solid #45475a;
                border-radius: 6px;
                font-size: 13px;
            }
            QListWidget::item {
                padding: 10px;
                border-bottom: 1px solid #313244;
            }
            QListWidget::item:hover {
                background-color: #313244;
                color: #89b4fa;
            }
            QListWidget::item:selected {
                background-color: #1e66f5;
                color: #ffffff;
                font-weight: bold;
            }
        """)

        for win_id, title in self.windows:
            item = QListWidgetItem(f"🗔  {title}")
            item.setData(Qt.ItemDataRole.UserRole, win_id)
            self.list_widget.addItem(item)

        self.list_widget.itemClicked.connect(self.activate_window)
        layout.addWidget(self.list_widget)

        # Style
        self.setStyleSheet("""
            QWidget {
                background-color: #1e1e2e;
                border: 2px solid #89b4fa;
                border-radius: 10px;
            }
        """)

        self.resize(400, min(350, max(120, len(self.windows) * 45 + 50)))

        # Center on mouse cursor
        pos = QCursor.pos()
        self.move(pos.x() - 200, pos.y() - 100)

    def activate_window(self, item):
        win_id = item.data(Qt.ItemDataRole.UserRole)
        if win_id:
            subprocess.run(["wmctrl", "-i", "-a", win_id])
        self.close()

    def keyPressEvent(self, event):
        if event.key() == Qt.Key.Key_Escape:
            self.close()
        else:
            super().keyPressEvent(event)


def main():
    app = QApplication(sys.argv)
    switcher = LightweightSwitcher()
    switcher.show()
    sys.exit(app.exec())

if __name__ == "__main__":
    main()
