# - Find aio library


IF (DL_LIBRARY)
  # Already in cache, be silent
  SET(DL_FIND_QUIETLY TRUE)
ENDIF (DL_LIBRARY)


SET(DL_NAMES dl)
FIND_LIBRARY(DL_LIBRARY
  NAMES ${DL_NAMES}
  PATHS /lib64 /usr/lib64
)

IF (DL_LIBRARY)  
    MESSAGE(STATUS "DL founded:  ${DL_LIBRARY}")  
ENDIF (DL_LIBRARY) 
