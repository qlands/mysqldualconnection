# - Find aio library


IF (RT_LIBRARY)
  # Already in cache, be silent
  SET(DL_FIND_QUIETLY TRUE)
ENDIF (RT_LIBRARY)


SET(DL_NAMES rt)
FIND_LIBRARY(RT_LIBRARY
  NAMES ${DL_NAMES}
  PATHS /lib64 /usr/lib64
)

IF (RT_LIBRARY)  
    MESSAGE(STATUS "DL founded:  ${RT_LIBRARY}")  
ENDIF (RT_LIBRARY) 
