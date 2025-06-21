#include "sf/result.h"
#include <sf/window.h>
#include <stdlib.h>

#include "sf/meshes.h"

int main() {
    // Prepare window
    sf_window *win;
    register sf_result res = sf_window_new(&win, sf_lit("Window"), (sf_vec2){1280, 720});
    if (!res.ok) {
        perror(res.err.c_str);
        return EXIT_FAILURE;
    }
    sf_discard(res);

    // Prepare shader
    sf_shader shader;
    res = sf_shader_new(&shader, sf_lit("shaders/default"));
    if (!res.ok) {
        perror(res.err.c_str);
        return EXIT_FAILURE;
    }
    sf_discard(res);

    // Prepare texture
    sf_texture chaser;
    res = sf_texture_cload(&chaser, "chaser.jpg");
    if (!res.ok) {
        perror(res.err.c_str);
        return EXIT_FAILURE;
    }
    sf_discard(res);
    sf_texture reactor;
    res = sf_texture_cload(&reactor, "reactor.jpg");
    if (!res.ok) {
        perror(res.err.c_str);
        return EXIT_FAILURE;
    }
    sf_discard(res);
    sf_texture pickmeup;
    res = sf_texture_cload(&pickmeup, "pickmeup.jpg");
    if (!res.ok) {
        perror(res.err.c_str);
        return EXIT_FAILURE;
    }
    sf_discard(res);

    // Prepare quad to display texture
    sf_mesh mesh = sf_mesh_new();
    sf_mesh_add_vertices(&mesh, (sf_vertex[]){
        {{-0.5f, -0.5f, 0}, {0, 1}, sf_rgbagl(SF_WHITE)},
        {{-0.5f, 0.5f, 0}, {0, 0}, sf_rgbagl(SF_WHITE)},
        {{0.5f, -0.5f, 0}, {1, 1}, sf_rgbagl(SF_WHITE)},

        {{0.5f, 0.5f, 0}, {1, 0}, sf_rgbagl(SF_WHITE)},
        {{0.5f, -0.5f, 0}, {1, 1}, sf_rgbagl(SF_WHITE)},
        {{-0.5f, 0.5f, 0}, {0, 0}, sf_rgbagl(SF_WHITE)},
    }, 6);

    // Transform and camera
    sf_transform chaser_t = SF_TRANSFORM_IDENTITY;

    sf_transform reactor_t = SF_TRANSFORM_IDENTITY;
    reactor_t.parent = &chaser_t;
    reactor_t.position = (sf_vec3){1.25f, 0, 0};
    reactor_t.scale = (sf_vec3){0.75f, 0.75f, 0.75f};

    sf_transform pickmeup_t = SF_TRANSFORM_IDENTITY;
    pickmeup_t.parent = &reactor_t;
    pickmeup_t.position = (sf_vec3){0, 1.25f, 0};
    pickmeup_t.scale = (sf_vec3){0.75f, 0.75f, 0.75f};

    sf_camera cam = sf_camera_perspective(75, win->size.x/win->size.y, 0.1f, 100.0f);
    cam.transform.position.z = 2.5f;

    while (sf_window_loop(win)) {
        // Rotate slowly
        chaser_t.rotation.y += 0.01f;
        reactor_t.rotation.y += 0.005f;
        pickmeup_t.rotation.y += 0.0025f;

        res = sf_mesh_draw(&mesh, &shader, &cam, chaser_t, &chaser);
        if (!res.ok)
            printf("Draw Error: %s\n", res.err.c_str);
        sf_discard(res);
        res = sf_mesh_draw(&mesh, &shader, &cam, reactor_t, &reactor);
        if (!res.ok)
            printf("Draw Error: %s\n", res.err.c_str);
        sf_discard(res);
        res = sf_mesh_draw(&mesh, &shader, &cam, pickmeup_t, &pickmeup);
        if (!res.ok)
            printf("Draw Error: %s\n", res.err.c_str);
        sf_discard(res);

        sf_window_draw(win, &cam);
    }

    return EXIT_SUCCESS;
}
