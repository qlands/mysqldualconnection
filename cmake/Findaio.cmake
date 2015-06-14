# - Find aio library

IF (AIO_LIBRARY)
  # Already in cache, be silent
  SET(AIO_FIND_QUIETLY TRUE)
ENDIF (AIO_LIBRARY)


SET(AIO_NAMES aio)
FIND_LIBRARY(AIO_LIBRARY
  NAMES ${AIO_NAMES}
  PATHS /usr/lib /usr/local/lib /usr/lib64
)

IF (AIO_LIBRARY)  
    MESSAGE(STATUS "AIO founded:  ${AIO_LIBRARY}")  
ENDIF (AIO_LIBRARY)