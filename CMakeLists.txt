cmake_minimum_required(VERSION 2.6)
file(TO_CMAKE_PATH "$ENV{IMAGINEPP_ROOT}/CMake" p)
list(APPEND CMAKE_MODULE_PATH "${p}") #For old Imagine++
list(APPEND CMAKE_SYSTEM_FRAMEWORK_PATH /Library/Frameworks) #Mac, why not auto?
find_package(Imagine REQUIRED)

project(Jeu_portal)


add_executable(Jeu_portal Jeu_portal.cpp mvtperso.cpp mvtperso.h Plateformes.h Plateforme.cpp Portail.h Portail.cpp)
ImagineUseModules(Jeu_portal Graphics)
