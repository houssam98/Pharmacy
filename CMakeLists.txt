cmake_minimum_required(VERSION 3.7)
project(Pharmacy)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Sources/Products.cpp Headers/Products.hpp Sources/DBMS.cpp Headers/DBMS.hpp Sources/Transactions.cpp Headers/Transactions.hpp Sources/Category.cpp Headers/Category.hpp Sources/Users.cpp Headers/Users.hpp Sources/Orders.cpp Headers/Orders.hpp Sources/Statistics.cpp Headers/Statistics.hpp Users/Customer.cpp Users/Customer.hpp Users/Employee.cpp Users/Employee.hpp Users/Manager.cpp Users/Manager.hpp Users/Admin.cpp Users/Admin.hpp Users/Commands.cpp Users/Commands.h)
add_executable(Pharmacy ${SOURCE_FILES})
TARGET_LINK_LIBRARIES(Pharmacy pq)