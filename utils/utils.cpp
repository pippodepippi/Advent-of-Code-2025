#include "utils.h"

std::string getInputPath(int argc, char** argv,
                         const std::string& default_file)
{
    if (argc > 1) {
        return argv[1];
    }

#ifdef INPUT_DIR
    return std::string(INPUT_DIR) + "/" + default_file;
#else
    return default_file; // fallback
#endif

}


std::ifstream openFile(const std::string& filename)
{
    std::ifstream file(filename);

    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file: " + filename);
    }

    return file;
}
