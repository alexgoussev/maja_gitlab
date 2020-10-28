pyTv-VE-L2INIT-VENUS-MUSCATE_CHAIN
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Titre
*****

Validation fonctionnelle et numérique de la chaîne L2 (Pre-PostProcessing, entrée/sorties) avec un produit VENUS Muscate en mode INIT.


Objectif
********

L’objectif de cet essai est de valider le fonctionnement global de la chaîne L2 en mode INIT sur des produits VENUS Muscate.
Ce test permet également de tester le bon déroulement de la chaîne lorsque l'écriture des données SRE est désactivée.

Description
***********

Les options de traitement sont :

- Instance INIT de VENUS Muscate afin de produire un VENUS Muscate
- Désactivation de l'écriture des images SRE
- Activation de la correction environnementale


Liste des données d’entrées
***************************

Les images utilisées en entrée sont les suivantes :

- VENUS-XS_20120103-105148-000_L1C_CAMARGUE_C_V1-0/VENUS-XS_20120103-105148-000_L1C_CAMARGUE_C_V1-0_MTD_ALL.xml
- VE_TEST_AUX_REFDE2_CAMARGUE_0002.DBL
- VE_TEST_AUX_REFDE2_CAMARGUE_0002.HDR
- VE_TEST_AUX_REFDE2_CAMARGUE_0002.DBL.DIR


Les fichiers GIPPs utilisés en entrée sont les suivants :

-VE_TEST_EXO_METDTA_20110101T000001_20111231T230000.DBL
-VE_TEST_EXO_METDTA_20110101T000001_20111231T230000.HDR
-VE_TEST_GIP_CKEXTL_S_CAMARGUE_00005_00000000_99999999.EEF
-VE_TEST_GIP_CKQLTL_S_CAMARGUE_00002_00000000_99999999.EEF
-VE_TEST_GIP_L2ALBD_L_CONTINEN_00002_00000000_99999999.DBL
-VE_TEST_GIP_L2ALBD_L_CONTINEN_00002_00000000_99999999.DBL.DIR
-VE_TEST_GIP_L2ALBD_L_CONTINEN_00002_00000000_99999999.HDR
-VE_TEST_GIP_L2COMM_L_ALLSITES_00001_20190626_21000101.EEF
-VE_TEST_GIP_L2DIFT_L_CONTINEN_00002_00000000_99999999.DBL
-VE_TEST_GIP_L2DIFT_L_CONTINEN_00002_00000000_99999999.DBL.DIR
-VE_TEST_GIP_L2DIFT_L_CONTINEN_00002_00000000_99999999.HDR
-VE_TEST_GIP_L2DIRT_L_CONTINEN_00002_00000000_99999999.DBL
-VE_TEST_GIP_L2DIRT_L_CONTINEN_00002_00000000_99999999.DBL.DIR
-VE_TEST_GIP_L2DIRT_L_CONTINEN_00002_00000000_99999999.HDR
-VE_TEST_GIP_L2SITE_S_CAMARGUE_00002_00000000_99999999.EEF
-VE_TEST_GIP_L2SMAC_L_ALLSITES_00002_00000000_99999999.EEF
-VE_TEST_GIP_L2TOCR_L_CONTINEN_00002_00000000_99999999.DBL
-VE_TEST_GIP_L2TOCR_L_CONTINEN_00002_00000000_99999999.DBL.DIR
-VE_TEST_GIP_L2TOCR_L_CONTINEN_00002_00000000_99999999.HDR
-VE_TEST_GIP_L2WATV_L_CONTINEN_00002_00000000_99999999.DBL
-VE_TEST_GIP_L2WATV_L_CONTINEN_00002_00000000_99999999.DBL.DIR
-VE_TEST_GIP_L2WATV_L_CONTINEN_00002_00000000_99999999.HDR

Liste des produits de sortie
****************************

Produit VENUS MUSCATE L2A

Prérequis
*********
Il n’y a pas de prérequis.

Durée attendue
***************
La durée d’exécution de l’essai n’est pas un critère attendu.

Epsilon utilisé sur la non regression
*************************************
0.001

Vérifications à effectuer
**************************
Le test génère en sortie une image contenant les angles.

Mise en oeuvre du test
**********************

Ce test est exécuté en lançant la commande :
ctest -R pyTv-VE-L2INIT-VENUS-MUSCATE_CHAIN


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
25/11/2020              OK
================== =================

