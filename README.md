# DAMIS algorithms

MPI implementations of the DAMIS data mining algorithms (C++17, [ALGLIB](https://www.alglib.net/)).
The program `Algorithms` reads an ARFF file, runs one algorithm and writes the result and a
statistics file. It is started by [DAMIS_WebService](https://github.com/InScience/DAMIS_WebService)
(`DamisService.cgi`), which in turn is called by the [DAMIS-GUI](https://github.com/InScience/DAMIS-GUI).

## Build

Ubuntu 26.04 / Debian 13:

```sh
sudo apt-get install build-essential openmpi-bin libopenmpi-dev
make -j"$(nproc)"          # produces ./Algorithms
make install PREFIX=/opt/damis
```

## Run

```sh
mpirun -np 4 ./Algorithms -al <ALGORITHM> <parameters> -i input.arff -o result.arff -s stat.arff
```

Every process computes a projection from its own random start; the master keeps the one with
the smallest error. The stat file contains `algError` and `calcTime`. Exit code is non-zero if
the call is invalid. A temporary distance matrix (`*.bin`) is written next to the input file,
so its directory must be writable.

| `-al` | Parameters |
|---|---|
| `PCA` | `-projType 0 -d <dimension>` or `-projType 1 -d <% of variance to keep>` |
| `SMACOFMDS` | `-maxIter -d -eps -zeidel 0\|1` |
| `RELATIVEMDS` | `-maxIter -d -eps -noOfBaseVectors -selStrategy 1(random)\|2(PCA)\|3(dispersion)` |
| `DMA` | `-maxIter -d -eps -neighbour` |
| `SAMANN` | `-maxIter -d -eta -mTrain -nNeurons` |
| `SOMMDS` | `-rows -columns -eHat -mdsIteration -eps -mdsProjection` |
| `SOM` | `-rows -columns -eHat` |
| `KMEANS` | `-maxIter -noOfClust` |
| `MLP` | `-h1pNo -h2pNo -qty -maxIter -kFoldVal 0\|1` (needs a class attribute) |
| `DECTREE` | `-dL -dT -r -nTree` (needs a class attribute) |

## Test

```sh
scripts/smoke-test.sh            # all algorithms on arff_files/iris.arff, NP=2
NP=4 scripts/smoke-test.sh
```

GitHub Actions (`.github/workflows/ci.yml`) build and run the smoke test on Ubuntu 26.04 on every push and
pull request.

## Changes in 2026

- Standalone `Makefile` (the NetBeans project files were never committed).
- Fixed: undefined behaviour in `strToInt`/`strToDouble` for missing parameters, PCA with
  `-projType 1` crashing (shadowed `d`), SOMMDS ignoring the `-mdsIteration` passed by the web
  service, RELATIVEMDS random and dispersion base vector selection
  (int overflow / missing square), the temporary distance matrix file name now being generated
  once and broadcast to all processes (concurrent runs no longer collide) and removed after the run.
- Removed C++17-incompatible `std::ptr_fun` / `std::not1`.
