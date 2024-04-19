#include <>


int main(int argc, char *argv[]) {
    // argv[0] -> kv
    for (int i = 1; i < argc; i++) {
        readFile(argv[i]);
    }
    return 0;
}