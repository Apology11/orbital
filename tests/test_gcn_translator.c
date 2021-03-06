/**
 * (c) 2019 Alexandro Sanchez Bach. All rights reserved.
 * Released under MIT license. Read LICENSE for more details.
 */

#include "gcn_analyzer.h"
#include "gcn_translator.h"
#include "gcn_parser.h"

#include <stdio.h>
#include <stdlib.h>

#define UNUSED(arg) (void)(arg)

static int translate_shader(const uint8_t *data, size_t size)
{
    UNUSED(data);
    UNUSED(size);

    return 0;
}

int main(int argc, const char **argv)
{
    size_t shader_size;
    uint8_t *shader_data;
    const char *name;
    FILE *file;
    int ret;

    if (argc <= 1) {
        fprintf(stderr, "Usage: %s [path/to/shader.bin]\n", argv[0]);
        return 0;
    }

    name = argv[1];
    file = fopen(name, "rb");
    if (!file) {
        fprintf(stderr, "File %s does not exist!\n", name);
        return 1;
    }
    fseek(file, 0, SEEK_END);
    shader_size = ftell(file);
    shader_data = malloc(shader_size);
    if (!shader_data) {
        fprintf(stderr, "Could not allocate 0x%zX bytes!\n", shader_size);
        return 1;
    }
    fseek(file, 0, SEEK_SET);
    if (fread(shader_data, 1, shader_size, file) != shader_size) {
        fprintf(stderr, "Could not read 0x%zX bytes!\n", shader_size);
        return 1;
    }
    ret = translate_shader(shader_data, shader_size);
    free(shader_data);
    fclose(file);

    return ret;
}
