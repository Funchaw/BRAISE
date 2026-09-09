# Squelette de projet UE5 — BRAISE

Ce dossier contient le **squelette C++** du prototype défini dans
[`../docs/02-prototype/prototype-ue5.md`](../docs/02-prototype/prototype-ue5.md).
Il n'a été ni ouvert ni compilé dans cette session (pas d'Unreal Engine
disponible dans cet environnement cloud) — à ouvrir et tester dans votre
installation UE5 locale.

## Prérequis

- **Unreal Engine 5.4** installé (le fichier `BRAISE.uproject` cible cette
  version — si vous avez une autre version 5.x, faites un clic droit sur
  `BRAISE.uproject` > *Switch Unreal Engine version...*, ou éditez le champ
  `EngineAssociation` directement).
- Visual Studio 2022 (Windows) avec la charge de travail "Développement
  desktop en C++" + "Développement de jeu avec Unreal Engine", ou Xcode
  (Mac) / toolchain Linux selon votre plateforme.

## Étape 1 — Première ouverture

1. Faites un clic droit sur `BRAISE.uproject` → **Generate Visual Studio
   project files** (Windows) ou l'équivalent de votre plateforme. Ça crée
   les fichiers `.sln`/workspace nécessaires (ignorés par git).
2. Double-cliquez sur `BRAISE.uproject`. UE5 va détecter que les modules
   C++ ne sont pas compilés et proposer de les compiler — acceptez.
   Ça peut prendre plusieurs minutes la première fois.
3. Si l'éditeur s'ouvre sans erreur de compilation, le squelette est
   fonctionnel.

## Étape 2 — Ce qu'il reste à créer DANS l'éditeur

Le C++ fourni est **générique et data-driven** : il ne contient
volontairement aucune valeur définitive, aucune mesh, aucun VFX. Voici
exactement quoi créer, dans l'ordre :

### 2.1 Le personnage joueur — `BP_Tison`

- Content Browser → clic droit → *Blueprint Class* → parent
  `ABraiseCharacter` (cherchez "Braise Character").
- Dans le viewport du Blueprint : remplacez la mesh par défaut par une
  **capsule ou un cube placeholder** (Static Mesh basique).
- Onglet *Class Defaults* :
  - `Default Mapping Context` : créez un `Input Mapping Context`
    (clic droit Content Browser → Input → Input Mapping Context), nommez-le
    `IMC_Tison`.
  - `Move Action` : créez un `Input Action` (`IA_Move`, Value Type =
    Axis2D), ajoutez-le à `IMC_Tison` avec le binding WASD/clavier +
    stick gauche manette (utilisez les modificateurs *Swizzle* et
    *Negate* standards pour mapper Y/-Y, X/-X comme dans le template
    Third Person d'Epic si besoin de référence de configuration — aucun
    contenu de ce template n'est à réutiliser tel quel, seulement la
    configuration de l'Input Action).
- Sur les composants `HeatGauge`, `XPComponent`, `WeaponComponent` déjà
  présents (hérités du C++), ajustez les valeurs par défaut si besoin
  (elles ont des valeurs de départ raisonnables pour tester).
- Ajoutez un composant `UUpgradeManagerComponent` (pas encore dans le
  C++ du personnage par défaut — ajoutez-le dans ce Blueprint) et
  remplissez `AvailableUpgrades` une fois les compétences créées
  (étape 2.4).
- Dans le Blueprint, bindez `XPComponent → On Level Up` sur
  `UpgradeManagerComponent → Handle Level Up`.

### 2.2 Les Cendreux — `BP_Cendreux_BraiseEteint` et `BP_Cendreux_CendreVive`

- Deux Blueprints parent `ACendreuxBase`.
- Pour chacun, créez un `UCendreuxDefinition` (clic droit → Miscellaneous
  → Data Asset → `CendreuxDefinition`) : `DA_Cendreux_BraiseEteint` et
  `DA_Cendreux_CendreVive`, avec les valeurs de
  `docs/03-bestiaire/bestiaire.md` (archétype, vie, vitesse, dégâts).
- Dans l'Event Graph de chaque Blueprint, implémentez `On Telegraph
  Start` (jouer une anim/VFX placeholder — un simple changement de
  couleur suffit) et `On Attack Execute` (pour Cendre-vive : spawn un
  `AEmberProjectile` vers le joueur ; pour Braise-éteint : pas d'attaque
  à distance, juste des dégâts au contact via `ApplyDamage` côté joueur
  — à câbler en Blueprint sur l'event de collision).
- Mesh placeholder = cube/capsule coloré différemment par archétype.

### 2.3 Le mini-boss — `BP_MiniBoss_Prototype`

- Blueprint parent `ACendreuxBoss`.
- `PhaseHealthThresholds` a déjà `[0.5]` par défaut (2 phases) — laissez
  tel quel pour le prototype.
- Bindez `On Phase Changed` pour changer la couleur du matériau
  placeholder (valide la mécanique "corruption visible" même sans art
  final).

### 2.4 Les compétences — `BP_Upgrade_*`

Créez 3 à 5 Blueprints parent `UUpgradeDefinition` (un par compétence du
pool de départ, voir `docs/04-progression/xp-et-competences.md` pour des
exemples). Implémentez `ApplyToCharacter` pour chacune (ex : augmenter
`BaseFireRate` du `WeaponComponent`, ou `MaxWalkSpeed` du
`CharacterMovement`). Ajoutez-les tous à `AvailableUpgrades` sur
`BP_Tison`.

### 2.5 Le projectile — `BP_EmberProjectile`

- Blueprint parent `AEmberProjectile`, mesh placeholder (sphère), couleur
  qui change si `bEmpowered` est vrai (petit effet visuel simple).
- Assignez-le au champ `Projectile Class` du `WeaponComponent` sur
  `BP_Tison`.

### 2.6 Le Directeur de Horde — `BP_HordeDirector`

- Blueprint parent `AHordeDirector`.
- Remplissez `SpawnTable` avec les deux entrées (Definition +
  CendreuxClass) créées en 2.2.

### 2.7 Le niveau de test — `L_Prototype`

- File → New Level → Empty Level (ou Basic).
- Sauvegardez sous `Content/Maps/L_Prototype`.
- Placez un sol simple (plane/cube étiré), une lumière (une seule source
  de lumière dynamique forte pour préfigurer "le joueur est la seule
  lumière" — pour le prototype, une simple point light suffit).
- Placez `BP_HordeDirector` et `BP_MiniBoss_Prototype` (désactivé au
  départ, à activer manuellement pour tester, ou déclenché par un
  Trigger Volume après X secondes — au choix).
- Dans *Project Settings → Maps & Modes*, vérifiez que `L_Prototype` est
  la carte par défaut, et que `Default Pawn Class` du GameMode pointe
  vers `BP_Tison` (pas `ABraiseCharacter` directement).

### 2.8 GameMode

- Créez `BP_BraiseGameMode` (parent `ABraiseGameMode`), assignez
  `Default Pawn Class = BP_Tison`, et utilisez-le comme GameMode de
  `L_Prototype` (Override GameMode dans World Settings).

## Étape 3 — Tester

Play In Editor. Vérifiez les 4 critères de validation listés dans
`docs/02-prototype/prototype-ue5.md`. Notez vos retours (ressenti,
bugs, réglages à ajuster) — c'est ce qui guidera l'itération suivante,
pas une nouvelle liste de fonctionnalités.

## Ce qui n'est PAS dans ce squelette (normal, hors périmètre)

- UI de choix de compétence (à faire en UMG — non fournie, le C++ expose
  juste le delegate `OnUpgradeChoicesReady`).
- HUD (jauge de chaleur visuelle, XP, timer) — idem, à faire en UMG.
- Biomes multiples, Codex, sauvegarde câblée (squelette `UBraiseSaveGame`
  présent mais non utilisé, volontairement — voir prototype scope).
- Toute direction artistique, musique, son définitifs.
