# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "exercise2: 1 messages, 1 services")

set(MSG_I_FLAGS "-Iexercise2:/home/marco/IntelligentRobotics/exercise2_ws/src/exercise2/msg;-Istd_msgs:/opt/ros/noetic/share/std_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(geneus REQUIRED)
find_package(genlisp REQUIRED)
find_package(gennodejs REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(exercise2_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/marco/IntelligentRobotics/exercise2_ws/src/exercise2/msg/Message.msg" NAME_WE)
add_custom_target(_exercise2_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "exercise2" "/home/marco/IntelligentRobotics/exercise2_ws/src/exercise2/msg/Message.msg" ""
)

get_filename_component(_filename "/home/marco/IntelligentRobotics/exercise2_ws/src/exercise2/srv/Service.srv" NAME_WE)
add_custom_target(_exercise2_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "exercise2" "/home/marco/IntelligentRobotics/exercise2_ws/src/exercise2/srv/Service.srv" "exercise2/Message:std_msgs/Header"
)

#
#  langs = gencpp;geneus;genlisp;gennodejs;genpy
#

### Section generating for lang: gencpp
### Generating Messages
_generate_msg_cpp(exercise2
  "/home/marco/IntelligentRobotics/exercise2_ws/src/exercise2/msg/Message.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/exercise2
)

### Generating Services
_generate_srv_cpp(exercise2
  "/home/marco/IntelligentRobotics/exercise2_ws/src/exercise2/srv/Service.srv"
  "${MSG_I_FLAGS}"
  "/home/marco/IntelligentRobotics/exercise2_ws/src/exercise2/msg/Message.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/exercise2
)

### Generating Module File
_generate_module_cpp(exercise2
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/exercise2
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(exercise2_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(exercise2_generate_messages exercise2_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/marco/IntelligentRobotics/exercise2_ws/src/exercise2/msg/Message.msg" NAME_WE)
add_dependencies(exercise2_generate_messages_cpp _exercise2_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/marco/IntelligentRobotics/exercise2_ws/src/exercise2/srv/Service.srv" NAME_WE)
add_dependencies(exercise2_generate_messages_cpp _exercise2_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(exercise2_gencpp)
add_dependencies(exercise2_gencpp exercise2_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS exercise2_generate_messages_cpp)

### Section generating for lang: geneus
### Generating Messages
_generate_msg_eus(exercise2
  "/home/marco/IntelligentRobotics/exercise2_ws/src/exercise2/msg/Message.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/exercise2
)

### Generating Services
_generate_srv_eus(exercise2
  "/home/marco/IntelligentRobotics/exercise2_ws/src/exercise2/srv/Service.srv"
  "${MSG_I_FLAGS}"
  "/home/marco/IntelligentRobotics/exercise2_ws/src/exercise2/msg/Message.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/exercise2
)

### Generating Module File
_generate_module_eus(exercise2
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/exercise2
  "${ALL_GEN_OUTPUT_FILES_eus}"
)

add_custom_target(exercise2_generate_messages_eus
  DEPENDS ${ALL_GEN_OUTPUT_FILES_eus}
)
add_dependencies(exercise2_generate_messages exercise2_generate_messages_eus)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/marco/IntelligentRobotics/exercise2_ws/src/exercise2/msg/Message.msg" NAME_WE)
add_dependencies(exercise2_generate_messages_eus _exercise2_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/marco/IntelligentRobotics/exercise2_ws/src/exercise2/srv/Service.srv" NAME_WE)
add_dependencies(exercise2_generate_messages_eus _exercise2_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(exercise2_geneus)
add_dependencies(exercise2_geneus exercise2_generate_messages_eus)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS exercise2_generate_messages_eus)

### Section generating for lang: genlisp
### Generating Messages
_generate_msg_lisp(exercise2
  "/home/marco/IntelligentRobotics/exercise2_ws/src/exercise2/msg/Message.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/exercise2
)

### Generating Services
_generate_srv_lisp(exercise2
  "/home/marco/IntelligentRobotics/exercise2_ws/src/exercise2/srv/Service.srv"
  "${MSG_I_FLAGS}"
  "/home/marco/IntelligentRobotics/exercise2_ws/src/exercise2/msg/Message.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/exercise2
)

### Generating Module File
_generate_module_lisp(exercise2
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/exercise2
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(exercise2_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(exercise2_generate_messages exercise2_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/marco/IntelligentRobotics/exercise2_ws/src/exercise2/msg/Message.msg" NAME_WE)
add_dependencies(exercise2_generate_messages_lisp _exercise2_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/marco/IntelligentRobotics/exercise2_ws/src/exercise2/srv/Service.srv" NAME_WE)
add_dependencies(exercise2_generate_messages_lisp _exercise2_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(exercise2_genlisp)
add_dependencies(exercise2_genlisp exercise2_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS exercise2_generate_messages_lisp)

### Section generating for lang: gennodejs
### Generating Messages
_generate_msg_nodejs(exercise2
  "/home/marco/IntelligentRobotics/exercise2_ws/src/exercise2/msg/Message.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/exercise2
)

### Generating Services
_generate_srv_nodejs(exercise2
  "/home/marco/IntelligentRobotics/exercise2_ws/src/exercise2/srv/Service.srv"
  "${MSG_I_FLAGS}"
  "/home/marco/IntelligentRobotics/exercise2_ws/src/exercise2/msg/Message.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/exercise2
)

### Generating Module File
_generate_module_nodejs(exercise2
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/exercise2
  "${ALL_GEN_OUTPUT_FILES_nodejs}"
)

add_custom_target(exercise2_generate_messages_nodejs
  DEPENDS ${ALL_GEN_OUTPUT_FILES_nodejs}
)
add_dependencies(exercise2_generate_messages exercise2_generate_messages_nodejs)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/marco/IntelligentRobotics/exercise2_ws/src/exercise2/msg/Message.msg" NAME_WE)
add_dependencies(exercise2_generate_messages_nodejs _exercise2_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/marco/IntelligentRobotics/exercise2_ws/src/exercise2/srv/Service.srv" NAME_WE)
add_dependencies(exercise2_generate_messages_nodejs _exercise2_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(exercise2_gennodejs)
add_dependencies(exercise2_gennodejs exercise2_generate_messages_nodejs)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS exercise2_generate_messages_nodejs)

### Section generating for lang: genpy
### Generating Messages
_generate_msg_py(exercise2
  "/home/marco/IntelligentRobotics/exercise2_ws/src/exercise2/msg/Message.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/exercise2
)

### Generating Services
_generate_srv_py(exercise2
  "/home/marco/IntelligentRobotics/exercise2_ws/src/exercise2/srv/Service.srv"
  "${MSG_I_FLAGS}"
  "/home/marco/IntelligentRobotics/exercise2_ws/src/exercise2/msg/Message.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/exercise2
)

### Generating Module File
_generate_module_py(exercise2
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/exercise2
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(exercise2_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(exercise2_generate_messages exercise2_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/marco/IntelligentRobotics/exercise2_ws/src/exercise2/msg/Message.msg" NAME_WE)
add_dependencies(exercise2_generate_messages_py _exercise2_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/marco/IntelligentRobotics/exercise2_ws/src/exercise2/srv/Service.srv" NAME_WE)
add_dependencies(exercise2_generate_messages_py _exercise2_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(exercise2_genpy)
add_dependencies(exercise2_genpy exercise2_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS exercise2_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/exercise2)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/exercise2
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_cpp)
  add_dependencies(exercise2_generate_messages_cpp std_msgs_generate_messages_cpp)
endif()

if(geneus_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/exercise2)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/exercise2
    DESTINATION ${geneus_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_eus)
  add_dependencies(exercise2_generate_messages_eus std_msgs_generate_messages_eus)
endif()

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/exercise2)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/exercise2
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_lisp)
  add_dependencies(exercise2_generate_messages_lisp std_msgs_generate_messages_lisp)
endif()

if(gennodejs_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/exercise2)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/exercise2
    DESTINATION ${gennodejs_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_nodejs)
  add_dependencies(exercise2_generate_messages_nodejs std_msgs_generate_messages_nodejs)
endif()

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/exercise2)
  install(CODE "execute_process(COMMAND \"/usr/bin/python3\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/exercise2\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/exercise2
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_py)
  add_dependencies(exercise2_generate_messages_py std_msgs_generate_messages_py)
endif()
