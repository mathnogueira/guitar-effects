#include <plugins/pyPlugin.h>

using namespace AudioFX;

int main(int argc, char* argv[])
{
    PyPlugin plugin("amps.simple");
    plugin.initialize();
    plugin.getOptions();
    return 0;
}