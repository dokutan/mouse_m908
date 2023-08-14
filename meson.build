project('mouse_m908', ['cpp', 'c'],
          version: '3.3',
    meson_version: '>= 0.59.0',
  default_options: [ 'warning_level=2',
                     'cpp_std=gnu++2a',
                   ],
)

libusb_dep = dependency('libusb-1.0')

sources =  files(
        'mouse_m908.cpp',
        'include/data.cpp',
        'include/help.h',
        'include/load_config.cpp',
        'include/load_config.h',
        'include/rd_mouse.cpp',
        'include/rd_mouse.h',
        'include/rd_mouse_wireless.cpp',
        'include/rd_mouse_wireless.h'
)

devices = ['generic', 'm607', 'm686', 'm709', 'm711', 'm715', 'm719', 'm721', 'm908', 'm913', 'm990', 'm990chroma']

foreach device : devices
  sources += files(
    f'include/@device@/constructor.cpp',
    f'include/@device@/data.cpp',
    f'include/@device@/getters.cpp',
    f'include/@device@/helpers.cpp',
    f'include/@device@/mouse_@device@.h',
    f'include/@device@/readers.cpp',
    f'include/@device@/setters.cpp',
    f'include/@device@/writers.cpp'
  )
endforeach

udev_dep = dependency('udev')
udev_rules_dir = udev_dep.get_variable(pkgconfig:'udevdir')


executable('mouse_m908', sources,
  dependencies: [libusb_dep],
  install: true,
)
if host_machine.system() == 'linux'
  install_data('mouse_m908.rules',
      install_dir: join_paths(udev_rules_dir, 'rules.d')
  )
endif
install_data('mouse_m908.1',
  install_dir: get_option('mandir')
)

