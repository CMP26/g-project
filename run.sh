#!/bin/bash
cmake .
 
make

./bin/GAME_APPLICATION -c='./config/entity-test/test-1.jsonc'

