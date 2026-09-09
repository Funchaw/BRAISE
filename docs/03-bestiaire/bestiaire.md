# Bestiaire & Biomes — les Cendreux

Toutes les créatures du jeu appartiennent à **la Cendre**, force qui
cherche à éteindre les dernières lumières du monde. Elles sont collectivement
appelées **Cendreux**. Aucun nom, silhouette ou comportement ci-dessous ne
reprend un élément d'un jeu existant — la structure (archétypes par
rôle) s'inspire de la logique générale des survivors-likes, le contenu est
original.

## Archétypes transversaux (présents dans plusieurs biomes, variantes visuelles par biome)

| Archétype | Rôle | Comportement | Tell (télégraphie) |
|---|---|---|---|
| **Braise-éteint (Fodder)** | Chair à canon, pression de nombre | Fonce en ligne droite vers le joueur | Aucun (danger = nombre, pas surprise) |
| **Cendre-vive (Ranged)** | Pression à distance | Garde ses distances, tire un projectile lent | Clignote avant de tirer (0.4s) |
| **Fondu (Charger)** | Punit l'immobilité | Charge en ligne droite après un temps d'arrêt | S'immobilise et vibre avant la charge |
| **Éclateur (Exploder)** | Punit le corps-à-corps aveugle | Fonce, explose en zone à l'impact ou à la mort | S'illumine juste avant d'exploser |
| **Étouffeur (Suppressor)** | Contrôle de zone | Émet un champ qui réduit la jauge de chaleur du joueur à proximité | Zone d'effet visible en permanence (pas de surprise, danger positionnel) |
| **Élite (Elite)** | Mini-boss de vague | Variante surdimensionnée d'un archétype existant avec 1 capacité additionnelle | Aura visuelle distincte + annonce sonore à l'apparition |

Ces archétypes définissent des **comportements**, pas des créatures
finales — chaque biome les habille avec sa propre silhouette et son propre
thème visuel (voir ci-dessous), pour éviter la sensation de "reskin"
paresseux : la charte artistique de chaque biome doit rendre ses Cendreux
visuellement distincts, seul le rôle de gameplay est partagé.

## Biome 1 — Les Cendrières (tutoriel)

- **Thème visuel** : plaines de cendre grise à perte de vue, quelques
  arbres calcinés, ciel bas.
- **Cendreux présents** : Braise-éteint, Cendre-vive (formes simples,
  serves d'introduction).
- **Élite de biome** : "Le Cendrier" — Braise-éteint élite qui laisse une
  traînée de cendre ralentissante derrière lui.
- **Événement signature** : "Vent de cendre" — bourrasque périodique qui
  réduit temporairement la visibilité (pousse le joueur à se fier au son).
- **Boss de biome** : *Le Premier Éteint* — grand Cendreux humanoïde figé,
  pattern en 2 phases (corruption visible : ses fissures s'assombrissent
  à mesure qu'il perd de la vie, jusqu'à s'effondrer en cendres).

## Biome 2 — La Forge Engloutie

- **Thème visuel** : ruines industrielles à demi-effondrées, structures
  métalliques rougeoyantes, chaleur ambiante.
- **Cendreux présents** : Fondu, Éclateur, variante "brûlante" du
  Cendre-vive (projectile plus rapide).
- **Élite de biome** : "Le Forgeron Éteint" — Fondu élite dont la charge
  laisse une traînée de chaleur (synergise/entre en tension avec la jauge
  du joueur : bon pour charger sa jauge si on ose s'approcher).
- **Événement signature** : "Coulée" — un couloir de chaleur traverse
  la zone périodiquement, dangereux à traverser mais accélère
  temporairement la recharge de chaleur du joueur (risque/récompense).
- **Boss de biome** : *La Forge Vivante* — structure semi-immobile à
  plusieurs points faibles rotatifs, phases liées à la destruction
  progressive de ses parties (pas une simple barre de vie).

## Biome 3 — Le Rivage Éteint

- **Thème visuel** : côte figée dans un crépuscule permanent, eau sombre
  immobile, brume basse.
- **Cendreux présents** : Étouffeur, Braise-éteint (variante lente mais
  nombreuse), Cendre-vive (variante à tir en arc).
- **Élite de biome** : "La Noyée de Cendre" — Étouffeur élite à large
  rayon d'effet.
- **Événement signature** : "Marée de cendre" — montée temporaire du
  niveau de cendre qui réduit l'espace jouable (écho direct de la
  mécanique "fenêtre de tension" définie en fiche mécanique 2).
- **Boss de biome** : *Le Dernier Reflet* — Cendreux à double phase
  (terrestre puis aquatique), teste l'adaptation du joueur aux deux
  types d'espace de jeu.

## Codex (fonctionnalité de progression méta)

Chaque Cendreux rencontré au moins une fois est enregistré dans le
**Codex des Cendreux**, consultable hors run : silhouette, archétype,
biome d'origine, et une ligne de lore courte. Le Codex se remplit
automatiquement — aucune action dédiée requise du joueur — et sert de
métrique de complétion pour le end-game/achievements Steam.

## Règle de conception pour tout futur ajout de Cendreux

Avant d'ajouter une nouvelle créature : identifier son **archétype de
comportement** (un des 6 ci-dessus, ou un nouveau si aucun ne convient),
son **biome**, et son **tell**. Un Cendreux sans tell clair n'est ajouté
que dans les archétypes "pression de nombre" (Braise-éteint) — jamais
pour un archétype à dégâts ponctuels élevés, pour rester fidèle au
principe de lisibilité défini en fiche mécanique 3.

➡️ Suite : [`../04-progression/xp-et-competences.md`](../04-progression/xp-et-competences.md)
