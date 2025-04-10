#!bin/bash
cmake .
make
./bin/GAME_APPLICATION -c='./config/mesh-test/monkey-3.jsonc'