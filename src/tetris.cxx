#include "controller.hxx"

#include <stdexcept>
#include <string>


int
main(int argc, char *argv[]) {

    try {
        int width;
        int height;
        switch (argc) {
            case 1:
                width = 18;
                height = 22;
                break;
            case 3:
                width = std::stoi(argv[1]);
                height = std::stoi(argv[2]);
                break;
            default:
                std::cerr << "Usage: " << argv[0] << " [WIDTH HEIGHT]\n";
                return 1;
        }
        Controller(width, height).run();

    } catch (std::exception const& e) {
        std::cerr << argv[0] << ": " << e.what() << "\n";
        return 1;
    }

    return 0;
}
