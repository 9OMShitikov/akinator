#include <iostream>

#include <vector>
#include <string_view>
#include <cstdlib>
#include <string.h>
#include <stdio.h>
#include "strings_read_functions.h"
#include "akinator_functions.cpp"

void add_node (char** buff, tree_node* node_ptr, ssize_t ind, size_t& size, size_t& taken) {
    ASSERT(buff);
    ASSERT(node_ptr);
    add_string_to_buff(buff, size, taken, "v");
    add_int_to_buff(buff, size, taken, ind);
    add_string_to_buff(buff, size, taken, " [label = \"");
    add_string_to_buff(buff, size, taken, node_ptr->name);
    if (node_ptr->type == question) {
        add_string_to_buff(buff, size, taken, "?\", style = filled, color = powderblue]\n");
    }
    else {
        add_string_to_buff(buff, size, taken, "\", style = filled, color = orangered]\n");
    }
}

void add_edges (char** buff, tree_node* node_ptr, ssize_t ind, size_t& size, size_t& taken) {
    ASSERT(buff);
    ASSERT(node_ptr);
    if (node_ptr->type == question) {
        add_string_to_buff(buff, size, taken, "v");
        add_int_to_buff(buff, size, taken, ind);
        add_string_to_buff(buff, size, taken, "->v");
        add_int_to_buff(buff, size, taken, node_ptr->pos_no);
        add_string_to_buff(buff, size, taken, " [label = \"No\"]\n");

        add_string_to_buff(buff, size, taken, "v");
        add_int_to_buff(buff, size, taken, ind);
        add_string_to_buff(buff, size, taken, "->v");
        add_int_to_buff(buff, size, taken, node_ptr->pos_yes);
        add_string_to_buff(buff, size, taken, " [label = \"Yes\"]\n");

        add_string_to_buff(buff, size, taken, "{rank = same; ");
        add_string_to_buff(buff, size, taken, "v");
        add_int_to_buff(buff, size, taken, node_ptr->pos_no);
        add_string_to_buff(buff, size, taken, ", ");
        add_string_to_buff(buff, size, taken, "v");
        add_int_to_buff(buff, size, taken, node_ptr->pos_yes);
        add_string_to_buff(buff, size, taken, "}\n");
    }
}

int main(int argc, char* argv[]) {
    const char *input_file = nullptr;
    if (argc > 1) input_file = argv[1];
    else input_file = "akinator_tree";

    const char *output_file = nullptr;
    if (argc > 2) output_file = argv[2];
    else output_file = "tree_graph.dot";

    AutoFree<tree_node> tree_nodes;

    AutoFree<char> str_buff;
    str_buff.ptr = new char(0);
    size_t buff_size = 1;
    size_t buff_taken = 0;

    int size = read_bin<tree_node> (&tree_nodes, input_file);

    add_string_to_buff(&(str_buff.ptr), buff_size, buff_taken, "digraph akinator_tree {\n");

    for (int i = 0; i < size; ++i) {
        add_node(&(str_buff.ptr), tree_nodes.ptr + i, i, buff_size, buff_taken);
    }
    for (int i = 0; i < size; ++i) {
        add_edges(&(str_buff.ptr), tree_nodes.ptr + i, i, buff_size, buff_taken);
    }
    add_string_to_buff(&(str_buff.ptr), buff_size, buff_taken, "}\n");

    clear_output(output_file);
    print_buff(buff_taken, &str_buff, output_file);
    char* buff;
}