#include "formatter_ex.h"

#include "formatter.h"

std::ostream& formatter(std::ostream& out, std::string message)
{
    return out << formatter(message);
}
