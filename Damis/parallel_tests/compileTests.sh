#!/bin/bash
echo "Compiling tests...."
mpic++ `cat cppFiles_Diff.txt` smacof_Diff_Seed.cpp -o _Smacof_Diff_Seed.out -I -L../alglib/ ../alglib/libalglib.so
mpic++ `cat cppFiles_Diff.txt` smacofZ_DSC_Diff_Seed.cpp -o _SmacofZeidel_DSC_Diff_Seed.out -I -L../alglib/ ../alglib/libalglib.so
mpic++ `cat cppFiles_Diff.txt` smacofZ_ASC_Diff_Seed.cpp -o _SmacofZeidel_ASC_Diff_Seed.out -I -L../alglib/ ../alglib/libalglib.so
mpic++ `cat cppFiles_Diff.txt` smacofZ_RND_Diff_Seed.cpp -o _SmacofZeidel_RND_Diff_Seed.out -I -L../alglib/ ../alglib/libalglib.so
mpic++ `cat cppFiles_Diff.txt` samann_Diff_Seed.cpp -o _Samann_Diff_Seed.out -I -L../alglib/ ../alglib/libalglib.so

mpic++ `cat cppFiles_Same.txt` smacof_Same_Seed.cpp -o _Smacof_Same_Seed.out -I -L../alglib/ ../alglib/libalglib.so
mpic++ `cat cppFiles_Same.txt` smacofZ_DSC_Same_Seed.cpp -o _SmacofZeidel_DSC_Same_Seed.out -I -L../alglib/ ../alglib/libalglib.so
mpic++ `cat cppFiles_Same.txt` smacofZ_ASC_Same_Seed.cpp -o _SmacofZeidel_ASC_Same_Seed.out -I -L../alglib/ ../alglib/libalglib.so
mpic++ `cat cppFiles_Same.txt` smacofZ_RND_Same_Seed.cpp -o _SmacofZeidel_RND_Same_Seed.out -I -L../alglib/ ../alglib/libalglib.so
mpic++ `cat cppFiles_Same.txt` samann_Same_Seed.cpp -o _Samann_Same_Seed.out -I -L../alglib/ ../alglib/libalglib.so
echo "Done!!!"
