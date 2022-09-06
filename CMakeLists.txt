cmake_minimum_required(VERSION 3.10)
project(saboteur C)

set(CMAKE_C_STANDARD 99)

add_executable(saboteur main.c fonctions.h initialisation.c menu.c clavier.c utilitaire.c annoncerole.c carte.c plateau.c pioche.c mouvement_carte.c ia.c)

IF (WIN32)
    target_link_libraries(saboteur -lmingw32 -lallegro-5.0.10-monolith-md-debug)
ELSE ()
    INCLUDE_DIRECTORIES(/usr/local/Cellar/allegro/5.2.6.0/include)
    LINK_DIRECTORIES(/usr/local/Cellar/allegro/5.2.6.0/lib)
    file(GLOB LIBRARIES "/usr/local/Cellar/allegro/5.2.6.0/lib/*.dylib")
    message("LIBRARIES = ${LIBRARIES}")
    TARGET_LINK_LIBRARIES(saboteur ${LIBRARIES})
ENDIF (WIN32)