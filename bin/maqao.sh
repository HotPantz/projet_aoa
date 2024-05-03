#!/bin/bash

# Vérifier si un argument est fourni
if [ $# -ne 1 ]; then
    echo "Usage: $0 <type_d_optimisation>"
    exit 1
fi

# Récupérer le type d'optimisation à partir du premier argument
opti_type=$1

# Vérifier si un exécutable avec le nom spécifié est présent
if [ ! -x "./measure_phase2_$opti_type" ]; then
    echo "Aucun exécutable avec le nom spécifié n'est présent dans ce répertoire."
    exit 1
fi

# Lancer la commande avec maqao
maqao OV --replace -R1 -xp="$opti_type" -uarch=ZEN_V1 -- "./measure_phase2_$opti_type" 300 18 1750

# Déplacer le répertoire opti_one_html dans le dossier bin avec le nom de l'optimisation spécifié
#rm -r ./measure_phase2_"$opti_type"_one_html
mv -f ./"$opti_type"/RESULTS/measure_phase2_"$opti_type"_one_html .
