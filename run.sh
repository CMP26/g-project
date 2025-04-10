#!bin/bash
cmake .
make
./bin/GAME_APPLICATION -c='./config/transform-test/test-0.jsonc'