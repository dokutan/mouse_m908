# keymap.md
This documents all options for button mapping.
A button on the mouse can be mapped to one function out of the following categories:

- Mousebutton
	- Example: ``left``
- Special function (these affect the mouse, no key event is sent to the PC)
	- Example: ``dpi+``
- Macros (a sequence of simulated keypresses, needs to be defined separately)
	- Example: ``macro1``
- Keyboard key
	- Example: ``a`` 
- Keyboard key + modifiers
	- Example: ``super_l+shift_l+a``
- Fire button (simulates multiple button presses)
	- Example: ``fire:mouse_left:5:1``
- Snipe button (changes DPI while pressed)
	- Example: ``snipe:200``
- Media controls (only available for compatibility, use the Media_* keyboard keys if possible)
	- Example: ``media_play``

Additionally it is possible to specify the raw bytes of the mapping, this is intended for debugging and testing. Example: ``0x11aa22bb``

The following sections list all valid button mappings.

## Media controls
media_play
media_stop
media_previous
media_next
media_volume_up
media_volume_down
media_mute

## Fire button (simulates multiple button presses)
fire:⟨button⟩:⟨repeats⟩:⟨delay⟩

⟨button⟩ can be:
- mouse_left
- mouse_right
- mouse_middle
- a keyboard key

⟨repeats⟩ can be 1-255
⟨delay⟩ can be 1-255

## Snipe button (changes DPI while pressed)
snipe:⟨DPI⟩

⟨DPI⟩ can be 200-1100 (increment: 100)

## Mousebuttons and special functions
forward
backward
dpi+
dpi-
dpi-cycle
report_rate+
report_rate-
scroll_up
scroll_down
left
right
middle
profile_switch
profile+
profile-
led_mode_switch
dpi_led_toggle
reset_settings
none

## Compatibility functions (these are only handled by the official software and are mostly redundant)
compatibility_cut
compatibility_copy
compatibility_paste
compatibility_select_all
compatibility_find
compatibility_new
compatibility_print
compatibility_save
compatibility_switch_window
compatibility_close_window
compatibility_open_explorer
compatibility_run
compatibility_show_desktop
compatibility_lock_pcme
compatibility_browser_home
compatibility_browser_backward
compatibility_browser_forward
compatibility_browser_stop
compatibility_browser_refresh
compatibility_browser_search
compatibility_browser_favorite
compatibility_mail

## Macros (see README.md)
macro⟨N⟩
macro⟨N⟩:⟨repeats⟩
macro⟨N⟩:while
macro⟨N⟩:until

⟨N⟩ is the number of the macro (1-15)
⟨repeats⟩ can be 1-255
while: macro is repeated while button is pressed 
until: macro is repeated until button is pressed again

## Keyboard keys
### Modifers
ctrl_l+
shift_l+
alt_l+
super_l+
ctrl_r+
shift_r+
alt_r+
super_r+

### Keys
Esc
F1
F2
F3
F4
F5
F6
F7
F8
F9
F10
F11
F12
PrtSc
ScrLk
Pause
a
b
c
d
e
f
g
h
i
j
k
l
m
n
o
p
q
r
s
t
u
v
w
x
y
z
1
2
3
4
5
6
7
8
9
0
Tab
Caps_Lock
Shift_l
Ctrl_l
Alt_l
Super_l
Super_r
Alt_r
Menu
Ctrl_r
Shift_r
Return
Backspace
Caps_Lock
Space
Tilde
Minus
Equals
Bracket_l
Bracket_r
Backslash
Hash
Semicolon
Apostrophe
Comma
Period
Slash
Int_Key
Right
Left
Down
Up
Insert
Home
PgUp
Delete
End
PgDown
Num_Slash
Num_Asterisk
Num_Minus
Num_Plus
Num_Return
Num_1
Num_2
Num_3
Num_4
Num_5
Num_6
Num_7
Num_8
Num_9
Num_0
Num_Period
Num_Lock
Num_Equals
Num_Comma
Num_Paren_l
Num_Paren_r
Power
Lang1
Lang2
Lang3
Lang4
Lang5
Lang6
Lang7
Lang8
Lang9
F13
F14
F15
F16
F17
F18
F19
F20
F21
F22
F23
F24
Execute
Help
Props
Select
Stop
Again
Undo
Cut
Copy
Paste
Find
Mute
Volume_Up
Volume_Down
International1
International2
International3
International4
International5
International6
International7
International8
International9
Media_Play_Pause
Media_Stop_CD
Media_Previous
Media_Next
Media_Eject_CD
Media_Volume_Up
Media_Volume_Down
Media_Mute
Media_WWW
Media_Back
Media_Forward
Media_Stop
Media_Find
Media_Scroll_Up
Media_Scroll_Down
Media_Edit
Media_Sleep
Media_Screenlock
Media_Refresh
Media_Calc

