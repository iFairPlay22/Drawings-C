#ifndef __DRAWING__H
#define __DRAWING__H

// ########################################### //
// ################## COLOR ################## //
// ########################################### //

typedef enum
{
    BLACK,
    WHITE,
    RED,
    BLUE,
    GREEN,
    YELLOW
} Color;

// ############################################### //
// ################## RECTANGLE ################## //
// ############################################### //

// Rectangle : Shape
// Shape.type = 0
typedef struct
{
    // x, y
    int width, height;
} Rectangle;

// ############################################ //
// ################## CIRCLE ################## //
// ############################################ //

// Circle : Shape
// Shape.type = 1
typedef struct
{
    // x, y
    int radius;
} Circle;

// ############################################# //
// ################## SEGMENT ################## //
// ############################################# //

// Segment : Shape
// Shape.type = 2
typedef struct
{
    // x, y
    int x2, y2;
} Segment;

// ########################################## //
// ################## TEXT ################## //
// ########################################## //

// Text : Shape
// Shape.type = 3
typedef struct
{
    // x, y
    char *text;
} Text;

// ############################################# //
// ################## POLYGON ################## //
// ############################################# //

// PolygonNode
typedef struct
{
    int x, y;
} PolygonNode;

// Polygon :: Shape
// Shape.type = 4
typedef struct
{
    // x, y
    PolygonNode **nodes;
    int size;
} Polygon;

// ########################################### //
// ################## SHAPE ################## //
// ########################################### //

// Shape
/*		  		     	 		  	 
    Sorte d'interface représentant une forme		  		     	 		  	 
*/
typedef struct
{
    int type;
    int x, y;
    union
    {
        Rectangle *rectangle;
        Circle *circle;
        Segment *segment;
        Text *text;
        Polygon *polygon;
    };
    Color color;
} Shape;

// ############################################# //
// ################## DRAWING ################## //
// ############################################# //

// PolygonManager
typedef struct
{
    Polygon *currentPolygon;
    Shape *lastPolygonShape;
    int ignore;
} PolygonManager;

// Drawing
/*		  		     	 		  	 
    Conteneur de Shapes		  		     	 		  	 
*/
typedef struct
{
    Shape **shapes;
    int size;
    int offsetX, offsetY;
    Color color;
    PolygonManager *polygonManager;
} Drawing;

// ############################################### //
// ################## FUNCTIONS ################## //
// ############################################### //

/*		  		     	 		  	 
    Crée un nouveau Drawing, alloué dynamiquement.		  		     	 		  	 
*/
Drawing *createDrawing();

/*		  		     	 		  	 
    Change la couleur à dessiner.		  		     	 		  	 
*/
void setColor(Drawing *d, Color c);

/*		  		     	 		  	 
    Libère l'instance de Drawing, et met le pointeur à NULL		  		     	 		  	 
*/
void freeDrawing(Drawing **d);

/*		  		     	 		  	 
    Affiche le contenu du Drawing,		  		     	 		  	 
    ou chaque ligne est (pour le moment) au format		  		     	 		  	 
    "<id> : Rectangle at (<x>,<y>) size <width> x <height>"		  		     	 		  	 
*/
void displayDrawing(Drawing *d);

/*		  		     	 		  	 
    Affiche un Polygon en format SVG		  		     	 		  	 
*/
void displayDrawingAsSvg(Drawing *drawing);

/*		  		     	 		  	 
    Ajoute un rectangle au Drawing,		  		     	 		  	 
    dont les coordonnées du coin haut gauche sont (x,y),		  		     	 		  	 
    et dont les dimensions sont width x height		  		     	 		  	 
*/
void addRectangle(Drawing *d, int x, int y, int width, int height);

/*		  		     	 		  	 
    Ajoute un cercle au Drawing,		  		     	 		  	 
    dont les coordonnées du centre sont (x,y),		  		     	 		  	 
    et dont le rayon est radius		  		     	 		  	 
*/
void addCircle(Drawing *d, int x, int y, int radius);

/*		  		     	 		  	 
    Ajoute un segment au Drawing,		  		     	 		  	 
    allant de (x1,y1), à (x2, y2)		  		     	 		  	 
*/
void addSegment(Drawing *d, int x1, int y1, int x2, int y2);

/*		  		     	 		  	 
    Ajoute un texte au Drawing,		  		     	 		  	 
    commençant aux coordonnées (x,y),		  		     	 		  	 
    et dont le contenu est text		  		     	 		  	 
*/
void addText(Drawing *d, int x, int y, char *text);

/*		  		     	 		  	 
    Pour ajouter un polygone, il faut donc le commencer, puis ajouter des points.		  		     	 		  	 
*/
void startPolygon(Drawing *d);

/*		  		     	 		  	 
    On ajoute une forme. Si on ajoute des points alors qu'un polygone n'est pas commencé,		  		     	 		  	 
    la fonction addPoint ne fera rien, mais on affichera "Error : no polygon started"		  		     	 		  	 
    Une fois terminé, si le polygone a moins de deux points, il est supprimé.		  		     	 		  	 
    Si il en a exactement deux, il est converti en segment.		  		     	 		  	 
    Sinon, il est affiché comme polygone.		  		     	 		  	 
*/
void addPoint(Drawing *d, int x, int y);

/*		  		     	 		  	 
    Supprime l'élément d'indice i de votre dessin		  		     	 		  	 
*/
void removeElement(Drawing *d, int i);

/*
    Sauvegarde le fichier sous forme binaire
*/
void writeDrawing(Drawing *d, char *filename);

/*
    Lit le fichier sous forme binaire et le renvoie
*/
Drawing *readDrawing(char *filename);

/*		  		     	 		  	 
    Décale toutes les formes de votre dessin de dx et dy.		  		     	 		  	 
*/
void translateDrawing(Drawing *d, int dx, int dy);

#endif