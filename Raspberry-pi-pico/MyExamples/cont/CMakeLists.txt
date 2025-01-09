# garante a versao correta do CMake
cmake_minimum_required(VERSION 3.21)

#inclusao do caminho do SDK do Raspberry Pi Pico
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

#Define o nome do projeto "cont" e as linguagens que usara "C, C++, e Assembly"
project(cont C CXX ASM)

#Inicia o SDK
pico_sdk_init()

#Adiciona o executavel
add_executable(cont
    cont.c
)

#linka as bibliotecas necessarias
target_link_libraries(cont pico_stdlib)

#faz a adicao dos arquivos UF2 e BIN para poder executar o programa
pico_add_extra_outputs(cont)

# Faz com que a porta COM apareca, necessita do stdio_init_all();
pico_enable_stdio_usb(cont 1)