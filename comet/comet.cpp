#include <comet.hpp>

#include <project\sys\system.hpp>
#include <project\managament.hpp>


namespace comet {

void init() {
    comet::system::init();
    Projects::init();
}


void finalize() {
    Projects::finalize();
    comet::system::finalize();
}


}