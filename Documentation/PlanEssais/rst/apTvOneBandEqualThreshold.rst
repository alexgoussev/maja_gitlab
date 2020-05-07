apTvSmoothingBis
~~~~~~~~~~~~~~~~

Objectif
********
Validation de l'application "OneBandEqualThreshold"

Description
***********

Le module "OneBandEqualThreshold" génére un masque dont la valeur vaut 'inside_value' si au moins une des bande vaut 'threshold', 'outside_value' sinon


Liste des données d’entrées
***************************

Image à plusieurs bande

Liste des produits de sortie
****************************

Masque

Prérequis
*********
Il n’y a pas de prérequis.

Durée attendue
***************
La durée d’exécution de l’essai n’est pas un critère attendu.

Epsilon utilisé sur la non regression
*************************************
0

Vérifications à effectuer
**************************
Le test génère en sortie une image arrondies à plusieurs bandes. 

Mise en oeuvre du test
**********************

Ce test est exécuté en lançant la commande :
ctest -R apTvOneBandEqualThreshold

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

Exigences
*********
Ce test couvre les exigences suivantes :
Néant
