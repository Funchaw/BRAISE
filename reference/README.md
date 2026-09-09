# Dossier de référence — matériel d'analyse uniquement

Ce dossier est **exclu de git** (`.gitignore`). Il ne doit jamais contenir
d'assets destinés au nouveau jeu.

## Ce que ce dossier peut contenir

Vos fichiers de l'ancienne version Amiga (ROM/ADF, disassembly, captures,
notes), pour que l'analyse de gameplay puisse s'appuyer sur des observations
précises plutôt que sur la mémoire générale du genre.

## Règle absolue

- **Analyse autorisée** : timings, patterns d'ennemis, courbes de difficulté,
  structure de niveaux, comportement des power-ups, cadence de tir, etc.
- **Réutilisation interdite** : sprites, palettes, musiques, sons, code,
  cartes de niveaux, noms, textes, logos — rien de tout cela ne doit être
  extrait, converti ou réencodé dans le nouveau projet.

Le pipeline est : **OBSERVATION → COMPRÉHENSION → NOUVELLE CONCEPTION →
NOUVELLE IMPLÉMENTATION**, jamais ISO → conversion → copie.

## Si vous déposez des fichiers ici

Dites-le moi et précisez ce qu'ils contiennent (ROM complète, captures
d'écran, notes de speedrun, disassembly...) — j'ajusterai les fiches de
`docs/00-analyse/` avec des observations plus précises, sans jamais faire
référence à des extraits protégés dans les documents versionnés.
