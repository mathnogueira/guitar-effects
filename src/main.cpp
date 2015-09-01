#include <plugins/pyPlugin.h>
#include <plugins/option.h>
#include <vector>

using namespace AudioFX;

int main(int argc, char* argv[])
{
    PyPlugin plugin("amps.simple");
    plugin.initialize();
    plugin.importOptions();
    std::vector<PluginOption*> options = plugin.getOptions();
    for (unsigned int i = 0; i < options.size(); ++i) {
        options[i]->setValue(i * 3);
    }
    plugin.applyOptions();
    plugin.execute();
    return 0;
}