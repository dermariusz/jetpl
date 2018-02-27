string  = executable('string-test', 'string-test.c', link_with: jetpl, include_directories : incdir)
strip   = executable('strip-test', 'strip-test.c', link_with: jetpl, include_directories : incdir)
typical = executable('typical-test',  'typical.c', 'typical-test.c', link_with: jetpl, include_directories : incdir)

test('test string', string)
test('test strip', strip)
test('test typical', typical)
