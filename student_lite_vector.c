#include "lite_vector.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

lite_vector* lv_new_vec(size_t type_size){
    lite_vector * this_vector = malloc(sizeof(lite_vector));
    this_vector -> length = 0;
    this_vector -> type_size = type_size;
    this_vector -> data = malloc(10 * sizeof(void*));
    this_vector -> max_capacity = 10;
    return this_vector;
}

void lv_cleanup(lite_vector* vec){
    free(vec -> data);
    free(vec);
}

size_t lv_get_length(lite_vector* vec){
    if (vec != NULL) {
        return vec -> length;
    }
    return -1;
}

bool lv_clear(lite_vector* vec){
    if (vec != NULL) {
        vec -> length = 0;
        free(vec -> data);
        vec -> data = malloc(10 * sizeof(void*));
        vec -> max_capacity = 10;
        return true;
    }
    return false;
}

void* lv_get(lite_vector* vec, size_t index){
    if (vec != NULL) {
        return vec -> data[index];
    }
    return NULL;
}

static bool lv_resize(lite_vector* vec){
    void** tempData = malloc(2 * (vec -> length) * sizeof(void*));
    if (tempData == NULL) {
        return 0;
    }
    vec -> max_capacity *= 2;
    int i;
    for (i = 0; i < (vec -> length); i++) {
        tempData[i] = vec -> data[i];
    }
    free(vec -> data);
    vec -> data = tempData;
    return 1;

}

bool lv_append(lite_vector* vec, void* element){
    if (element == NULL ) {
        return 0;
    }
    if (vec -> length == vec -> max_capacity) {
        lv_resize(vec);
    }
    vec -> data[vec -> length] = element;
    vec ->length = vec -> length + 1;

    return 1;

}