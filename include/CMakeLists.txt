add_library(Purplehole)

target_sources(Purplehole PRIVATE 
../src/classes/animation.cpp 
../src/classes/collisions.cpp 
../src/classes/entities.cpp 
../src/classes/interface.cpp 
../src/classes/tilemap.cpp 

../src/core/assets.cpp 
../src/core/engine.cpp 
../src/core/imageHandle.cpp 
../src/core/keybinds.cpp 
../src/core/utils.cpp 

../src/main/editor.cpp 
../src/main/game.cpp 
../src/main/menu.cpp



./classes/animation.hpp 
./classes/collisions.hpp 
./classes/entities.hpp 
./classes/interface.hpp 
./classes/tilemap.hpp 

./core/assets.hpp 
./core/engine.hpp 
./core/imageHandle.hpp 
./core/keybinds.hpp 
./core/utils.hpp

./main/editor.hpp 
./main/game.hpp
./main/menu.hpp
)

target_include_directories(Purplehole PUBLIC .)
target_link_libraries(Purplehole PUBLIC vendor)