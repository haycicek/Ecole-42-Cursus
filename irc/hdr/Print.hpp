#pragma once

// include
#include <iostream>
#include <sstream>

enum Color
{
    RED,
    GREEN,
    YELLOW,
    BLUE,
    MAGENTA,
    CYAN,
    WHITE
};

const std::string RESET = "\033[0m";
const std::string COLORS[] = {
    "\033[31m", // RED
    "\033[32m", // GREEN
    "\033[33m", // YELLOW
    "\033[34m", // BLUE
    "\033[35m", // MAGENTA
    "\033[36m", // CYAN
    ""  // WHITE
};

template <typename T>
std::string convertString(const T &variable)
{
    std::ostringstream oss;
    oss << variable;
    return oss.str();
}

template <typename T>
void println(const T &variable , int color = WHITE)
{
    std::cout << COLORS[color] << variable << RESET << std::endl;
}

template <typename T>
void print(const T &variable , int color = WHITE)
{
    std::cout << COLORS[color] << variable << RESET;
}

template <typename T>
void printlnErr(const T &variable , int color = WHITE)
{
    std::cerr << COLORS[color] << variable << RESET << std::endl;
}
