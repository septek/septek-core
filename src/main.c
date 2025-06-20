#include "sf/result.h"
#include <sf/window.h>
#include <stdlib.h>

#include "sf/meshes.h"

int main() {
    mat4 projection;
    glm_perspective(glm_rad(90), 1280.0f/720.0f, 1, 100, projection);

    sf_window *win;
    register sf_result res = sf_window_new(&win, sf_lit("Window"), (sf_vec2){1280, 720});
    if (!res.ok) {
        perror(res.err.c_str);
        return EXIT_FAILURE;
    }

    sf_mesh mesh = sf_mesh_new();
    sf_mesh_add_vertices(&mesh, (sf_vertex[]){
        { .position = {0, 0, 0}, .color = sf_rgbagl(SF_WHITE), .uv = {0, 0} },
        { .position = {10, 0, 0}, .color = sf_rgbagl(SF_WHITE), .uv = {0, 0} },
        { .position = {0,  10, 0}, .color = sf_rgbagl(SF_WHITE), .uv = {0, 0} },

        { .position = {10,  10, 0}, .color = sf_rgbagl(SF_WHITE), .uv = {0, 0} },
        { .position = { 0, 10, 0}, .color = sf_rgbagl(SF_WHITE), .uv = {0, 0} },
        { .position = { 10,  0, 0}, .color = sf_rgbagl(SF_WHITE), .uv = {0, 0} },
    }, 6);

    sf_shader shader;
    res = sf_shader_new(&shader, sf_lit("shaders/default"));
    if (!res.ok) {
        perror(res.err.c_str);
        return EXIT_FAILURE;
    }

    sf_camera cam = sf_camera_new(60, projection);
    while (sf_window_loop(win)) {
        if (sf_key_check(win, SF_KEY_W))
            cam.transform.position.z -= 0.1f;
        if (sf_key_check(win, SF_KEY_A))
            cam.transform.position.x -= 0.1f;
        if (sf_key_check(win, SF_KEY_S))
            cam.transform.position.z += 0.1f;
        if (sf_key_check(win, SF_KEY_D))
            cam.transform.position.x += 0.1f;
        if (sf_key_check(win, SF_KEY_SPACE))
            cam.transform.position.y += 0.1f;
        if (sf_key_check(win, SF_KEY_LEFT_SHIFT))
            cam.transform.position.y -= 0.1f;

        if (sf_key_check(win, SF_KEY_I))
            cam.transform.rotation.x -= 0.05f;
        if (sf_key_check(win, SF_KEY_J))
            cam.transform.rotation.y += 0.05f;
        if (sf_key_check(win, SF_KEY_K))
            cam.transform.rotation.x += 0.05f;
        if (sf_key_check(win, SF_KEY_L))
            cam.transform.rotation.y -= 0.05f;

        res = sf_mesh_draw(&mesh, &shader, &cam, (sf_transform){
            {0, 0, 0},
            {0, 0, 0},
            {1, 1, 1},
        });
        if (!res.ok)
            printf("Draw Error: %s\n", res.err.c_str);

        sf_window_draw(win, &cam);
    }
}
