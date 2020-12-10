pyTv-STARTMAJA_CHAIN
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Titre
*****

Validation fonctionnelle et numérique de StartMaja avec des produits SENTINEL2 en modes INIT et NOMINAL.


Objectif
********

L’objectif de cet essai est de valider le fonctionnement global de StartMaja en mode INIT ET NOMINAL sur des produits SENTINEL2.
Plus particulièrement, ce test permet de vérifier que la chaîn est bien capable de télécharger les GIPPS et autres données nécessaires,
et de bien faire le lien avec l'orchestrateur MAJA.


Description
***********

Les options de traitement sont :

- Méthode SPECTROTEMPORAL pour l’estimation des aérosols,
- Correction de l’environnement et des pentes,
- Ecriture à la résolution L2,
- activation de la correction des cirrus


Liste des données d’entrées
***************************

Les images utilisées en entrée sont les suivantes :

- S2A_MSIL1C_20170605T105031_N0205_R051_T31UDQ_20170605T105303.SAFE
- S2A_MSIL1C_20170615T105031_N0205_R051_T31UDQ_20170615T105505.SAFE
- S2__TEST_AUX_REFDE2_31UDQ_0001.DBL.DIR
- S2__TEST_AUX_REFDE2_31UDQ_0001.HDR

Les fichiers GIPPs utilisés en entrée sont les suivants :

- S2__TEST_EXO_CAMS_20170625T000000_20190418T025513.DBL.DIR
- S2__TEST_EXO_CAMS_20170625T000000_20190418T025513.HDR
- S2__TEST_EXO_CAMS_20170625T120000_20190418T053109.DBL.DIR
- S2__TEST_EXO_CAMS_20170625T120000_20190418T053109.HDR


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
ctest -R pyTv-STARTMAJA_MAJA


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
26/11/2010              OK
================== =================

