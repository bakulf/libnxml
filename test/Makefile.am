noinst_PROGRAMS = parser write namespace
check_PROGRAMS = new easy test_base
TESTS = $(check_PROGRAMS)

test_base_SOURCES = test_base.c
test_base_LDADD = ../src/libnxml.la

parser_SOURCES = parser.c
parser_LDADD = ../src/libnxml.la

write_SOURCES = write.c
write_LDADD = ../src/libnxml.la

new_SOURCES = new.c
new_LDADD = ../src/libnxml.la

easy_SOURCES = easy.c
easy_LDADD = ../src/libnxml.la

namespace_SOURCES = namespace.c
namespace_LDADD = ../src/libnxml.la

AM_CPPFLAGS = -I$(top_builddir)/src -I$(top_srcdir)/src
