#include "Application.h"

int main(int argc, char* argv[])
{
    Application app;
    int res = static_cast<int>(app.start(argc, argv));
    return res;
}