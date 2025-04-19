#!/bin/bash
cmake --build build

./bin/GAME_APPLICATION -c='./config/material-test/test-0.jsonc'
./bin/GAME_APPLICATION -c='./config/material-test/test-1.jsonc'

