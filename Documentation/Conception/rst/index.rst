
.. figure:: Art/image1.png

**CS Systèmes d'Information**

| Business Unit ESPACE                                                                                          
| Département Payload Data & Applications    
| Image Processing		   


.. tabularcolumns:: |L|J|J|J|p{0.6in}|
		    
=============================================== == ================= ============
Software: **MAJA**
**SETG-**\ **CG-**\ **MAJA-**\ **010-**\ **CS**                       
Change                                          02 Date              29/11/2019
Issue                                           01 Date              10/03/2020
Distribution Code                               E
Ref. : CSSI/SPACE/PD&A/MAJA/DCG 
=============================================== == ================= ============

**DOCUMENT DE CONCEPTION GLOBALE POUR LES CHAINES MAJA [DCG]**

=================================== ===============
Rédigé par :                        le : 10/03/2020
                                                   
ESQUIS Benjamin  CSSI/ESPACE/PDA/IP                
BRICIER Aurélien CSSI/ESPACE/PDA/IP                
Validé par :                        le : 18/04/2018
                                                   
OLIVIE Francis CSSI/ESPACE/DSM                     
Pour application :                  le : 10/03/2020
                                                   
ESQUIS Benjamin CSSI/ESPACE/PDA/IP                
=================================== ===============

**Bordereau d'indexation**

+----------------------------------------------------------------------------------------+-----------------------------------------------------+------------------------+---------------+
| Confidentialité :                                                                      | Mots clés : Conception, MAJA, Sentinel2, VENµS, chaînes L2                                   |
| DLP                                                                                    |                                                                                              |
+----------------------------------------------------------------------------------------+-----------------------------------------------------+------------------------+---------------+
| TITRE Du Document :                                                                                                                                                                   |
| Document de conception globale                                                                                                                                                        |
| MAJA                                                                                                                                                                                  |
| [DCG]                                                                                                                                                                                 |
+----------------------------------------------------------------------------------------+-----------------------------------------------------+------------------------+---------------+
|   AUTEUR(s):                                                                           | | BRICIER Aurélien CSSI/ESPACE/PDA/IP                                                        |
|                                                                                        | | ESQUIS Benjamin  CSSI/ESPACE/PDA/IP                                                        |
+----------------------------------------------------------------------------------------+-----------------------------------------------------+------------------------+---------------+
| RESUME : Ce document présente la conception définie pour le développement de l'outil MAJA.                                                                                            |
+----------------------------------------------------------------------------------------+-----------------------------------------------------+------------------------+---------------+
| Documents Rattaches : Le document [SDM] complète ce document...                        | LOCALISATION :                                                                               |
|                                                                                        | CSSI/SPACE/PD&A/MAJA                                                                         |
+----------------------------------------------------------------------------------------+-----------------------------------------------------+------------------------+---------------+
| Volume : 1                                                                             | Nombre total de pages : N/A                         | Doc composite : N      | LANGUAGE : FR |
|                                                                                        |                                                     |                        |               |
|                                                                                        | Dont pages préliminaires : 0                        |                        |               |
|                                                                                        |                                                     |                        |               |
|                                                                                        | Nombre de pages suppl : 0                           |                        |               |
+----------------------------------------------------------------------------------------+-----------------------------------------------------+------------------------+---------------+
| GESTION DE CONF. : NG                                                                  | CM RESP. :                                                                                   |
+----------------------------------------------------------------------------------------+-----------------------------------------------------+------------------------+---------------+
| CAUSE D'EVOLUTION : Mise à jour pour MAJA v4.1.0                                                                                                                                      |
+----------------------------------------------------------------------------------------+-----------------------------------------------------+------------------------+---------------+
| CONTRAT : Marché ACIS n°131348                                                                                                                                                        |
+----------------------------------------------------------------------------------------+-----------------------------------------------------+------------------------+---------------+

**Diffusion interne**

================== ====================
ESQUIS Benjamin    CSSI/ESPACE/PDA/IP   
BROSSARD Julie     CSSI/ESPACE/PDA/IP   
OLIVIE Francis     CSSI/ESPACE/DSM      
RECULEAU SERGE     CSSI/ESPACE/PDA/PDGS 
\                                       
\                                       
\                                       
\                                       
\                                       
\                                       
\                                       
\                                       
\                                       
================== ====================

**Diffusion externe**

================== ===================== ============
Nom                Sigle                 Observations
BAILLARIN Simon    DNO/OT/IS            
DESJARDINS Camille DSO/SI/MO            
HAGOLLE Olivier    DSO/SI/CB            
LARIF Marie-France DNO/SC/3S            
LASSALLE Pierre    DNO/OT/IS            
SAMSON Laetitia    EQUERT POUR DCT/AQ/SO
\                                       
\                                       
\                                       
\                                       
\                                       
\                                       
\                                       
================== ===================== ============

**Modification**

.. tabularcolumns:: |p{1cm}|L|p{2cm}|L|

=== ==== ========== ================================================================================
Ed. Rév. Date       Référence, Auteur(s), Causes d’évolution
02  01   10/03/2020 CSSI/ESPACE/PDA/IP/MAJA/DCG
                   
                    ESQUIS Benjamin CSSI/ESPACE/PDA/IP
                   
                    Refonte pour MAJA 4.1

02  00   29/11/2019 CSSI/ESPACE/PDA/IP/MAJA/DCG
                   
                    ESQUIS Benjamin CSSI/ESPACE/PDA/IP
                   
                    Refonte pour MAJA 4.0

01  03   18/04/2018 CSSI/ESPACE/PDA/IP/MAJA/DCG
                   
                    BRICIER Aurélien CSSI/ESPACE/PDA/IP
                   
                    Ajout des modifications pour MAJA 3.1
01  02   20/10/2017 CSSI/ESPACE/PDA/IP/MAJA/DCG
                   
                    BRICIER Aurélien CSSI/ESPACE/PDA/IP
                   
                    Ajout des modifications pour MAJA 3.0
01  01   04/05/2017 CSSI/ESPACE/PDA/IP/MAJA/DCG
                   
                    ESQUIS Benjamin CSSI/ESPACE/PDA/IP
                   
                    Mise à jour du document suite à la livraison de MAJA 2.0
                   
                    Ajout description I3D
01  00   21/12/2016 CSSI/ESPACE/PDA/IP/MAJA/DCG
                   
                    FEUVRIER Thomas CSSI/ESPACE/PDA/IP
                   
                    Création du document à partir du document MACCS LAIG-CG-MAC-010-CS édition 02/04
=== ==== ========== ================================================================================

Sommaire
========

.. toctree::
	:maxdepth: 5
	:caption: Glossaire et Liste des paramètres AC \& AD 1
	
	Glossaire

.. toctree::
	:maxdepth: 5
	:caption: Généralités
	
	Généralités


.. toctree::
	:maxdepth: 5
	:caption: Introduction
	
	Introduction

.. toctree::
	:maxdepth: 5
	:caption: Rappel des principales exigences et contraintes
	
	Exigences

.. toctree::
	:maxdepth: 5
	:caption: Présentation générale de MAJA
	
	Presentation

.. toctree::
	:maxdepth: 5
	:caption: Les algorithms
	
	Algorithms

.. toctree::
	:maxdepth: 5
	:caption: Les plugins « capteur »
	
	Plugins

