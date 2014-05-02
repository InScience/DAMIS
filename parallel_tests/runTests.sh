#!/bin/bash

fileName='testResults.txt'
n=4

echo "--- Testing methods using different generated initial projection matrix Y ----"
echo "--- Testing methods using different generated initial projection matrix Y ----" > $fileName
echo "Testing on $n CPUs"
echo "Testing on $n CPUs" >> $fileName

mpirun -np $n ./_Smacof_Diff_Seed.out >> $fileName
mpirun -np $n ./_SmacofZeidel_DSC_Diff_Seed.out >> $fileName
mpirun -np $n ./_SmacofZeidel_ASC_Diff_Seed.out >> $fileName
mpirun -np $n ./_SmacofZeidel_RND_Diff_Seed.out >> $fileName
mpirun -np $n ./_Samann_Diff_Seed.out >> $fileName

echo "--- Testing methods using the same initial randomly generated projection matrix Y ----"
echo "--- Testing methods using the same initial randomly generated projection matrix Y ----" >> $fileName
echo "Testing on $n CPUs"
echo "Testing on $n CPUs" >> $fileName

mpirun -np $n ./_Smacof_Same_Seed.out >> $fileName
mpirun -np $n ./_SmacofZeidel_DSC_Same_Seed.out >> $fileName
mpirun -np $n ./_SmacofZeidel_ASC_Same_Seed.out >> $fileName
mpirun -np $n ./_SmacofZeidel_RND_Same_Seed.out >> $fileName
mpirun -np $n ./_Samann_Same_Seed.out >> $fileName
