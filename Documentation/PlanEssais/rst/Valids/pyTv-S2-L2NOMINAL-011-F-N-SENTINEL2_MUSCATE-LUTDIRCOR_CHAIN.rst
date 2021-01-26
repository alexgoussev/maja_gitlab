pyTv-S2-L2NOMINAL-011-F-N-SENTINEL2_MUSCATE-LUTDIRCOR_CHAIN
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Titre
*****

Validation fonctionnelle et numérique de la chaîne L2 (Pre-PostProcessing, entrée/sorties) avec un produit SENTINEL2 Muscate en mode NOMINAL.


Objectif
********

L’objectif de cet essai est de valider le fonctionnement global de la chaîne L2 en mode NOMINAL sur des produits SENTINEL2 Muscate comportant différentes résolutions.
Dans certains cas la méthode de ROY pour la correction directionnelle ne donne pas de bon résultats. Une méthode utilisant des LUT a alors été ajoutée pour traiter ces cas.
Ce test permet donc plus particulièrement de vérifier que la chaîne est capable de bien intégrer cette méthode de correction directionnelle basée sur des LUTs.


Description
***********

Les options de traitement sont :

- Méthode SPECTROTEMPORAL pour l’estimation des aérosols,
- Correction de l’environnement et des pentes,
- Ecriture à la résolution L2,
- activation de la correction des cirrus
- méthode utilisant des LUTs pour calculer les coefficients de correction directionnelle.



Liste des données d’entrées
***************************

Les images utilisées en entrée sont les suivantes :

- SENTINEL2B_20171010-105012-463_L1C_T31TCH_C_V1-0/SENTINEL2B_20171010105012-463_L1C_T31TCH_C_V1-0_MTD_ALL.xml
- SENTINEL2B_20171008-105012-463_L2A_T31TCH_C_V1-0/SENTINEL2B_20171008105012-463_L2A_T31TCH_C_V1-0_MTD_ALL.xml
- S2__TEST_AUX_REFDE2_T31TCH_0001.DBL


Les fichiers GIPPs utilisés en entrée sont les suivants :

- S2A_TEST_GIP_CKEXTL_S_31TJF____10001_20150703_21000101.EEF
- S2A_TEST_GIP_L2TOCR_L_CONTINEN_10002_20150703_21000101.DBL
- S2B_TEST_GIP_L2DIFT_L_CONTINEN_10002_20150703_21000101.DBL
- S2B_TEST_GIP_L2WATV_L_CONTINEN_10002_20150703_21000101.DBL
- S2A_TEST_GIP_CKQLTL_S_31TJF____10005_20150703_21000101.EEF
- S2A_TEST_GIP_L2TOCR_L_CONTINEN_10002_20150703_21000101.HDR
- S2B_TEST_GIP_L2DIFT_L_CONTINEN_10002_20150703_21000101.DBL.DIR
- S2B_TEST_GIP_L2WATV_L_CONTINEN_10002_20150703_21000101.DBL.DIR
- S2A_TEST_GIP_L2ALBD_L_CONTINEN_10003_20150703_21000101.DBL
- S2A_TEST_GIP_L2WATV_L_CONTINEN_10002_20150703_21000101.DBL
- S2B_TEST_GIP_L2DIFT_L_CONTINEN_10002_20150703_21000101.HDR
- S2B_TEST_GIP_L2WATV_L_CONTINEN_10002_20150703_21000101.HDR
- S2A_TEST_GIP_L2ALBD_L_CONTINEN_10003_20150703_21000101.HDR
- S2A_TEST_GIP_L2WATV_L_CONTINEN_10002_20150703_21000101.HDR
- S2B_TEST_GIP_L2DIRT_L_CONTINEN_10002_20150703_21000101.DBL
- S2A_TEST_GIP_L2COMM_L_ALLSITES_10008_20150703_21000101.EEF
- S2B_TEST_GIP_CKEXTL_S_31TJF____10001_20150703_21000101.EEF
- S2B_TEST_GIP_L2DIRT_L_CONTINEN_10002_20150703_21000101.DBL.DIR
- S2A_TEST_GIP_L2DIFT_L_CONTINEN_10002_20150703_21000101.DBL
- S2B_TEST_GIP_CKQLTL_S_31TJF____10005_20150703_21000101.EEF
- S2B_TEST_GIP_L2DIRT_L_CONTINEN_10002_20150703_21000101.HDR
- S2A_TEST_GIP_L2DIFT_L_CONTINEN_10002_20150703_21000101.HDR
- S2B_TEST_GIP_L2ALBD_L_CONTINEN_10003_20150703_21000101.DBL
- S2B_TEST_GIP_L2SMAC_L_ALLSITES_10001_20150703_21000101.EEF
- S2__TEST_GIP_L2SITE_S_31TJF____10001_00000000_99999999.EEF
- S2A_TEST_GIP_L2DIRT_L_CONTINEN_10002_20150703_21000101.DBL
- S2B_TEST_GIP_L2ALBD_L_CONTINEN_10003_20150703_21000101.DBL.DIR
- S2B_TEST_GIP_L2TOCR_L_CONTINEN_10002_20150703_21000101.DBL
- S2A_TEST_GIP_L2DIRT_L_CONTINEN_10002_20150703_21000101.HDR
- S2B_TEST_GIP_L2ALBD_L_CONTINEN_10003_20150703_21000101.HDR
- S2B_TEST_GIP_L2TOCR_L_CONTINEN_10002_20150703_21000101.DBL.DIR
- S2A_TEST_GIP_L2SMAC_L_ALLSITES_10001_20150703_21000101.EEF
- S2B_TEST_GIP_L2COMM_L_ALLSITES_10008_20150703_21000101.EEF
- S2B_TEST_GIP_L2TOCR_L_CONTINEN_10002_20150703_21000101.HDR
- S2__TEST_GIP_DIRCOR_L_ALLSITES_50003_20201010_21000101.DBL.DIR
- S2__TEST_GIP_DIRCOR_L_ALLSITES_50003_20201010_21000101.HDR


Liste des produits de sortie
****************************

Produit SENTINEL2 L2A MUSCATE

Prérequis
*********
Il n’y a pas de prérequis.

Durée attendue
***************
La durée d’exécution de l’essai n’est pas un critère attendu.

Epsilon utilisé sur la non regression
*************************************
0.0001

Vérifications à effectuer
**************************
Le test génère en sortie une image contenant les angles.

Mise en oeuvre du test
**********************

Ce test est exécuté en lançant la commande :
ctest -R pyTv-S2-L2NOMINAL-011-F-N-SENTINEL2_MUSCATE-LUTDIRCOR_CHAIN


Exigences
*********
Ce test couvre les exigences suivantes :
MACCS-Exigence 640 (C) ; MACCS-Exigence 650 (C) ;



Journal d’essai de la recette
*****************************

Notes sur le déroulement du test
--------------------------------
Rien de particulier n’a été noté lors du déroulement du test.

Conclusion du déroulement du test
---------------------------------
RAS

Validation du test
------------------

================== =================
Date de validation    Résultat
03/11/2020              OK
================== =================

