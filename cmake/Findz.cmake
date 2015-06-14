# - Find aio library


IF (Z_LIBRARY)
  # Already in cache, be silent
  SET(Z_FIND_QUIETLY TRUE)
ENDIF (Z_LIBRARY)


SET(Z_NAMES z)
FIND_LIBRARY(Z_LIBRARY
  NAMES ${Z_NAMES}
  PATHS /usr/lib /usr/local/lib /usr/lib64
)

IF (Z_LIBRARY)  
    MESSAGE(STATUS "Z founded:  ${Z_LIBRARY}")  
ENDIF (Z_LIBRARY) 
