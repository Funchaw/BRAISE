# BRAISE

Nouveau jeu vidéo commercial original — un successeur spirituel des
shoot'em up atmosphériques de l'ère Amiga (esprit *Agony*), fusionné avec
une boucle de progression façon survivors-like (inspiration Megabonk/
Vampire Survivors : XP, compétences aléatoires, bestiaire, biomes). Sans
licence, sans réutilisation d'assets, avec son propre univers, ses propres
personnages, son propre code et sa propre identité commerciale.

## Statut

**Phase 2 — Prototype en cours de construction.** Concept validé, game
design de la fusion shmup/survivors-like posé, et un premier **squelette
de projet UE5** a été généré (voir [`unreal/`](./unreal/)). Il reste à
l'ouvrir dans un UE5 local, y construire les Blueprints/niveau de test
décrits dans [`unreal/README.md`](./unreal/README.md), et jouer au
prototype pour valider le game feel.

## Règle d'or

> Notre objectif n'est pas de faire un meilleur *Agony*, ni un clone de
> Megabonk/Vampire Survivors. Notre objectif est de créer un excellent
> jeu original qui procure des sensations nostalgiques des grands shmups
> Amiga tout en empruntant une structure de progression moderne éprouvée,
> le tout fondu dans sa propre identité.

L'ancien jeu de référence sert uniquement de benchmark de conception
(voir [`reference/README.md`](./reference/README.md)). Aucun asset
(sprite, texture, musique, son, code, niveau, nom, texte) d'aucune
référence (Agony, Vampire Survivors, Megabonk) n'est ni ne sera réutilisé
— seules des structures de gameplay génériques du genre sont réinterprétées.

## Univers & protagoniste

- **Monde** : Braise — le soleil s'est éteint, les derniers foyers de vie
  s'organisent autour des dernières forges vivantes.
- **Protagoniste** : **Tison**, un esprit-braise né de ces forges, seule
  source de lumière et de chaleur du monde. *(Nom choisi faute de
  préférence exprimée — à changer librement si besoin, un seul terme à
  mettre à jour dans les docs et le code.)*
- **Antagonistes** : la Cendre, et ses créatures, les **Cendreux**
  (bestiaire détaillé dans `docs/03-bestiaire/`).

## Documents disponibles

- [`docs/00-analyse/01-analyse-gameplay.md`](./docs/00-analyse/01-analyse-gameplay.md)
  — analyse gameplay et game feel du genre shmup de référence.
- [`docs/00-analyse/02-fiches-mecaniques.md`](./docs/00-analyse/02-fiches-mecaniques.md)
  — fiches mécanique par mécanique (originale → modernisation → UE5).
- [`docs/01-concepts/concepts-originaux.md`](./docs/01-concepts/concepts-originaux.md)
  — 3 concepts originaux, comparaison, décision (**BRAISE** retenu).
- [`docs/01-concepts/braise-gdd-v2.md`](./docs/01-concepts/braise-gdd-v2.md)
  — **GDD à jour** : fusion shmup atmosphérique × survivors-like, piliers,
  boucle de jeu, biomes, roadmap de fonctionnalités.
- [`docs/03-bestiaire/bestiaire.md`](./docs/03-bestiaire/bestiaire.md)
  — archétypes de Cendreux, 3 biomes détaillés, Codex.
- [`docs/04-progression/xp-et-competences.md`](./docs/04-progression/xp-et-competences.md)
  — système XP, montées de niveau, pool de compétences, rareté.
- [`docs/02-prototype/prototype-ue5.md`](./docs/02-prototype/prototype-ue5.md)
  — périmètre exact du premier prototype jouable.
- [`unreal/`](./unreal/) — **squelette de projet UE5 (C++)** du prototype
  + [`unreal/README.md`](./unreal/README.md) : guide pas-à-pas pour
  l'ouvrir, compiler, et construire les Blueprints/niveau manquants.

## Méthode de travail

On avance étape par étape : objectif → tâches → production → test →
retour → correction → validation → étape suivante.

## Note technique importante

Cette session tourne dans un environnement cloud **sans Unreal Engine
installé** — le code a été écrit avec soin (patterns UE5 standards) mais
n'a pas pu être compilé ni testé ici. La première étape concrète pour
vous est d'ouvrir `unreal/BRAISE.uproject` dans votre UE5 local : s'il y a
une erreur de compilation, dites-le moi (copiez le message d'erreur) et
je corrige.

---

## PROCHAINE ACTION

1. Ouvrez `unreal/BRAISE.uproject` dans Unreal Engine 5 (voir
   [`unreal/README.md`](./unreal/README.md) pour les prérequis) et
   vérifiez que le projet compile.
2. Suivez le guide pas-à-pas de `unreal/README.md` pour créer les
   Blueprints et le niveau de test (BP_Tison, 2 types de Cendreux, le
   mini-boss, 3-5 compétences, le niveau `L_Prototype`).
3. Jouez au prototype et évaluez-le contre les 4 critères de
   `docs/02-prototype/prototype-ue5.md`.
4. Revenez avec vos retours (ce qui marche, ce qui ne marche pas, erreurs
   de compilation éventuelles) — c'est ce qui guide l'itération suivante.
