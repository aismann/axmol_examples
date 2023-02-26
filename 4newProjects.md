cd D:\______\aismann\axmol

set project=Clipper2
set locDir=D:\______\aismann\__public\axmol\axmol_examples
set locDir=D:\______\aismann\__private\axmol\

axmol new -p org.frankensoft.%project% -d %locDir% -l cpp --portrait %project%
cd  %locDir%\%project%
cmake -B build_64 -A x64 "-DAX_PREBUILT_DIR=build_64"
cmake --build build_64 --config Debug --target %project%
run debug
cd D:\______\aismann\__public\axmol\