#include "sf/dynamic.h"
#include <stdlib.h>

int main() {
    sf_map map = sf_map_new();
    sf_map_cinsert(&map, "lol", &sf_lit("fart"));
    printf("%s\n", sf_map_cget(&map, sf_str, "lol").c_str);
    sf_map_delete(&map);
    return EXIT_SUCCESS;
}
