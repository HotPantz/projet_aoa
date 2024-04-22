#AOA - Sujet 7

## Makefile
Le Makefile dans /src/ permet de compiler tous les binaires utilisés pour les expériences

make : 
L'invocation de "make" compile les drivers et les kernels communs, ie. avec GCC

make icx :
Compile les kernel avec ICX

make fred/sami : 
Compile les kernel avec AOCC 
AOCC est invoqué avec la commande "clang", pour ne pas redéfinir le chemin de ce dernier, on utilise des
chemins complets vers le binaire de AOCC clang : pour compiler, il faudra changer le chemin dans la 
variable AOCC / AOCC2 en le remplaçant avec le chemin sur son système.

## Graphique de la calibration des warmups : warmup_calib.sh
Ce script lance le driver calibration sur la taille de la donnée définie par 
la variable SIZE, nombre de répétitions REPS et fréquence FREQ du processeur

La fréquence est fixée avec la commande cpupower lancée dans le script même
Le driver calibration est lancé avec taskset afin de le pin (changer le coeur si besoin, 1 par défaut)

UTILISATION :
1. Aller dans /scripts/
2. Changer les valeurs de SIZE, REPS, FREQ (et le coeur sur lequel on pin, si besoin)
3. Lancer la commande ./warmup_calib.sh
4. Les résultats de l'expérience sont dans ../calibration_data/warmups_calibrate_results.txt

## Graphique de l'étalonnage des répétitions : rdtsc_calib.sh
Ce script lance le driver "normal" (measure) sur la taille de la donnée définie par 
la variable SIZE, nombre de répétitions REPS et fréquence FREQ du processeur

La fréquence est fixée avec la commande cpupower lancée dans le script même
Le driver calibration est lancé avec taskset afin de le pin (changer le coeur si besoin, 1 par défaut)

UTILISATION : 
1. Aller dans /scripts/
2. Changer les valeurs de SIZE, REPS, FREQ (et le coeur sur lequel on pin, si besoin)
3. Lancer la commande ./warmup_calib.sh
4. Les résultats de l'expérience sont dans ../calibration_data/rdtsc_calibration_results.txt

## Graphique montrant les frontieres entre les niveaux de mémoire
Ce script lance le driver de base (GCC -O2) measure sur des tailles de donnée
différentes, contenues dans le tableau "arg_values"

UTILISATION:
1. Aller dans /scripts/
2. Changer les valeurs de warmups, reps et ajouter/supprimer des valeurs dans arg_values
3. Lancer la commande ./cache_levels.sh
4. Les résultats de l'expérience sont dans ../results/cache_levels_results.txt

## Graphique montrant les performances des variantes de compilation 
Ce script lance tous les binaires spécifiés dans la liste "commands", eux mêmes
situés dans le répértoire /bin/
Les résultats des expériences se trouvent dans /results/
Les mesures sont lancées avec cpupower et taskset.

Changer : commandes dans "commands" (AOCC/ICX), warmups, reps, size, coeur affecté dans taskset

UTILISATION:
1. Aller dans /scripts/
2. Changer : commandes dans "commands" (AOCC/ICX), warmups, reps, size, coeur affecté dans taskset
3. Lancer la commande ./measures_amd.h ; ./measures_icx.h
4. Les résultats de l'expérience sont dans /results/



