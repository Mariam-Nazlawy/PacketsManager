#include <iostream>
#include "PacketsManager.h"
int main() {
   PacketsManager manager;
    uintmax_t disk_size;

    std::cout << "Enter allowed disk size in KB: ";
    std::cin >> disk_size;
    manager.set_diskSize(disk_size*1000);

bool st = true;
    while (st){
        try{
        manager.read();
        }
        catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
        st = false;
    }
}
