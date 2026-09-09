# BRAISE

Nouveau jeu vidéo commercial original — un successeur spirituel des
shoot'em up atmosphériques de l'ère Amiga (esprit *Agony*), sans licence,
sans réutilisation d'assets, avec son propre univers, ses propres
personnages, son propre code et sa propre identité commerciale.

## Statut

**Phase 1 — Concept validé, game design en cours.** Le concept *BRAISE*
a été retenu. Aucun code n'a encore été écrit ; prochaine étape : cadrer
précisément le premier prototype jouable avant tout développement UE5
(voir "Méthode de travail" plus bas).

## Règle d'or

> Notre objectif n'est pas de faire un meilleur *Agony*. Notre objectif
> est de créer un excellent nouveau shoot'em up moderne qui procure
> certaines sensations nostalgiques des grands jeux Amiga tout en
> possédant sa propre identité.

L'ancien jeu sert uniquement de référence de conception et de benchmark
(voir [`reference/README.md`](./reference/README.md) pour les règles
d'usage strictes des fichiers Amiga). Aucun asset (sprite, texture,
musique, son, code, niveau, nom, texte) de la référence n'est ni ne sera
réutilisé.

## Documents disponibles

- [`docs/00-analyse/01-analyse-gameplay.md`](./docs/00-analyse/01-analyse-gameplay.md)
  — analyse gameplay et game feel du genre de référence, ce qui a vieilli.
- [`docs/00-analyse/02-fiches-mecaniques.md`](./docs/00-analyse/02-fiches-mecaniques.md)
  — fiches mécanique par mécanique (originale → modernisation → nouvelle
  version → implémentation UE5 envisagée).
- [`docs/01-concepts/concepts-originaux.md`](./docs/01-concepts/concepts-originaux.md)
  — 3 concepts de jeux originaux, comparaison, et sélection recommandée
  (**Concept B — *BRAISE***).
- [`docs/02-prototype/prototype-ue5.md`](./docs/02-prototype/prototype-ue5.md)
  — périmètre exact du premier prototype jouable (formes simples, aucun
  asset final).

## Méthode de travail

On avance étape par étape, jamais tout d'un coup :
objectif → tâches → production → test → retour → correction → validation
→ étape suivante. Le code ne démarre qu'une fois le concept et le
gameplay validés par le test du prototype.

## Concept retenu ✅

**BRAISE** — dans un monde où le soleil s'est éteint, le joueur incarne un
esprit-braise né des dernières forges vivantes, seule source de lumière et
de chaleur à l'écran, dans un combat aérien contre les entités de cendre
qui veulent l'éteindre. Mécanique centrale : jauge de chaleur risque/
récompense (charger le tir attire le danger).

Détails complets dans
[`docs/01-concepts/concepts-originaux.md`](./docs/01-concepts/concepts-originaux.md)
(*Necroveil* et *Hollow Choir* restent archivés comme pistes de secours).

---

## PROCHAINE ACTION

Avant de construire le prototype UE5, quelques décisions concrètes de
game design restent ouvertes (voir la question posée dans le chat) :
nom du protagoniste, boucle de gameplay seconde par seconde, et réglages
précis de la jauge de chaleur. Une fois ces points tranchés, la tâche
suivante sera de **construire le squelette du premier prototype UE5**
décrit dans
[`docs/02-prototype/prototype-ue5.md`](./docs/02-prototype/prototype-ue5.md)
(joueur, tir, jauge de chaleur, 2 ennemis, 1 power-up, 1 mini-boss, formes
simples) — toujours sans graphismes définitifs, pour tester uniquement le
game feel.
