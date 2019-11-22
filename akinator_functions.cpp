enum node_types {
    question = 980710257,
    result = 980643425,

};

enum child_types {
    yes = 980641145,
    no = 980381194,
};

class tree_node {
public:
    node_types type;
    char name[128];
    child_types type_yes = yes;
    size_t pos_yes;
    child_types type_no = no;
    size_t pos_no;
    int c = '\n';
    tree_node () {
        type = result;
        for (int i = 0; i < 128; ++i) name[i] = 0;
        name[127] = '\n';
    }
};

bool check_name (tree_node* tree, int pos, size_t size, int& last_ans) {
    ASSERT(tree);
    ASSERT(pos < size);
    ASSERT(pos >= 0);
    if (tree[pos].name[0] != 0)
        tree[pos].name[0] = toupper(tree[pos].name[0]);
    char buff[512];
    sprintf(buff, "%s%c", tree[pos].name, '?');
    say_and_print(buff);
    say_and_print("Answer \"N\" if no, \"Y\" if yes.");
    if (tree[pos].type == question)
        say_and_print("If probably yes, print \"PY\", if probably no, print \"PN\"");
    char ans[100];

    if (tree[pos].type == question) {

        while (true) {
            scanf("%s", ans);
            if (strcmp(ans, "Y") == 0) {
                return check_name(tree, tree[pos].pos_yes, size, last_ans);
            } else if (strcmp(ans, "N") == 0) {
                return check_name(tree, tree[pos].pos_no, size, last_ans);
            } else if (strcmp(ans, "PN") == 0) {
                bool fl = check_name(tree, tree[pos].pos_no, size, last_ans);
                if (!fl) {
                    int tmp;
                    fl = check_name(tree, tree[pos].pos_yes, size, tmp);
                }
                return fl;
            } else if (strcmp(ans, "PY") == 0) {
                bool fl = check_name(tree, tree[pos].pos_yes, size, last_ans);
                if (!fl) {
                    int tmp;
                    fl = check_name(tree, tree[pos].pos_no, size, tmp);
                }
                return fl;
            } else {
                say_and_print("Please, answer correctly.");
            }
        }
    }
    else if (tree[pos].type == result) {
        while (true) {
            scanf("%s", ans);
            last_ans = pos;
            if (strcmp(ans, "Y") == 0) {
                return true;
            } else if (strcmp(ans, "N") == 0) {
                return false;
            } else {
                say_and_print("Please, answer correctly.\n");
            }
        }
    }
    else {
        std::cerr<<"What???";
        throw std::exception();
    }
}

void add_name(tree_node* tree, size_t& size, int split_pos) {
    ASSERT(tree);
    ASSERT(split_pos >= 0);
    ASSERT(split_pos < size);

    new (tree + size) tree_node;
    new (tree + (size + 1)) tree_node;
    strcpy(tree[size].name, tree[split_pos].name);
    tree[split_pos].type = question;
    tree[split_pos].pos_no = size;
    tree[split_pos].pos_yes = size + 1;

    say_and_print("What was it?");
    get_line_with_endl(tree[size + 1].name);
    if (tree[size + 1].name[0] != 0)
        tree[size + 1].name[0] = tolower(tree[size + 1].name[0]);
    if (tree[size].name[0] != 0)
        tree[size].name[0] = tolower(tree[size].name[0]);

    char buff[512];
    sprintf(buff, "Print, in what %s is different from %s?", tree[size + 1].name, tree[size].name);
    say_and_print(buff);
    get_line_with_endl(tree[split_pos].name);
    size += 2;
}
