# Premier prototype UE5 — définition de portée (v2, post-fusion Megabonk)

> Ce document remplace la v1 (shmup pur à défilement) suite au pivot vers
> une structure survivors-like en zone semi-ouverte (voir
> `docs/01-concepts/braise-gdd-v2.md`). Toujours : **GAMEPLAY > GRAPHISMES**,
> formes simples, aucun asset final.

## Objectif du prototype

Valider, jouable, que la boucle centrale fonctionne : déplacement libre +
jauge de chaleur (risque/récompense) + montée en puissance par XP/
compétences aléatoires + pression d'une horde de Cendreux croissante +
un mini-boss lisible.

## Contenu du prototype (périmètre fermé)

1. **Zone de jeu** : une seule arène semi-ouverte, plane, taille modeste
   (assez grande pour courir, pas un "monde ouvert" au sens plein — un
   rectangle/cercle de terrain suffit).
2. **Joueur (Tison)** : déplacement libre à la manette/clavier (8+
   directions), pas de défilement forcé, vitesse et inertie légère
   comme définies en fiche mécanique 2.
3. **Tir** : automatique vers l'ennemi le plus proche ou dirigé (à
   trancher au test — commencer par automatique, plus proche de l'ADN
   survivors-like), alimenté par la jauge de chaleur (fiche mécanique 1
   adaptée : charge en tirant, tir renforcé à jauge haute, seuil de
   surchauffe).
4. **Cendreux (2 archétypes suffisent au prototype)** :
   - un **Braise-éteint** (fonce en ligne droite, pression de nombre) ;
   - un **Cendre-vive** (garde ses distances, tire, avec tell visuel).
5. **Directeur de horde minimal** : spawn des Cendreux à fréquence
   croissante avec le temps (une simple courbe suffit, pas besoin du
   système complet biome par biome).
6. **XP & montée de niveau** : Éclats de Braise lâchés à la mort d'un
   Cendreux, magnétisme simple vers le joueur, seuil d'XP déclenchant un
   choix de **3 compétences** parmi un pool restreint (3-5 compétences
   suffisent au prototype, une par catégorie du document
   `docs/04-progression/xp-et-competences.md`).
7. **Un mini-boss** : forme simple avec 2 phases (seuil de vie), reprend
   la mécanique "corruption visible" (fiche mécanique 5) même en
   placeholder (changement de couleur/matériau suffit).
8. **Score/temps de survie** : compteur simple à l'écran (Cendreux
   détruits + temps écoulé).

## Explicitement hors périmètre du prototype

- plusieurs biomes (un seul suffit) ;
- Codex/bestiaire consultable ;
- progression méta entre runs (Braisier, déblocages) ;
- narration, cinématiques ;
- musique/son définitifs (placeholder minimal) ;
- menus/options avancés, sauvegarde ;
- direction artistique finale ;
- pool complet de compétences (voir document dédié — 3-5 suffisent ici).

## Critères de validation du prototype

- le déplacement libre est agréable sans réglage fin ;
- la jauge de chaleur crée un vrai dilemme perceptible ;
- la montée de niveau et le choix de compétence sont clairs et
  gratifiants, même avec un pool restreint ;
- la pression de la horde croissante se sent "juste" (ni trop lente ni
  écrasante) sur une session de 3-5 minutes ;
- le mini-boss est lisible sans texte explicatif.

## Environnement technique

Aucun moteur graphique n'étant disponible dans cette session cloud, le
squelette de projet UE5 (structure de dossiers, classes C++ de base) est
livré dans [`../../unreal/`](../../unreal/) — voir
[`../../unreal/README.md`](../../unreal/README.md) pour l'ouvrir et le
tester dans un UE5 installé localement, et pour la liste des éléments à
créer dans l'éditeur (Blueprints dérivés, niveau de test, Input Actions).
