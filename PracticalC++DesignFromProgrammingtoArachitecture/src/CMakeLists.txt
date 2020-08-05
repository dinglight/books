cmake_minimum_required(VERSION 3.5)

project(calc)

set(CMAKE_CXX_STANDARD 17)

set(SRCS
    Publisher.cpp
    Observer.cpp
    UserInterface.cpp
    Tokenizer.cpp
    CommandDispatcher.cpp
    CommandIssuedObserver.cpp
    Command.cpp
    CommandRepository.cpp
    CoreCommands.cpp
    Stack.cpp
    StackUpdatedObserver.cpp
    Cli.cpp
    cli_main.cpp
    )
#add_library(${PROJECT_NAME} ${SRCS})
add_executable(${PROJECT_NAME} ${SRCS})

target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
)
