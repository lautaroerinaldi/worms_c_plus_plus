cmake_minimum_required(VERSION 2.8)

project(Worms)

find_package (PkgConfig REQUIRED)
pkg_check_modules(GTKMM REQUIRED gtkmm-3.0)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(${PROJECT_BINARY_DIR})
include_directories(${PROJECT_SOURCE_DIR})

FILE(GLOB_RECURSE vista "vista/componentes/*.cpp" "vista/componentes/*.h"
                        "vista/elementos/*.cpp" "vista/elementos/*.h"
                        "vista/estadosGusanos/*.cpp" "vista/estadosGusanos/*.h"
                        "vista/estadosJuego/*.cpp" "vista/estadosJuego/*.h"
                        "vista/eventos/*.cpp" "vista/eventos/*.h")

FILE(GLOB_RECURSE protocolo 	"comun/Protocolo/Armas/*.h" "comun/Protocolo/Armas/*.cpp"
				"comun/Protocolo/Balas/*.h" "comun/Protocolo/Balas/*.cpp"
				"comun/Protocolo/ControlMaquinaDeEstados/*.h" "comun/Protocolo/ControlMaquinaDeEstados/*.cpp"
				"comun/Protocolo/ControlPartidas/*.h" "comun/Protocolo/ControlPartidas/*.cpp"
				"comun/Protocolo/ErroresYNotificaciones/*.h" "comun/Protocolo/ErroresYNotificaciones/*.cpp"
				"comun/Protocolo/Escenario/*.h" "comun/Protocolo/Escenario/*.cpp"
				"comun/Protocolo/MovimientosGusanos/*.h" "comun/Protocolo/MovimientosGusanos/*.cpp"
				"comun/Protocolo/Solicitudes/*.h" "comun/Protocolo/Solicitudes/*.cpp"
				"comun/Protocolo/Turnos/*.h" "comun/Protocolo/Turnos/*.cpp"
				"comun/Protocolo/Visuales/*.h" "comun/Protocolo/Visuales/*.cpp")

FILE(GLOB_RECURSE controllerClient	"comun/*.h" "comun/*.cpp"
                                        "comun/Sockets/*.h" "comun/Sockets/*.cpp"
                                        "comun/Threads/*.h" "comun/Threads/*.cpp"
                                        "comun/Utiles/*.h" "comun/Utiles/*.cpp"
                                        "cliente/*.h" "cliente/*.cpp")

FILE(GLOB_RECURSE controllerServidor	"comun/*.h" "comun/*.cpp"
                                	"comun/Sockets/*.h" "comun/Sockets/*.cpp"
			                "comun/Threads/*.h" "comun/Threads/*.cpp"
			                "comun/Utiles/*.h" "comun/Utiles/*.cpp"
			                "servidor/*.h" "servidor/*.cpp")

FILE(GLOB_RECURSE editor "editor/*.h" "editor/*.cpp")
FILE(GLOB_RECURSE glade "editor/*.glade")
FILE(GLOB_RECURSE images "../img/*")
FILE(GLOB_RECURSE fuentes "../fonts/*")
FILE(GLOB_RECURSE sonidos "../sound/*")
FILE(GLOB_RECURSE escenarios "../escenarios/*")
FILE(GLOB_RECURSE comun "comun/*")
FILE(GLOB_RECURSE b2d "Box2D/*.h" "Box2D/*.cpp")
FILE(GLOB_RECURSE modelo "modelo/*.h" "modelo/*.cpp")

include_directories(Yaml)

FILE(GLOB_RECURSE yaml "Yaml/*.h" "Yaml/*.cpp")

add_library(yaml ${yaml})

add_library(Box2D ${b2d})

add_executable (cliente
  ${protocolo}
  ${controllerClient}
  ${vista}
)

add_executable (servidor
	parsers/ParserEscenario.h
	parsers/ParserEscenario.cpp
	${protocolo}
	${modelo}
	${controllerServidor}
	${comun})

#editor
add_executable(editor
              ${editor}
)

target_link_libraries(cliente SDL2 SDL2_image  SDL2_ttf SDL2_mixer pthread)
target_link_libraries(servidor pthread Box2D yaml)

include_directories (${GTKMM_INCLUDE_DIRS})
link_directories (${GTKMM_LIBRARY_DIRS})
add_definitions (${GTKMM_CFLAGS_OTHER})
target_link_libraries(editor ${GTKMM_LIBRARIES} yaml glibmm-2.4)

install(FILES ${images} DESTINATION ${CMAKE_BINARY_DIR}/img)

install(FILES ${fuentes} DESTINATION ${CMAKE_BINARY_DIR}/font)

install(FILES ${sonidos} DESTINATION ${CMAKE_BINARY_DIR}/sound)

install(FILES ${escenarios} DESTINATION ${CMAKE_BINARY_DIR}/escenarios)

install(FILES ${glade} DESTINATION ${CMAKE_BINARY_DIR}/glade)

