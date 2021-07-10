cmake_minimum_required(VERSION 3.0)
project( agenda )

SET(name agenda)

get_directory_property(_vars VARIABLES)

list(APPEND SOURCES
    src/date/date.c
    src/date/horaire.c
    src/menu/menu.c
    src/rdv/rdv.c
    src/main.c
)

add_executable( ${name} ${SOURCES})

target_link_libraries( ${name})
