LES ESSAIS DE VALIDATION
=====================================

Objectifs
----------

Les essais menés durant la phase d’intégration et de validation sont des essais dits fonctionnels
et/ou numériques. Ils permettent de tester toutes les fonctionnalités du logiciel avec variation des
paramètres d’entrée et des contextes d’utilisation. Ils couvrent les cas d’activation nominaux, les cas
dégradés, les tests de performances. Ils permettent de répondre à la question « est-ce que le logiciel
répond bien au besoin ? ».

L’objectif général de la validation est de garantir que le ou les composants implémentés fournissent
des résultats exacts. Des tests de non-régression sont également mis en place afin de garantir l’exac-
titude des résultats au fur et à mesure des développements. Cette phase de validation permet notam-
ment de :
– Vérifier l’adéquation des fonctionnalités offertes par le système aux exigences,
– Garantir, en complément des différents essais réalisés au niveau des composants, une vérification
des exigences compréhensible par l’utilisateur,
– Valider les interfaces avec les entités externes,
CS - Communication & Systèmes — SETG-PE-MAJA-010-CS — Éd. 03Rév. 02— Plan d’Intégration et de Validation
7.2. Phase de validation
199
– Pérenniser un ensemble de scripts/jeux de données/résultats pour chaque essai afin de pouvoir les
rejouer ultérieurement en cas d’évolution du système,
– Apprêter le système pour son entrée en recette.



F IG . 4.1 – Arborescence des modules algorithmiques.

Description du processus de validation
------------------------------------------

Le processus de validation est itératif. Il est initialisé pendant la phase de conception, précisé tout
au long de la progression du développement, et complété pour la livraison sur site. Le processus est
composé des étapes suivantes :
– Définition des tests : cette activité consiste à prévoir les tests qui devront démontrer que le système
est conforme aux exigences utilisateur. Cette définition est réalisée en deux étapes :
– La première consiste à produire un plan de validation. Elle s’attachera notamment à définir et
identifier les essais unitaires et données constituant le plan de validation. Cette étape est réalisée
durant les phases de conception et éventuellement complété au cours des développements,
– La deuxième consiste à produire les plans d’essais détaillés (PED) de chacun des essais. Ces
PED contiennent toutes les informations décrites section 3.6.1.1,
– Vérification de la couverture des essais : cette activité est réalisée avec l’outil Reqtify, et une
matrice de couverture « exigence/cas de tests » est produite.
– Les étapes d’exécution sont les suivantes :
– Génération de la version logicielle à valider par l’équipe projet à partir des sources gérés par
l’équipe de gestion en configuration CS (la procédure de génération fait l’objet elle-même d’un
test),
– Installation du logiciel (l’installation fait l’objet elle-même d’un test),
– Pour chaque essai de validation :
– Installation des contextes d’essais, tels que définis dans le PED de l’essai,
– Génération automatique du journal d’essai en début d’essai en fonction de sa description
dans le PED,
– Mise en œuvre de l’essai et rédaction de la partie résultats obtenus dans le journal d’essai,
– Récupération des contextes de fin d’essai et exécution éventuelle de la procédure de vérifica-
tion des résultats (comparaison du contexte récupéré par rapport à un contexte de référence).
– Mise à jour du rapport de la campagne d’essais.
La phase de validation conduit à la mise en œuvre de l’ensemble des cas de tests identifiés. Ces
cas de tests sont complétés et finalisés lors de cette phase. Les données et outils de validation sont
mis en œuvre et adaptés le cas échéant. Les tests et données de validation sont maintenus pendant
l’ensemble du cycle de vie du logiciel. Ce processus est tout d’abord mis en œuvre sur la machine
de développement à CS sur laquelle est également réalisée la recette usine des chaînes MAJA L2,
L3 ainsi que des outils associés. Suite à une phase d’intégration sur la configuration cible CNES, les
tests associés à des produits simulés (choix du capteur) pourront être exécutés.
La recette site sera réalisée sur la configuration cible CNES.




Formalisation des tests de validation algorithmique
---------------------------------------------------

La nomenclature adoptée pour l’identification des essais d’intégration et de validation est la
suivante :
<Idcapteur>-<catégorie>-<traitement>-<n ̊d’essai>-<nature>-<type>-<produit>-
<thématique>
Ex : VE-P-L2INIT-001-F-N-VENUS-CLOUD
Avec :
VE : Id Capteur
peut prendre les valeurs :
– VE : produit image Venus,
– F2 : produit image Formosat-2,
– L5 ou L7 : produit image Landsat L5 ou L7,
– S2A ou S2B : produit image Sentinel2 A ou B
Catégorie identifie la catégorie du test et peut prendre les valeurs :
– P : Test de performance



LISTE DES ESSAIS
-------------------------------------------

Ce chapitre présente la liste des tests mis en place pour réaliser la validation numérique des modules
algorithmiques.

.. tabularcolumns:: |p{1cm}|L|L|

======= ======================================================= =============================================================================
1       apTvSmoothingBis                                        Application d'une gaussienne sur l'image
2       apTvResampling                                          Réechantillonnage d'une image sur un DTM
3       apTvStats                                               Calculs de statistiques sur une image
4       apTvMultiplyByScalar                                    Multiplication d'une image par un scalaire
5       apTvBinaryConcatenate                                   Concatenation de plusieurs bandes binaires(0-1)
6       apTvBinaryToVector                                      Déconcaténation en plan de bits
7       apTvConcatenatePerZone                                  Concaténation d'image selon un masque de zones
8       apTvDispatchZonesToVectorNoWeight                       Répartition de masques de zone 
9       apTvDispatchZonesToVectorWeight                         Répartition de masques de zone (bandes non ordonées)
10      apTvIncidenceAngle                                      Calcul des angles d'incidences
11      apTvOzoneExtractor                                      Extraction du volume d'ozone
12      apTvAngleListToImage					Création d'une image à partir d'une liste d'angles
13      apTvSolarAngle                                          Calcul des angles solaires
14      apTvImageListWriter                                     Ecriture simultanée d'une liste d'images
15      apTvRoundImage                                          Arrondis d'une image
16      apTvRoundVectorImage                                    Arrondis d'une image à plusieurs bandes
17      apTvRescaleIntensity                                    Modification de la radiometrie
18      apTvOneBandEqualThreshold                               Création d'un masque par test de valeur
19      apTvDarkestPixelAOTNominal                              Calcul du DarkestPixel pour le calcul de l'AOT
20      apTvGapFilling                                          Algorithm de gap filling
21      apTvAOTEstimation_SpectroTemporalNominal                Calcul de l'AOT en SpectroTemporel
22      apTvAOTMean_SpectroTemporalNominal                      Calcul de l'AOT moyen en SpectroTemporel
23      apTvAOTEstimation_MultiTemporalNominal                  Calcul de l'AOT en MultiTemporel
24      apTvAOTEstimationMultiSpectral                          Calcul de l'AOT en MultiSpectral
25      apTvAOTEstimationSpectroTemporalCAMS                    Calcul de l'AOT en SpectroTemporel avec CAMS
26      apTvPressureFilter                                      Calcul de la pression
27      apTvTOACorrection                                       Correction TOA de l'image
28      apTvWaterAmountGeneratorFilter                          Calcul d'un volume d'eau
29      apTvGammaCompute                                        Calcul d'un gamma pour la correction cirrus
30      apTvCirrusCorrectionApply                               Correction Cirrus d'une image
31      apTvCirrusFlag                                          Calcul du flag Cirrus
32      apTvCirrusMask                                          Calcul du masque de Cirrus
33      apTvComposite                                           Calcul des images composites
34      apTvDTMProcessing                                       Algorithme DTMProcessing 
35      apTvComputeRhoEnv                                       Calcul du RhoEnv
36      apTvEnvCorrection                                       Correction des effets environnementaux
37      apTvInterpolateForEnvCorr                               Interpolation spécifique pour les effets environnementaux
38      apTvCloudReflectance                                    Calcul du masque de nuages reflectance
39      apTvCloudReflectanceVariation                           Calcul du masque de variation des nuages reflectance
40      apTvCloudExtension                                      Calcul du masque de nuages "extension"
41      apTvCloudShadVar                                        Calcul du masque de variation des ombres des nuages
42      apTvCloudSnowCorrection                                 Correction des effets de neiges
43      apTvCloudMaskUndersampling                              Reechantillonnage spécifique aux images CLA
44      apTvCloudShadowWithAltitudeFilterInit                   Calcul du masque des ombres des nuages connaissant leurs altitudes
45      apTvCloudShadowWithoutAltitudeFilterNominal             Calcul du masque des ombres des nuages sans leurs altitudes
46      apTvRayleighCorrection                                  Correction Rayleigh
47      apTvCamsCompute                                         Extraction des données CAMS (ancien format)
48      apTvNewCamsCompute                                      Extraction des données CAMS (nouveau format)
49      apTvNewCamsMixedCompute                                 Extraction des données CAMS (ancien et nouveau format)
50      apTvDirectionalCorrection                               Calcul des coefficients de correction directionelle
51      apTvReduceLut                                           Extraction de MiniLut
52      apTvReduceLutDirCorr                                    Extraction de minilut avec correction directionnelle
53      apTvExtractLutChannel                                   Extraction d'une bande d'une LUT
54      apTvScatteringCorrection                                Correction du scattering
55      apTvSlopeCorrection                                     Correction des effets de pentes
56      apTvComputeTransmission                                 Calcul de la transmission athmosphérique
57      apTvSnowMask                                            Calcul du masque de neige
58      apTvSnowMaskVenus                                       Calcul du masque de neige (cas VENUS)
59      apTvWaterMask                                           Calcul du masque d'eau
60      apTvWaterVaporPostPro                                   Post processing du masque d'eau
61      apTvBandMath                                            Outil générique d'algorithmie sur image (OTB)
62      apTvExtractROI                                          Extraction de zone/bande (OTB)
63      apTvManageNoData                                        Application/Extraction de masques de NoData
64      apTvBinaryMorphologicalOperation                        Opérateurs Morphologiques
65      apTvConvertCartoToGeoPoint                              Conversion de coordonnées cartographiques
66      apTvConcatenateImages                                   Concaténation d'image en une seule


DESCRIPTION DÉTAILLÉE DES ESSAIS
------------------------------------------------------------

