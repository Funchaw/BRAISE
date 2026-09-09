# Fiches mécaniques — de l'ancien gameplay au nouveau

Format : Mécanique originale → Pourquoi elle fonctionne → Problème actuel →
Modernisation → Nouvelle version (originale) → Implémentation UE5.

---

## Fiche 1 — Transformation par power-up

**Mécanique originale** : le personnage change entièrement de forme en
ramassant certains objets ; chaque forme a son propre pattern de tir et sa
propre silhouette de collision.

**Pourquoi elle fonctionne** : c'est un power fantasy qualitatif (on devient
autre chose) et pas seulement quantitatif (plus de dégâts). Elle renouvelle
l'intérêt visuel et stratégique en continu.

**Problème éventuel** : dans l'original la transformation est souvent
temporaire/aléatoire et peu lisible pour le joueur (on ne sait pas toujours
ce qu'on va devenir ni pourquoi).

**Modernisation** : rendre le choix de forme lisible, intentionnel, et
persistant sur la durée d'un run (pas juste 10 secondes), avec un vrai
arbre de compromis (chaque forme a une force et une faiblesse claire).

**Nouvelle version** : **système de "Noyaux" interchangeables en temps réel**
— le joueur porte 2 noyaux équipés sur les 3-4 débloqués dans le run, et
peut basculer entre eux à la volée (pas de ramassage aléatoire). Chaque
noyau redéfinit tir principal + mobilité + une capacité passive. Le choix
tactique (quel noyau pour quelle situation) devient une compétence à part
entière, pas un hasard.

**Implémentation UE5** :
- Un `Data Asset` par noyau (`UCoreDataAsset`) décrivant : classe de projectile,
  cadence, vitesse de déplacement modifiée, capacité passive (tag Gameplay).
- Le pawn joueur possède un composant `UCoreLoadoutComponent` qui swap la
  configuration active (changement d'Enhanced Input mapping context, de
  Niagara de tir, de vitesse) en < 0.15s pour rester instantané au ressenti.
- Le C++ gère le composant et l'interface `ICoreBehavior` ; les *données*
  de chaque noyau restent en Data Asset pour que le design puisse itérer
  sans recompiler.

---

## Fiche 2 — Vitesse joueur > vitesse de scroll (contrôle aérien total)

**Mécanique originale** : le joueur se déplace bien plus vite que le
défilement du décor, sur les 4 bords de l'écran.

**Pourquoi elle fonctionne** : donne une sensation de maîtrise totale de
l'espace de jeu, contrairement aux shmups où le joueur est à peine plus
rapide que le danger.

**Problème éventuel** : sur un écran large moderne (16:9, ultrawide), l'espace
de jeu est très différent de l'écran 4:3 d'origine ; l'équilibrage vitesse
doit être repensé, pas recopié.

**Modernisation** : garder le principe (liberté de positionnement) mais
l'adapter à un espace de jeu plus large avec des zones de caméra dynamiques
plutôt qu'un cadre fixe.

**Nouvelle version** : **caméra à "fenêtre de tension"** — la zone jouable
se resserre légèrement dans les phases de confrontation (moins d'espace,
plus de danger perçu) et s'élargit dans les phases de traversée (plus de
liberté, respiration). La vitesse du joueur reste constante, c'est l'espace
qui respire.

**Implémentation UE5** : `Camera Component` piloté par un `Spring Arm`
+ une timeline/courbe pilotée par des volumes déclencheurs dans le niveau
(ou des events Data Table liés aux vagues d'ennemis), qui interpole le FOV
et les limites horizontales/verticales de la zone jouable (clamp appliqué
dans le mouvement du pawn, pas seulement visuel).

---

## Fiche 3 — Ennemis à patterns organiques + apparitions cachées

**Mécanique originale** : trajectoires sinusoïdales, apparitions hors-champ
qui récompensent la mémorisation du niveau.

**Pourquoi elle fonctionne** : crée une progression de skill basée sur la
connaissance du niveau (comme un die-and-retry doux), sans être punitif au
point de sembler injuste une fois le pattern appris.

**Problème éventuel** : la mémorisation pure est frustrante pour un public
qui n'a pas le temps de "apprendre par cœur" un niveau (moins de tolérance
qu'en 1992).

**Modernisation** : garder des patterns organiques et lisibles au premier
run (télégraphie claire), réserver la pure mémorisation aux niveaux de
difficulté élevée / modes "arcade".

**Nouvelle version** : **ennemis à "intention visible"** — une micro-
animation ou un effet Niagara précède systématiquement toute action
dangereuse (0.3-0.5s), donnant au joueur une chance de réagir dès la
première rencontre, sans dépendre uniquement de la mémorisation. La
mémorisation reste utile (optimiser sa réaction), mais n'est jamais
obligatoire pour survivre.

**Implémentation UE5** : `Behavior Tree` par archétype d'ennemi avec un
nœud `Telegraph` dédié (joue anim + Niagara + son avant toute décision
d'attaque), déplacements pilotés par des courbes (`UCurveVector`) plutôt
que du pathfinding classique — plus proche du "shmup" que d'une IA de jeu
d'action.

---

## Fiche 4 — Checkpoints rares + vies limitées

**Mécanique originale** : peu de checkpoints, mort = perte de progression
significative.

**Pourquoi elle fonctionne** : crée une tension réelle et rend la victoire
sur un niveau/boss gratifiante.

**Problème éventuel** : perçu aujourd'hui comme punitif/daté, source
d'abandon plutôt que d'engagement pour un public plus large.

**Modernisation** : séparer la tension (moment-à-moment) de la punition
(perte de progression), en donnant le choix au joueur.

**Nouvelle version** : **checkpoints denses par défaut + mode "Ember Run"
optionnel** (vies limitées, checkpoints rares, scoring/leaderboard dédié)
pour le public qui cherche la tension originale. Le mode par défaut garde
la difficulté du combat mais réduit la sanction de progression.

**Implémentation UE5** : `Game Instance Subsystem` de configuration de
difficulté choisi au lancement d'un run, qui paramètre le nombre de
checkpoints actifs dans le niveau via des `Data Table` (les checkpoints
existent tous dans le niveau, seuls certains sont "actifs" selon le mode).

---

## Fiche 5 — Boss multi-parties à point faible visuel

**Mécanique originale** : grand sprite, point faible identifiable par
l'observation, peu ou pas de barre de vie.

**Pourquoi elle fonctionne** : force l'observation et la compréhension
plutôt que le simple "tirer jusqu'à ce que ça meure" ; le mystère fait
partie du plaisir.

**Problème éventuel** : sans aucun feedback de progression, un joueur
moderne peut avoir l'impression de ne pas progresser / de ne pas savoir
s'il joue bien.

**Modernisation** : garder le mystère de la forme et du comportement, mais
ajouter un feedback de dégâts implicite (pas une barre de vie classique,
quelque chose de diégétique).

**Nouvelle version** : **boss à "corruption visible"** — le boss se
transforme visuellement (fissures, embrasement, pertes de membres/parties)
au fil des dégâts pris, sans HUD de vie explicite : la progression du
combat est lisible dans le corps même du boss. Voir détail complet dans
le futur document Level Design / Boss (section dédiée à venir).

**Implémentation UE5** : `Anim Blueprint` piloté par une variable de
"pourcentage de vie" exposée par un composant `UBossHealthComponent` en
C++, qui déclenche des transitions de matériaux (Material Parameter
Collection) et des Niagara de dégât progressif, plus des phases de combat
gérées par une State Machine (Gameplay Ability System si la complexité des
attaques le justifie — à valider une fois le boss conçu).

---

## Fiche 6 — Rythme traversée / confrontation

**Mécanique originale** : alternance de phases calmes (ambiance, tension)
et de phases denses (combat).

**Pourquoi elle fonctionne** : évite la fatigue d'un tir continu, laisse
respirer l'ambiance sonore/visuelle qui est une des forces du genre.

**Problème éventuel** : aucun — c'est une mécanique intemporelle, pas datée.
Le risque est de la perdre en voulant "moderniser" à tout prix (rythme trop
dense, trop de bruit visuel).

**Modernisation** : aucune modernisation nécessaire sur le principe —
seulement une exécution technique plus riche (son spatialisé, éclairage
dynamique, densité de particules) pour renforcer ce que l'original faisait
déjà bien avec des moyens limités.

**Nouvelle version** : conservée telle quelle comme pilier de direction
artistique et de level design.

**Implémentation UE5** : structuration des niveaux en séquences
`Level Sequence`/`Data Table` alternant zones "Ambiance" (peu d'ennemis,
MetaSounds ambiants, éclairage dynamique fort) et zones "Confrontation"
(vagues scriptées, musique adaptative qui monte en intensité via
MetaSounds paramétrés par un état de jeu).

---

➡️ Suite : [`../01-concepts/concepts-originaux.md`](../01-concepts/concepts-originaux.md)
