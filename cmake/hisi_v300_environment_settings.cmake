include(CMakeForceCompiler)
SET(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR arm ) 
SET(CMAKE_SYSTEM_VERSION 1)

SET(CMAKE_C_COMPILER   arm-hisiv300-linux-gcc)
SET(CMAKE_CXX_COMPILER arm-hisiv300-linux-g++)
SET(CMAKE_STRIP arm-hisiv300-linux-strip)

SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

SET(FTP_DIR "${PROJECT_SOURCE_DIR}/ftp/hisi")
	
SET(VZPROJECT_INCLUDE_DIR
	${PROJECT_SOURCE_DIR}/src/lib
  ${PROJECT_SOURCE_DIR}/src/third_part
  ${PROJECT_SOURCE_DIR}/src/third_part/boost
	)

SET(VZPROJECT_LIBRARY_DIR
)

MESSAGE(STATUS "       Add LIBRARY PATH AND NAME")
IF(CMAKE_BUILD_TYPE MATCHES Debug)
	MESSAGE(STATUS "       Debug Mode")
	SET(VZPROJECT_LIBRARY_DIR
		)
	SET(VZPROJECT_LINK_LIB
        -Wl,-rpath=.
		    pthread
		    rt
		)
ELSEIF(CMAKE_BUILD_TYPE MATCHES Release)
	MESSAGE(STATUS "       RELEASE MODE")
	MESSAGE(STATUS "       UNIX")
	SET(VZPROJECT_LIBRARY_DIR
		)
	SET(VZPROJECT_LINK_LIB
        -Wl,-rpath=.
		    pthread
		    rt
		)
ENDIF()

MESSAGE(STATUS "SETP 4 : ADD CODE SOURCE")

ADD_DEFINITIONS(
	  -DO2
    -D_LINUX
    -DPOSIX
    -DGENERIC_RELAY
	  -fpermissive
	)

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY  "${PROJECT_SOURCE_DIR}/bin/hisiv300")
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY  "${PROJECT_SOURCE_DIR}/lib/hisiv300")
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY  "${PROJECT_SOURCE_DIR}/lib/hisiv300")

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG  "${PROJECT_SOURCE_DIR}/bin/hisiv300")
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG  "${PROJECT_SOURCE_DIR}/lib/hisiv300")
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG  "${PROJECT_SOURCE_DIR}/lib/hisiv300")

# With Release properties
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE  "${PROJECT_SOURCE_DIR}/bin/hisiv300")
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE  "${PROJECT_SOURCE_DIR}/lib/hisiv300")
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE  "${PROJECT_SOURCE_DIR}/lib/hisiv300")

