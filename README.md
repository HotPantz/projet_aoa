# Projet Architecture des Ordinateurs Appronfondie
## Introduction :

Ce projet vise à optimiser un code source donné en utilisant différentes techniques d'optimisation et d'analyse de performance. Le code sera compilé et exécuté sur le cluster OB-1 ou sur des machines personnelles des membres de l'équipe.

## Objectif :

L'objectif principal est d'améliorer les performances du code en optimisant ses options de compilation ainsi que sa structure même à travers des transformations de code. Les performances seront mesurées et comparées à différentes étapes du processus d'optimisation.

## Phases du Projet :

### Phase I - Options de Compilation :

Calcul de la taille du problème pour s'adapter aux niveaux mémoire ciblés.
    Mesure de la performance du noyau avec différentes options de compilation telles que gcc (-O2, -O3, -O3 -march=native), icx (Intel), ou AOCC (AMD Zen).
    Exploration et combinaison d'autres options d'optimisation pertinentes.
    Explication des différences de performances entre versions en se basant sur les rapports MAQAO.
### Phase II - Transformation de Code :

#### Phase II.1 (gcc -O2 imposé) :

Configuration de la compilation avec gcc -O2.
Mesure initiale de la performance du noyau.
Analyse du noyau avec MAQAO pour identifier les goulets d'étranglement.
Proposition et implémentation d'optimisations au niveau du code source.
Itération sur les étapes précédentes pour améliorer les performances.

#### Phase II.2 (Compilateur et options modifiables) :

Utilisation de compilateurs alternatifs et d'options de compilation plus agressives.
Itération sur les étapes précédentes pour continuer à améliorer les performances.

## Consignes de Réalisation :

Justification de chaque choix effectué tout au long du projet.
Utilisation de MAQAO, likwid-perfctr, et/ou perf-stat pour l'analyse des performances et des goulets d'étranglement.
Exploration et application des transformations de boucles pour optimiser le code.
Optionnellement, parallélisation du code avec des directives OpenMP ou utilisation d'intrinsics pour l'optimisation avancée du code.
