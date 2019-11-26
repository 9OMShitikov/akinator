#include <iostream>
//#define PRINT_CHECKING
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "strings_read_functions.h"
#include "akinator_functions.h"



int main(int argc, char* argv[]) {
    const char *input_file;
    if (argc > 1) input_file = argv[1];
    else input_file = "akinator_tree";

    int heap_size = 210000;  // default scheme heap size
    int load_init_files = 1; // we want the festival init files loaded

    bool use_audio = false;

    say_and_print("This is akinator.\n\
There are some commands which you can use:\n\
-EA: enable audio\n\
-DA: disable audio.\
        ", use_audio);
    while (true) {

        say_and_print("What do you want?\n\
If you want to choose answer, print 1.\n\
If you want to init a tree, print 2.\n\
If you want do have a description of smb or smth, print 3.\n\
If you want to differ smth from smth, print 4.\n\
If you want to quit, print 5.", use_audio);
        char ans[100];
        while (true) {
            scanf("%s", ans);
            if (check_cmd(ans, use_audio)) {}
            else if (strcmp(ans, "1") == 0) {
                AutoFree<tree_node> nodes;
                size_t tree_size = read_file_with_free_place<tree_node>(&nodes, input_file, 2);
                int split_node = 0;
                if (!check_name(nodes.ptr, 0, tree_size, split_node, use_audio)) {
                    add_name(nodes.ptr, tree_size, split_node, use_audio);
                    print_bin<tree_node>(tree_size, &nodes.ptr, input_file);
                }
                break;
            } else if (strcmp(ans, "2") == 0) {
                say_and_print("Print first name, please.", use_audio);
                AutoFree<tree_node> nodes;
                nodes.ptr = new tree_node();
                get_line_with_endl(nodes.ptr->name);
                print_bin<tree_node>(1, &(nodes.ptr), input_file);
                break;
            } else if (strcmp(ans, "3") == 0) {
                AutoFree<tree_node> nodes;
                size_t tree_size = read_file_with_free_place<tree_node>(&nodes, input_file, 2);
                print_description(nodes.ptr, use_audio);
                break;
            } else if (strcmp(ans, "4") == 0) {
                AutoFree<tree_node> nodes;
                size_t tree_size = read_file_with_free_place<tree_node>(&nodes, input_file, 2);
                print_difference(nodes.ptr, use_audio);
                break;
            } else if (strcmp(ans, "5") == 0) {
                return 0;
            } else {
                say_and_print("Please, answer correctly.", use_audio);
            }
        }
    }
    return 0;
}