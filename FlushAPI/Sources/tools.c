#include <unistd.h>
#include <string.h>
#include "../Headers/tools.h"

char * getRootDir() {
    char * path = NULL;
    path = getcwd(path, 256 * sizeof(char));
    char * root_dir_name = "cmake-build-debug";
    path[strlen(path) - strlen(root_dir_name)] = '\0';
    return path;
}