#include "PacketsManager.h"


int main() {

    PacketsManager manager;
    manager.read_disk_c_size();
    manager.read_from_config_file();


    bool st = true;
    while (st){

        manager.read();
        st = false;
    }
}
