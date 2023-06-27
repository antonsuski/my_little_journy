cmake_minimum_required(VERSION 3.25)

project(decoder LANGUAGES CXX C)

add_executable(decoder main.cxx
                       x86_decoder.cxx
                       x86_decoder.hxx)
