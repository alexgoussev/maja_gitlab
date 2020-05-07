############################################################################################################
#                                                                                                          #
#                                        __  __    __     ____   __                                        #
#                                       (  \/  )  /__\   (_  _) /__\                                       #
#                                        )    (  /(__)\ .-_)(  /(__)\                                      #
#                                       (_/\/\_)(__)(__)\____)(__)(__)                                     #
#                                                                                                          #
#                                                                                                          #
############################################################################################################
# HISTORIQUE                                                                                               #
#                                                                                                          #
# VERSION : 3.1.0 : DM : LAIG-DM-MAJA-2526-CNES : 9 avril 2018 : Montée de version de d'OTB 6.0            #
#                                                                                                          #
# FIN-HISTORIQUE                                                                                           #
#                                                                                                          #
# $Id$                                                                                                     #
#                                                                                                          #
############################################################################################################

set(ITK_ENABLED_MODULES
  Common
  FiniteDifference
  GPUCommon
  GPUFiniteDifference
  ImageAdaptors
  ImageFunction
  Mesh
  QuadEdgeMesh
  SpatialObjects
  #TestKernel
  Transform

  AnisotropicSmoothing
  AntiAlias
  BiasCorrection
  BinaryMathematicalMorphology
  Colormap
  Convolution
  CurvatureFlow
  Deconvolution
  Denoising
  #DiffusionTensorImage
  DisplacementField
  DistanceMap
  FastMarching
  FFT
  GPUAnisotropicSmoothing
  GPUImageFilterBase
  GPUSmoothing
  GPUThresholding
  ImageCompare
  ImageCompose
  ImageFeature
  ImageFilterBase
  ImageFusion
  ImageGradient
  ImageGrid
  ImageIntensity
  ImageLabel
  ImageSources
  ImageStatistics
  LabelMap
  MathematicalMorphology
  Path
  QuadEdgeMeshFiltering
  Smoothing
  SpatialFunction
  Thresholding

  Eigen
  #FEM
  NarrowBand
  NeuralNetworks
  Optimizers
  Optimizersv4
  Polynomials
  Statistics

  RegistrationCommon
  #FEMRegistration
  GPURegistrationCommon
  GPUPDEDeformableRegistration
  Metricsv4
  PDEDeformableRegistration
  RegistrationMethodsv4

  #BioCell
  Classifiers
  ConnectedComponents
  DeformableMesh
  KLMRegionGrowing
  LabelVoting
  LevelSets
  LevelSetsv4
  #LevelSetsv4Visualization
  MarkovRandomFieldsClassifiers
  RegionGrowing
  SignedDistanceFunction
  Voronoi
  Watersheds
  IOMeta
  IOJPEG
  IOTIFF  
  )

set(ITK_MODULES_CMAKE_CACHE)
foreach(ITK_MODULE ${ITK_ENABLED_MODULES})
  list(APPEND ITK_MODULES_CMAKE_CACHE -DModule_ITK${ITK_MODULE}:BOOL=ON)
endforeach()
#set(ITK_URL  "http://download.sourceforge.net/project/itk/itk/4.7/InsightToolkit-4.7.2.tar.gz")
#set(ITK_URL_MD5 75ec63834ae59bc120a138d58ba3fa99)
set(ITK_URL  "https://sourceforge.net/projects/itk/files/itk/4.12/InsightToolkit-4.12.0.tar.gz")
set(ITK_URL_MD5 561a403f93c88c64085b5623e8e61f79)
set(ITK_DEPENDS ZLIB TIFF JPEG PNG EXPAT)
build_projects(ITK_DEPENDS)

ExternalProject_Add(ITK
  URL          "${ITK_URL}"
  URL_MD5      ${ITK_URL_MD5}
  PREFIX       ITK
  TMP_DIR      ITK/tmp
  STAMP_DIR    ITK/stamp
  SOURCE_DIR   ITK/source
  BINARY_DIR   ITK/build
  INSTALL_DIR ${SB_INSTALL_PREFIX}
  DOWNLOAD_DIR ${DOWNLOAD_DIR}
  CMAKE_CACHE_ARGS
  ${SB_CMAKE_CACHE_ARGS}
  -DITK_BUILD_DEFAULT_MODULES:BOOL=OFF
  -DUSE_FFTWF:BOOL=OFF
  -DUSE_FFTWD:BOOL=OFF
  -DBUILD_TESTING:BOOL=OFF
  -DBUILD_EXAMPLES:BOOL=OFF
  -DITK_USE_SYSTEM_EXPAT:BOOL=ON
  -DITK_USE_SYSTEM_ZLIB:BOOL=ON
  -DITK_USE_SYSTEM_TIFF:BOOL=ON
  -DITK_USE_SYSTEM_JPEG:BOOL=ON  
  -DITK_FORBID_DOWNLOADS:BOOL=ON
  -DITKGroup_Core:BOOL=OFF
  -DExternalData_URL_TEMPLATES:STRING=
  ${ITK_MODULES_CMAKE_CACHE}
  DEPENDS ${ITK_DEPENDS}
  CMAKE_COMMAND ${SB_CMAKE_COMMAND}
  LOG_DOWNLOAD ${WRITE_LOG}
  LOG_CONFIGURE ${WRITE_LOG}
  LOG_BUILD ${WRITE_LOG}
  LOG_INSTALL ${WRITE_LOG}
  )

SUPERBUILD_PATCH_SOURCE(ITK)

