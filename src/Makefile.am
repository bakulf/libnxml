lib_LTLIBRARIES = libnxml.la

libnxml_la_SOURCES = \
	nxml_parser.c \
	nxml_download.c \
	nxml_init.c \
	nxml_error.c \
	nxml_free.c \
	nxml_write.c \
	nxml_edit.c \
	nxml_utf.c \
	nxml_string.c \
	nxml_easy.c \
	nxml_tools.c \
	nxml_namespace.c

libnxml_la_LDFLAGS = -version-info @LIBNXML_VERSION_INFO@

EXTRA_DIST = nxml.h.in nxml.h nxml_internal.h

incdir = $(includedir)
inc_DATA = nxml.h
