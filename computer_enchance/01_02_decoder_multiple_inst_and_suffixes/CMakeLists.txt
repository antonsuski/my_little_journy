cmake_minimum_required(VERSION 3.25)

project(decoder_multy LANGUAGES CXX C)

add_executable(decoder_multy main.cxx
                       x86_decoder.cxx
                       x86_decoder.hxx)
