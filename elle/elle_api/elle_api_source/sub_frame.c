#include "sub_frame.h"


struct sub_frame *create_sub_frame(struct main_frame *parent, int x, int y, int width, int height)
{
    struct sub_frame *sub_frame = (struct sub_frame *)core_malloc(sizeof(struct sub_frame));
    if (sub_frame == NULL) {
        return NULL;
    }

    if (parent != NULL) {
        sub_frame->element = create_sub_element(parent->element, x, y, width, height);
    } else {
        sub_frame->element = create_sub_element(NULL, x, y, width, height);
    }

    // Initialize other fields
    sub_frame->kinship_tag = NULL;
    sub_frame->label_index_tag = NULL;
    sub_frame->queue = NULL;

    return sub_frame;
}