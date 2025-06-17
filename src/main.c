#include "sf/result.h"
#include <sf/window.h>
#include <stdlib.h>

int main() {
    mat4 projection;
    glm_ortho(0, 1280, 0, 720, -10, 100, projection);
    sf_window *win;
    const sf_result res = sf_window_new(&win, sf_lit("Window"), (sf_vec2){1280, 720});
    if (!res.ok) {
        perror(res.err.c_str);
        return EXIT_FAILURE;
    }

    sf_camera cam = sf_camera_new(60, projection);
    while (sf_window_loop(win)) {
        sf_window_draw(win, &cam);
    }
}
