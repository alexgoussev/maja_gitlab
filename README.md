
# MAJA
<img  title="Ambaro Bay, Madagascar" src="https://labo.obs-mip.fr/wp-content-labo/uploads/sites/19/2017/05/20160406.png" width="300" height="300" align="right"  />
<img  title="logo MAJA" src="https://labo.obs-mip.fr/wp-content-labo/uploads/sites/19/2015/11/logo_maja.png" alt="" width="80"  /> 
<img  title="logo CNES" src="https://labo.obs-mip.fr/wp-content-labo/uploads/sites/19/2015/03/Logo-CNES-horizontal-bleu-300-e1425986175723.png" alt="" width="130"  />
<img  title="logo CESBIO" src="https://labo.obs-mip.fr/wp-content-labo/uploads/sites/19/2012/12/logo_cesbio.png" alt="" width="110"  />
<img  title="logo CSSI" src="https://www.embedded-france.org/wp-content/uploads/2018/06/cs_2008_fr-1.jpg" alt="" width="150"  /> 
<img  title="logo DLR" src="https://labo.obs-mip.fr/wp-content-labo/uploads/sites/19/2015/11/logo_DLR.jpg" alt="" width="90"  />


1. [Installing Maja](#Requirements)
2. [MAJA output format](#format)
3. [Running Maja](#run)
4. [Generation the documentation](#doc)
5. [Running the tests](#tests)
6. [FAQ](#faq)
7. [Contributors](#contrib)
8. [References](#references)



MAJA (for Maccs-Atcor Joint Algorithm), is an atmospheric correction and cloud screening software based on [the MACCS processor](https://labo.obs-mip.fr/multitemp/maccs-how-it-works/), developped for CNES by CS-SI, from a method and a prototype developped at CESBIO, <sup>[1](#ref1)</sup> <sup>[2](#ref2)</sup> <sup>[3](#ref3)</sup>.
In 2017, thanks to an agreement between CNES and DLR and to some funding from ESA, we started adding methods from DLR 's atmospheric correction software ATCOR into MACCS.
MACCS then became MAJA. 

Currently, Maja is allows the following processing steps:
* Atmospheric correction
* Cloud detection
* Estimation of the Aerosol-Optical-Depth (AOT)
* Correction of environmental- and slope-effects

Maja is based on a **multi-temporal** method - allowing to refine the outputs using the previous inputs.
Check the chapters ['Running Maja'](#run) and ['Generating the documentation'](#doc) in order to get more information about the method.

<a name="Requirements"></a>
## Installing Maja

The following instructions will set you up to get a working copy on your system.

### Requirements

In order to compile Maja, you will need the following prerequisites:
* cmake >= 3.4
* MAJA-SuperbuildArchive_V4.x.tar.gz --> Contains all dependencies of Maja
* GCC with support of C++ 14
* Maja-4-x archive --> Contains the code of Maja itself

### Compiling from source

In order to compile Maja from source, run the following commands:
```  
cd Maja-4-x-archive
mkdir build
mkdir install
cd build
cmake ../SuperBuild \
	-DDOWNLOAD_DIR=<Path/to>/Superbuild-archives \
	-DENABLE_TU=OFF \
	-DENABLE_TV=OFF \
	-DENABLE_TVA=OFF \
	-DCMAKE_INSTALL_PREFIX=`pwd`/../install
make
```	

Follow the [next chapter](#run) in order to see how to run Maja.

### Creating a binary package

If you wish to install maja on another system without re-compiling, you can generate a binary-package after compiling using the following command:
```
cd Maja-4-x-archive/build
make binpkg
```
This will create the file `binpkg.dir/MAJA-4-x.run` inside your build/ folder.


### Setting additional environment variables for Maja

All necessary environment variables can be found inside the file `/path/to/maja/install/bin/.majaenv.sh`.

In the case where you used e.g. a different compiler for maja, you can append your own variables to it.


<a name="format"></a>
## Maja output format

Maja currently supports 3 different platforms with 2 format types (called plugins) each:

| Plugin name | Additional info |
| :--------: | --------: |
| Venus   | [Format description](https://labo.obs-mip.fr/multitemp/ven%c2%b5s-l2a-product-format/)  |
| Venus-Muscate   | [Format description](https://labo.obs-mip.fr/multitemp/format-of-ven%c2%b5s-l2a-produced-by-muscate/)  |
| Sentinel2   | [Format description](https://labo.obs-mip.fr/multitemp/sentinel-2/majas-native-sentinel-2-format/)  |
| Sentinel2-Muscate   | [Format description](https://labo.obs-mip.fr/multitemp/sentinel-2/theias-sentinel-2-l2a-product-format/)  |
| Landsat8   | [Format description](https://labo.obs-mip.fr/multitemp/landsat/product-format/)  |
| Landsat8-Muscate   | [Format description](https://labo.obs-mip.fr/multitemp/landsat/theias-landsat-8-l2a-product-format/)  |

<a name="run"></a>
## Running Maja

After compiling, you will be able to run maja in the following path: `<path/to/maja-install>/maja/4.x/bin/maja`.
Run `maja --help` to see a full list of parameters.

We recommend the use of a basic orchestrator, called Start_maja in order to process a time-series of images.
You can find the repo here:

https://github.com/CNES/Start-MAJA

There, you will find a manual on how to set up the software as well as a basic example.

<a name="doc"></a>
## Generation the documentation

The documentation can be compiled by setting the cmake flag `BUILD_DOCS=ON`.
It is deactivated by default.
To run the document compilation, simply execute `make` after activating the option.
The following requirements are needed in order to compile the pdf:

* sphinx-build
* sphinx-rtd-theme
* latex

<a name="tests"></a>
## Running the Tests

Maja needs two auxiliary archives to run the tests, called "MAJA-DATA" and "MAJA-Validation".
To run the compilation with tests, please execute the following commands:
```
cd Maja-4-x-archive
mkdir testing build install
cd build
cmake ../SuperBuild \
	-DMAJADATA_SOURCE_DIR=</path/to>/MAJA-DATA \
	-DMAJA_TEST_OUTPUT_ROOT=`pwd`/../testing \
	-DMAJA_VALIDATION_SRC_DIR=</path/to>/MAJA-Validation \
	-DDOWNLOAD_DIR=</path/to>/Superbuild-archives \
	-DENABLE_TV=ON \
	-DENABLE_TVA=ON \
	-DCMAKE_INSTALL_PREFIX=`pwd`/../install
make –j<NbThreads>
make install
```

Afterwards, run the tests using the following command:
```
ctest -N    # List all available tests
make test   # Runs the tests
```

<a name="faq"></a>
## FAQ

If you have issues or questions with MAJA, please raise an issue on this repository.
It will serve as a forum.

<a name="contrib"></a>
## Contributors

TBD

<a name="references"></a>
## References :
<a name="ref1">1</a>: A multi-temporal method for cloud detection, applied to FORMOSAT-2, VENµS, LANDSAT and SENTINEL-2 images, O Hagolle, M Huc, D. Villa Pascual, G Dedieu, Remote Sensing of Environment 114 (8), 1747-1755

<a name="ref2">2</a>: Correction of aerosol effects on multi-temporal images acquired with constant viewing angles: Application to Formosat-2 images, O Hagolle, G Dedieu, B Mougenot, V Debaecker, B Duchemin, A Meygret, Remote Sensing of Environment 112 (4), 1689-1701

<a name="ref3">3</a>: A Multi-Temporal and Multi-Spectral Method to Estimate Aerosol Optical Thickness over Land, for the Atmospheric Correction of FormoSat-2, LandSat, VENμS and Sentinel-2 Images, O Hagolle, M Huc, D Villa Pascual, G Dedieu, Remote Sensing 7 (3), 2668-2691

<a name="ref4">4</a>: MAJA's ATBD, O Hagolle, M. Huc, C. Desjardins; S. Auer; R. Richter, https://doi.org/10.5281/zenodo.1209633

