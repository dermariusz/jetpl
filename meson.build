project ('jetpl', 'c',
  version : '0.1.0',
  license : 'Mit'
)

incdir = include_directories('include')

subdir ('include')
subdir ('src')
subdir ('tests')

pkg = import('pkgconfig')
libs = jetpl
h = 'jetpl-1.0'
pkg.generate(libraries : libs,
			 subdirs : h,
			 version : '1.0',
			 name : 'JeTpl',
			 filebase : 'jetpl-1.0',
			 description: 'A simple templating engine')
