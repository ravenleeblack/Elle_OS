#ifndef sub_frame_h
#define sub_frame_h
#include "frame_bitmap.h"
#include "main_frame.h" 


// Forward declaration
struct main_frame;

struct sub_frame
{
    struct kinship_element *kinship_tag;
    struct index_element *label_index_tag;
    struct draw_element *element;
    struct sequence_queue *queue;
};

struct sub_frame *create_sub_frame(struct main_frame *parent, int x, int y, int width, int height);

#endif