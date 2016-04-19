#pragma once

#define CATCH catch(const std::exception& ex)
#define WAIT_FOR_ENTER() std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');