# - Find aio library


IF (CRYPT_LIBRARY)
  # Already in cache, be silent
  SET(CRYPT_FIND_QUIETLY TRUE)
ENDIF (CRYPT_LIBRARY)


SET(CRYPT_NAMES crypt)
FIND_LIBRARY(CRYPT_LIBRARY
  NAMES ${CRYPT_NAMES}
  PATHS /usr/lib /usr/local/lib /usr/lib64
)

IF (CRYPT_LIBRARY)  
    MESSAGE(STATUS "Crypt founded:  ${CRYPT_LIBRARY}")  
ENDIF (CRYPT_LIBRARY)