# define these targets in your makefile if you wish
# local_all local_depend local_clean depend_install local_install local_distclean local_extraclean:

# and define these variables to imapact your build
LOCAL_CFLAGS=
LOCAL_LDFLAGS=
LOCAL_OBJS=
include $(BASE)/build/modmake.rules

