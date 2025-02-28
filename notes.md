# TASK 0

## A. Execution

**Recherchez la fonction responsable de gérer les inputs du programme**

```
void TowerSimulation::create_keystrokes() const
```

Cette fonction est responsable de la gestion des inputs du programme.

**Sur quelle touche faut-il appuyer pour ajouter un avion ?**

Il faut appuyé sur la touche 'c'

**Comment faire pour quitter le programme ?**

on peut appuyé sur la touche 'q' ou 'x'

**A quoi sert la touche 'F' ?**

'f' permet de mettre la fenêtre en plein écran

**Quel est le comportement de l'avion ?**

L'avion tourne autour de l'aéroport lorsque qu'il a fini de déposer les passagers
à l'aéroport.

**Quelles informations s'affichent dans la console ?**

Voici un exemple de ce qui est affiché dans la console:
```
LH6604 is now landing...
now servicing LH6604...
done servicing LH6604
LH6604 lift off
```
Ça nous indique les actions de l'avion dans l'aéroport

**Ajoutez maintenant quatre avions d'un coup dans la simulation. Que fait chacun des avions ?**

Les avions attendent qu'il y ait de la place dans l'aéroport pour pouvoir atterrir

## B. Analyse du code

### TowerSimulation

Cette classe gère la simulation du programme, par exemple elle permet de lancer la simulation,
de simuler la création des avions...

### AircraftType

Cette classe représente les différents types d'avions avec leurs propres caractéristiques.

### AirportType

Cette classe se charge de contenir les chemins qu'un avion doit suivre lorsqu'il est sur la
piste d'atterissage mais aussi lorsqu'il veut sortir du terminal.

### Config

Cette classe stocke les configurations par défaut du programme, notamment la taille
de l'écran, la taille d'un avion...

### Geometry

Cette classe représente tous les calculs géométriques nécessaires pour le programme.

### Runway

Cette classe représente les pistes d'atterissage, on peut le comparer à un segment.

### Waypoint

Cette classe représente les points de repères d'un avion, il peut aussi spécifier son type
c'est-à-dire si le point de repère est sur le sol ou dans les airs.

### Aircraft

Cette classe représente les avions et permet d'effectuer des manoeuvres correspondant à
un avion, tel que changer de directions, signaler son arrivé à l'aéroport.

```
const std::string& get_flight_num() const;
```
Cette fonction permet de renvoyer l'identifiant de l'avion.

```
float distance_to(const Point3D& p) const;
```
Cette fonction renvoie la distance séparant l'avion et le point entré en paramètre.

```
void display() const override;
```
Cette fonction permet d'afficher l'avion sur la fenêtre.

```
void move() override;
```
Cette fonction s'occupe du déplacement de l'avion vers le prochain point.

### Tower

Cette classe représente une tour de contrôle, elle permet de diriger les avions.

```
WaypointQueue get_instructions(Aircraft& aircraft);
```
Cette fonction s'occupe d'acquérir de nouveaux points de coordonnées.

```
void arrived_at_terminal(const Aircraft& aircraft);
```
Cette fonction indique si un avion est arrivé à un terminal.

### Airport

Cette classe représente un aéroport, elle indique les points d'arrivée d'un
avion mais aussi les terminaux qu'ils auraient accès.

```
Tower& get_tower();
```
Cette fonction renvoie la tour de contrôle de l'aéroport.

```
void display() const override;
```
Cette fonction s'occupe de dessiner l'aéroport dans la fenêtre.

```
void move() override;
```
Cette fonction s'occupe de faire avancer l'état des services au sein des
terminaux. C'est-à-dire, on fait défiler les étapes de l'embarquation vers le
décollage de l'avion.

### Terminal

Cette classe représente les terminaux, elle va permettre d'accueillir les
passagers d'un avion et est capable d'indiquer son état.

```
bool in_use() const;
```
Indique si un avion occupe le terminal.

```
bool is_servicing() const;
```
Indique si le terminal est en service, donc si un avion est en train de délivrer les passagers.

```
void assign_craft(const Aircraft& aircraft);
```
Assigne ce terminal à un avion.

```
void start_service(const Aircraft& aircraft);
```
Commence la débarcation/embarcation des passagers dans l'avion.

```
void finish_service();
```
Termine la débarcation/embarcation des passagers dans l'avion.

```
void move() override;
```
Avance à la prochaine étape de débarcation/embarcation des passagers dans l'avion.

**Réalisez ensuite un schéma présentant comment ces différentes classes
intéragissent ensemble.**

voir TASK_0_B_1.png

**Quelles classes et fonctions sont impliquées dans la génération du chemin
d'un avion ?**

La classe **tower** se charge de générer des waypoint pour l'avion avec la
fonction `get_instructions(Aircraft& aircraft)`.

**Quel conteneur de la librairie standard a été choisi pour représenter le 
chemin ? Expliquez les intérêts de ce choix.**

Le conteneur utilisé est un **Deque** car on voudrait faire en sorte que l'avion
suive un chemin circulaire
lorsqu'il est en attente d'un terminal libre.
Cela permet donc d'avoir un chemin continu à l'infini sans faire quoique ce soit.

## C. Bidouillons

**Déterminez à quel endroit du code sont définies les vitesses maximales et
accélération de chaque avion.**

Dans le fichier **aircraft_type.hpp**, on définit la vitesse et
l'accélération de chaque avion.

**Le Concorde est censé pouvoir voler plus vite que les autres avions.
Modifiez le programme pour tenir compte de cela.**

```
inline void init_aircraft_types()
{
    aircraft_types[0] = new AircraftType { .02f, .05f, .02f, MediaPath { "l1011_48px.png" } };
    aircraft_types[1] = new AircraftType { .02f, .05f, .02f, MediaPath { "b707_jat.png" } };
    aircraft_types[2] = new AircraftType { .05f, .10f, .05f, MediaPath { "concorde_af.png" } };
}
```

**Identifiez quelle variable contrôle le framerate de la simulation.**

La variable qui contrôle le framerate de la simulation est la variable
**ticks_per_sec**
```
namespace GL {

inline unsigned int ticks_per_sec = DEFAULT_TICKS_PER_SEC;
    ...
}
```

**Ajoutez deux nouveaux inputs au programme permettant d'augmenter ou de
diminuer cette valeur.**

```
void change_framerate(const int value);

```
Cette fonction permet de permet de changer le framerate selon la valeur
spécifiée. elle peut être négative ou positive.

```
void TowerSimulation::create_keystrokes() const
{
    ...
    GL::keystrokes.emplace('m', []() { GL::change_framerate(-1); });
    GL::keystrokes.emplace('p', []() { GL::change_framerate(1); });
}
```
Voilà ce que l'on doit également ajouter dans le fichier `tower_sim.cpp` pour
attribuer une action à une touche du clavier.

**Essayez maintenant de mettre en pause le programme en manipulant ce framerate.
Que se passe-t-il ?**

Lorsque le framerate atteint 0, cela provoque un **Floating point exception**.

**Ajoutez une nouvelle fonctionnalité au programme pour mettre le programme en
pause, et qui ne passe pas par le framerate.**

```
void timer(const int step)
{
    if (!paused)
    {
        for (auto& item : move_queue)
        {
            item->move();
        }
    }
    glutPostRedisplay();
    glutTimerFunc(1000u / ticks_per_sec, timer, step + 1);
}
```
Il suffit d'ajouter une variable qui indique l'état du programme, en l'occurence
la variable **paused**. Il faut également bloquer les calculs à l'aide de cette
variable. Le bout de code ci-dessus indique la zone concernée.

**Identifiez quelle variable contrôle le temps de débarquement des avions et
doublez-le.**

```
void move() override
{
    if (in_use() && is_servicing())
    {
        // ++service_progress;
        service_progress += 2;
    }
}
```

**Pourquoi n'est-il pas spécialement pertinent d'en faire de même pour
DynamicObject ?**

Concernant l'ajout automatique de l'aircraft dans un **move_queue**, il n'est
pas nécessaire de le faire car il est plus cohérent d'indiquer au développeur
qu'on ajoute l'aircraft dans une liste, plutôt que de le faire implicitement.

De même pour la desctruction, on veut que le développeur ne soit pas trop perdu
lorsque l'on supprime un élément de la **move_queue**.

## D. Theorie

**Comment a-t-on fait pour que seule la classe Tower puisse réserver un terminal
de l'aéroport ?**

On a fait en sorte que ce soit la seule classe qui puisse fournir les instructions
aux avions, et donc d'attribuer les terminaux aux avions.

**Pourquoi selon-vous ne sommes-nous pas passer par une réference ?**

On n'est pas passé par référence car il est très peu probable pour un avion d'avoir
les mêmes waypoint qu'un autre avoi

**Pensez-vous qu'il soit possible d'éviter la copie du Point3D passé en paramètre ?**


# TASK 1

## Exercice A

**Créer une nouvelle classe AircraftManager**

Cela va permettre de rendre le code plus organisé car on essaye de respecter le
principe du **une classe, une responsabilité**.
Cela permet de rendre plus *sécurisé* car on sera obliger de passer par cette
classe pour pouvoir créer ou supprimer des aircrafts.

**Donner ce rôle à une classe existante**

Cela va permettre de rendre le code plus *intuitif*, par exemple déléguer la
création des aircrafts aux airports, ce qui semble logique et permet au
développeur de s'y retrouver.
Néanmoins, cela complexifie la tâche de la classe en question car on lui rajoute
une responsabilité / tâche supplémentaire.

## Exercice B

**Qui est responsable de détruire les avions du programme ?**

**opengl_interface** est responsable de la suppression des avions du programme
car la fonction `timer()` s'occupe de faire l'actualisation de l'état des
aircrafts.

**Quelles autres structures contiennent une référence sur un avion au moment où
il doit être détruit ?**

**display_queue** et **move_queue** contiennent l'aircraft doit être supprimé.

**Comment fait-on pour supprimer la référence sur un avion qui va être détruit
dans ces structures ?**

Il faut d'abord supprimer la référence de l'aircraft dans les conteneurs (avec
un erase). Puis, on peut effectuer la destruction de l'aircraft avec le mot-clef
**delete**.

On fait d'ailleurs la suppression automatique des aircrafts des conteneurs
depuis l'objet. L'aircraft accède donc directement à la liste des aircrafts.

**Pourquoi n'est-il pas très judicieux d'essayer d'appliquer la même chose pour
votre AircraftManager ?**

Il n'est pas judicieux de le faire car il faudrait que Aircraft ait accès à
AircraftManager, ce qui est contre-intuitif et incohérent car un Aircraft ne
devrait pas pouvoir avoir accès à l'objet qui le gère.

Donc, c'est bien à AircraftManager de gérer la destruction des Aircrafts.

# TASK 2

## OBJECTIVE 1

### Exercice A

```
void TowerSimulation::display_help() const
{
    ...
    for (const auto& [key, value] : GL::keystrokes)
    {
        std::cout << key << ' ';
    }
    ...
}
```

### Exercice B

1.

```
aircrafts.erase(std::remove_if(aircrafts.begin(),
                              aircrafts.end(),
                              [](std::unique_ptr<Aircraft>& aircraft){return aircraft->move()),
                              aircrafts.end());
```

2.

C'est au **AircraftManager** de compter le nombre de aircrafts, car c'est lui
qui a la responsabilité de gérer les aircrafts.
On aurait également pu faire en sorte de rajouter ce compteur dans
**AircraftFactory** car elle s'occupe de la création des aircrafts.

### Exercice C

voir *src/geometry.hpp*
Commit 549faf555dd964db03d633136e648f6440fc3921

## OBJECTIVE 2

### Exercice A

` int fuel = 150 + rand() % (2850);`

### Exercice B

1. voir commit 0ed01c58979e4307e788734cfeb0e424deafa72b
2. voir commit 8348b77a381c37b2168038a198026af2bdd54096 
3. voir commit 46f74ae0abd084882a006081c440a489e7efe4ca 
4. voir commit d2087c3c21a32675ddd2e68bbeb8e94f55c5d41a 

### Exercice D

1.

```
bool Aircraft::is_low_on_fuel() const
{
    return fuel < 200;
}
```


# TASK 4

## Objective 1

**Que devez-vous changer dans l'appel de la fonction pour que le programme 
compile ?**

Il faut rajouter le mot-clef *constexpr* devant `auto front = false;`.

## Objective 2

**Que se passe-t-il ?**

Une erreur se produit lorsque l'on essaye d'instancier un Point2D avec 3
argument.

> error: too many initializers for ‘std::array<float, 2>

**Comment pourriez-vous expliquer que cette erreur ne se produise que
maintenant ?**

Il y a une erreur car il y a trop de valeurs d'initialisation contrairement à la
taille du tableau.

**Que se passe-t-il maintenant si vous essayez d'instancier un Point3D avec 2
arguments ?**

Aucune erreur ne se produit.
