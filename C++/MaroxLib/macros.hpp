#pragma once

#ifndef CATCH
#define CATCH catch(const std::exception& ex)
#endif

#ifndef WAIT_FOR_ENTER
#define WAIT_FOR_ENTER() std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
#endif
