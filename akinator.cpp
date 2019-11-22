#include <iostream>

#include <vector>
#include <string_view>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "strings_read_functions.h"
#include "akinator_functions.cpp"


int main(int argc, char* argv[]) {
    const char *input_file;
    if (argc > 1) input_file = argv[1];
    else input_file = "akinator_tree";
    while (true) {
        say_and_print("What do you want?");
        say_and_print("If you want to choose answer, print 1. If you want to init a tree, print 2. If you want to quit, print 3.");
        char ans[100];
        while (true) {
            scanf("%s", ans);
            if (strcmp(ans, "1") == 0) {
                AutoFree<tree_node> nodes;
                size_t tree_size = read_file_with_free_place<tree_node>(&nodes, input_file, 2);
                int split_node = 0;
                if (!check_name(nodes.ptr, 0, tree_size, split_node)) {
                    add_name(nodes.ptr, tree_size, split_node);
                    print_bin<tree_node>(tree_size, &nodes.ptr, input_file);
                }
                break;
            } else if (strcmp(ans, "2") == 0) {
                say_and_print("Print first name, please.");
                AutoFree<tree_node> nodes;
                nodes.ptr = new tree_node();
                get_line_with_endl(nodes.ptr->name);
                print_bin<tree_node>(1, &(nodes.ptr), input_file);
                break;
            } else if (strcmp(ans, "3") == 0) {
                return 0;
            } else {
                say_and_print("Please, answer correctly.");
            }
        }
    }
    return 0;
}