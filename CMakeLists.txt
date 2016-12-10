cmake_minimum_required(VERSION 2.6)
if(COMMAND cmake_policy)
  cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)

project(Ensidu)
enable_testing()
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -Wall -std=gnu11")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -std=gnu++11")

#########
# Gestion des logins
#########
# Vous devez editer la ligne suivante pour y mettre votre login
#########
set(LOGINS login1)

if (LOGINS MATCHES "login1")
  message(FATAL_ERROR "** ERREUR / ERROR **: Vous devez modifier CMakeLists.txt pour remplacer login1 par votre login / Substitute login1 with your own login in CMakeLists.txt")
endif()



##
# Si vous utilisez d'autres fichiers .c, en plus de ceux listés,
# il faut les ajouter ici
##
add_executable(ensivoies src/ensivoies.c src/trainmonitor.c src/train.c)
target_link_libraries(ensivoies pthread)


##
# Programme de test
##
add_test(ExecutionVoies perl ${CMAKE_SOURCE_DIR}/tests/execvoies.pl)
add_test(Train perl ${CMAKE_SOURCE_DIR}/tests/train.pl)
add_test(CinqTrains perl ${CMAKE_SOURCE_DIR}/tests/voies5threads.pl)
add_test(JoinThreads perl ${CMAKE_SOURCE_DIR}/tests/voiesjoin.pl)
add_test(EntrelacementThreads perl ${CMAKE_SOURCE_DIR}/tests/voiesalternance.pl)
add_test(Valgrind perl ${CMAKE_SOURCE_DIR}/tests/memcheckvoies.pl)
add_test(ValgrindHelgrind perl ${CMAKE_SOURCE_DIR}/tests/helgrindvoies.pl)
add_test(ValgrindDRD perl ${CMAKE_SOURCE_DIR}/tests/drdvoies.pl)

set_tests_properties(ExecutionVoies Train CinqTrains JoinThreads EntrelacementThreads Valgrind ValgrindHelgrind ValgrindDRD PROPERTIES TIMEOUT 5)

add_custom_target(check ctest -V)
