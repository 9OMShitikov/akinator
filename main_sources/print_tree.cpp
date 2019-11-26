#include <iostream>

#include <vector>
#include <string_view>
#include <cstdlib>
#include <string.h>
#include <stdio.h>
#include "strings_read_functions.h"
#include "akinator_functions.h"
#include "print_tree_functions.h"

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

    char str[256];
    sprintf(str, "dot -O -Tpng %s", output_file);
    system(str);
    char* buff;
}