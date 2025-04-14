erase *.sdf
erase /AH *.suo
erase /AH *.opensdf

cd Release
erase *.pdb/s/Q
erase *.exe/s/Q
erase common_ClassLib.dll/s/Q
erase *.metagen/s/Q


cd..
cd Debug
erase *.pdb/s/Q
erase *.exe/s/Q
erase *.ilk/s/Q
erase common_ClassLib.dll/s/Q
erase *.metagen/s/Q

cd..

cd common_ClassLib
rd Release/s/Q
rd Debug/s/Q


pause



