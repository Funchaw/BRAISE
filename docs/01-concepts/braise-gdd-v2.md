# BRAISE — Game Design Document v2 (fusion Shmup atmosphérique × Survivors-like)

> **Pivot acté le 2026-09-09.** En plus de l'ADN "shoot'em up Amiga
> atmosphérique" (voir `docs/00-analyse/`), le jeu intègre désormais une
> inspiration **Megabonk / Vampire Survivors** : XP, montée de niveau avec
> choix aléatoire de compétences, bestiaire nombreux, plusieurs biomes,
> déplacement libre dans des zones semi-ouvertes. Ce document est la
> référence de design à jour ; `docs/01-concepts/concepts-originaux.md`
> reste l'historique de la décision initiale.

## Note de cadrage (Producteur/Game Director)

"Monde ouvert" + "toutes les meilleures fonctionnalités actuelles" est une
ambition illimitée par nature — aucun studio, même AAA, ne construit tout
en même temps. Pour rester réalisable **sans rien retirer de la vision**,
le jeu est structuré en **biomes semi-ouverts indépendants** (chacun une
grande arène explorable, pas un seul monde continu sans coupures) et en
**phases d'ajout de fonctionnalités** (roadmap en fin de document). Ça
donne la sensation d'un monde ouvert riche tout en gardant chaque biome
développable et testable isolément. C'est une recommandation de cadrage,
pas une restriction de la vision : tout ce qui est décrit ci-dessous est
prévu, dans l'ordre qui permet de livrer un jeu qui marche à chaque étape.

## Pitch v2

Dans **Braise**, le soleil s'est éteint. Le joueur incarne **Tison**, un
esprit-braise né des dernières forges vivantes du monde, seule source de
lumière et de chaleur sur les terres mourantes. Il erre à travers les
biomes agonisants du monde, absorbant l'essence des créatures de **la
Cendre** pour grandir en puissance, avant que la dernière lumière ne
s'éteigne pour de bon.

## Piliers de design (inchangés, renforcés par la fusion)

1. **Le joueur est la seule lumière** — mécanique ET signature visuelle.
2. **Risque/récompense via la chaleur** — briller plus = frapper plus fort
   mais attirer plus de danger (voir Fiche mécanique "Charge et Braise").
3. **Croissance de puissance lisible et gratifiante** — désormais portée
   par le système XP/compétences (nouveau pilier apporté par la fusion).
4. **Un bestiaire vivant et varié** — pas juste "plus d'ennemis", des
   comportements et silhouettes multiples par biome (nouveau pilier).
5. **Rythme traversée/confrontation** — conservé, mais réinterprété : dans
   une zone ouverte, la "traversée" devient l'exploration entre les vagues,
   la "confrontation" devient l'escalade de horde typique du genre
   survivors-like.

## Structure d'un run

Un run se déroule dans **un biome à la fois** (grande zone semi-ouverte,
pas un couloir de scroll comme un shmup classique) :

1. **Arrivée** — Tison apparaît au centre d'une zone. Peu d'ennemis,
   exploration libre, premiers Éclats de Braise (XP) au sol.
2. **Escalade** — un **Directeur de Horde** augmente progressivement la
   fréquence et la difficulté des vagues de Cendreux au fil du temps
   (courbe façon "survivors-like" : ça ne redescend jamais, seule la
   puissance du joueur permet de suivre).
3. **Montées de niveau** — chaque niveau d'XP gagné propose **3 choix
   aléatoires** de compétences/améliorations (voir document dédié
   `docs/04-progression/xp-et-competences.md`).
4. **Événements de biome** — mini-boss et événements spéciaux propres à
   chaque biome apparaissent à intervalles (temps écoulé + seuil de
   puissance du joueur), pas uniquement en fin de run.
5. **Boss de biome** — apparaît à un jalon de temps fixe ou en dernière
   phase de la zone ; vaincre le boss termine le run avec succès (ou le
   joueur peut choisir de continuer en mode "survie prolongée" à
   difficulté croissante infinie, façon high-score).
6. **Fin de run** — mort du joueur ou victoire sur le boss. Gain de
   **progression méta** (voir plus bas) quel que soit le résultat, pour
   éviter la frustration d'un run "perdu pour rien".

## Boucle seconde par seconde

Se déplacer librement → repérer les Cendreux et les Éclats de Braise →
gérer la jauge de chaleur (tirer charge la jauge ; une jauge haute = tirs
plus forts mais Tison brille plus fort et attire des vagues plus dures) →
détruire des Cendreux → ramasser XP → au level up, choisir une compétence
parmi 3 → s'adapter à l'escalade de horde → survivre aux événements de
biome → affronter le boss.

## Système de chaleur × système XP : la synergie qui différencie Braise

C'est le point de différenciation le plus important vis-à-vis de Vampire
Survivors/Megabonk (où la difficulté monte uniquement avec le temps) :

- Dans Braise, la difficulté monte avec le **temps ET la lumière émise par
  le joueur**. Un joueur qui optimise son build offensif (plus de chaleur,
  plus de dégâts) est *littéralement plus visible* et attire des vagues
  plus dangereuses — le scaling de difficulté est diégétique, pas une
  simple courbe invisible.
- Ça crée un vrai choix de build : jouer "discret" (chaleur basse,
  progression plus lente mais plus sûre) vs jouer "brasier" (chaleur
  haute, croissance rapide, danger maximal) — les deux étant viables
  selon les compétences choisies.

## Biomes (structure, contenu détaillé dans `docs/03-bestiaire/`)

Chaque biome = une zone semi-ouverte + un sous-ensemble du bestiaire + un
hasard/événement signature + un boss dédié. Voir
`docs/03-bestiaire/bestiaire.md` pour le détail complet. Prévus au
lancement (ordre de difficulty croissante) :

1. **Les Cendrières** (biome tutoriel — plaines de cendre grises, peu de
   danger environnemental, sert d'introduction aux Cendreux de base).
2. **La Forge Engloutie** (ruines industrielles à demi-effondrées,
   dangers de chaleur environnementale, synergique avec la mécanique de
   chaleur du joueur).
3. **Le Rivage Éteint** (côte figée, Cendreux aquatiques/lents mais
   nombreux, event signature : marées de cendre qui réduisent
   temporairement la visibilité).

D'autres biomes sont prévus en post-lancement (voir roadmap).

## Progression méta (entre les runs)

- **Braisier** (monnaie méta gagnée par run, proportionnelle à la
  progression atteinte) débloque : compétences de départ additionnelles,
  nouveaux biomes, entrées de bestiaire (codex), variantes de Tison.
- Le **Codex des Cendreux** (bestiaire consultable) se remplit au fil des
  rencontres — sert à la fois de contenu de progression et d'outil
  pédagogique (le joueur apprend les patterns hors run aussi).
- Pas de RPG stats profondes ni d'inventaire lourd — la méta-progression
  reste légère, conformément à la philosophie arcade du projet (voir règle
  d'or du README).

## Ce qui ne change PAS de la version shmup pure

- Le principe de télégraphie des attaques ennemies (fiche mécanique 3).
- Boss à "corruption visible" plutôt que barre de vie classique
  (fiche mécanique 5), désormais également utilisé pour les mini-boss de
  biome.
- Le ton et la direction artistique (monde en cendre, seule source de
  lumière = le joueur).
- La règle d'or : sensations nostalgiques du shmup Amiga + identité
  propre, jamais une redite d'un autre jeu (ni Agony, ni Vampire
  Survivors, ni Megabonk).

## Roadmap de fonctionnalités (pour tenir "toutes les meilleures
fonctionnalités actuelles" sans exploser le planning)

| Phase | Contenu |
|---|---|
| **Prototype (maintenant)** | 1 biome de test, mouvement, chaleur, tir, XP, 3 compétences, 3 types de Cendreux, 1 mini-boss. Formes simples. |
| **Vertical Slice** | 1 biome complet et poli (Les Cendrières), 8-10 compétences, 6-8 Cendreux, 1 boss de biome complet, Codex basique. |
| **Production v1** | 3 biomes, bestiaire complet par biome, progression méta (Braisier), sauvegarde. |
| **Post-launch** | biomes additionnels, New Game+/mode survie infinie, leaderboards, achievements Steam, Steam Cloud, co-op éventuel (à évaluer — non promis). |

➡️ Suite : [`../03-bestiaire/bestiaire.md`](../03-bestiaire/bestiaire.md) et
[`../04-progression/xp-et-competences.md`](../04-progression/xp-et-competences.md)
