#include "proj.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SQUARES 20
#define MAX_POLYGON_NODES 20

// ########################################### //
// ################## SHAPE ################## //
// ########################################### //

void freeMalformedPolygon(Drawing *drawing);
void displayColorAsSvg(Color color);

/*
    Crée une shape
*/
Shape *createShape(Color color, int x, int y)
{
    Shape *shape = (Shape *)malloc(sizeof(Shape));
    shape->color = color;
    shape->x = x;
    shape->y = y;
    return shape;
}

/*
    Ecrire une shape dans un fichier binaire
*/
void writeShape(Shape *shape, FILE *f)
{
    fwrite(&(shape->type), sizeof(int), 1, f);
    fwrite(&(shape->color), sizeof(int), 1, f);
    fwrite(&(shape->x), sizeof(int), 1, f);
    fwrite(&(shape->y), sizeof(int), 1, f);
}

/*
    Lit une shape depuis un fichier binaire
*/
Shape *readShape(FILE *f)
{
    int type, x, y, color;

    fread(&type, sizeof(int), 1, f);
    fread(&color, sizeof(int), 1, f);
    fread(&x, sizeof(int), 1, f);
    fread(&y, sizeof(int), 1, f);

    Shape *shape = createShape(color, x, y);
    shape->type = type;

    return shape;
}

/*		  		     	 		  	 
    Ajoute une Shape (forme non initialisée) dans un Drawing		  		     	 		  	 
*/
Shape *addEmptyShape(Drawing *drawing, int x, int y)
{

    if (drawing == NULL)
        return NULL;

    if (!drawing->polygonManager->ignore)
        freeMalformedPolygon(drawing);

    if (drawing->size == MAX_SQUARES)
    {
        printf("MAX_SQUARES reached...\n");
        return NULL;
    }

    // Add Shape
    Shape *shape = createShape(drawing->color, x, y);
    drawing->shapes[drawing->size] = shape;
    drawing->size++;

    return shape;
}

// ############################################### //
// ################## RECTANGLE ################## //
// ############################################### //

/*		  		     	 		  	 
    Crée un Rectangle dont les coordonnées du coin haut gauche		  		     	 		  	 
    sont (x,y), et dont les dimensions sont width x height		  		     	 		  	 
*/
Rectangle *createRectangle(int width, int height)
{
    Rectangle *rect = (Rectangle *)malloc(sizeof(Rectangle));

    rect->width = width;
    rect->height = height;

    return rect;
}

/*		  		     	 		  	 
    Ajoute un rectangle au Drawing,		  		     	 		  	 
    dont les coordonnées du coin haut gauche sont (x,y),		  		     	 		  	 
    et dont les dimensions sont width x height		  		     	 		  	 
*/
void addRectangle(Drawing *drawing, int x, int y, int width, int height)
{
    Shape *shape = addEmptyShape(drawing, x, y);

    if (shape == NULL)
        return;

    shape->rectangle = createRectangle(width, height);
    shape->type = 0;
}

/*		  		     	 		  	 
    Affiche un Rectangle		  		     	 		  	 
*/
void displayRectangle(Drawing *drawing, Shape shape)
{
    Rectangle rect = *(shape.rectangle);
    printf(
        "Rectangle at (%d,%d) size %d x %d\n",
        shape.x + drawing->offsetX, shape.y + drawing->offsetY,
        rect.width, rect.height);
}

/*		  		     	 		  	 
    Affiche un Rectangle en format SVG		  		     	 		  	 
*/
void displayRectangleAsSvg(Drawing *drawing, Shape shape)
{
    Rectangle rect = *(shape.rectangle);

    printf(
        "<rect x=\"%d\" y=\"%d\" width=\"%d\" height=\"%d\" ",
        shape.x + drawing->offsetX, shape.y + drawing->offsetY,
        rect.width, rect.height);
    displayColorAsSvg(shape.color);
    printf("/>\n");
}

/*
    Lit un Rectangle depuis un fichier binaire
*/
void writeRectangle(Shape *shape, FILE *f)
{
    fwrite(&(shape->rectangle->width), sizeof(int), 1, f);
    fwrite(&(shape->rectangle->height), sizeof(int), 1, f);
}

/*
    Sauvegarde un Rectangle sous forme binaire
*/
void readRectangle(Shape *shape, FILE *f)
{
    int width, height;

    fread(&width, sizeof(int), 1, f);
    fread(&height, sizeof(int), 1, f);

    shape->rectangle = createRectangle(width, height);
}

/*		  		     	 		  	 
    Libère en mémoire le contenu d'un Rectangle		  		     	 		  	 
*/
void freeRectangle(Shape shape)
{
    free(shape.rectangle);
}

// ############################################ //
// ################## CIRCLE ################## //
// ############################################ //

/*		  		     	 		  	 
    Crée un Circle,		  		     	 		  	 
    dont les coordonnées du centre sont (x,y),		  		     	 		  	 
    et dont le rayon est radius		  		     	 		  	 
*/
Circle *createCircle(int radius)
{

    Circle *circle = (Circle *)malloc(sizeof(Circle));

    circle->radius = radius;

    return circle;
}

/*		  		     	 		  	 
    Ajoute un cercle au Drawing,		  		     	 		  	 
    dont les coordonnées du centre sont (x,y),		  		     	 		  	 
    et dont le rayon est radius		  		     	 		  	 
*/
void addCircle(Drawing *drawing, int x, int y, int radius)
{
    Shape *shape = addEmptyShape(drawing, x, y);

    if (shape == NULL)
        return;

    shape->circle = createCircle(radius);
    shape->type = 1;
}

/*		  		     	 		  	 
    Affiche un Circle		  		     	 		  	 
*/
void displayCircle(Drawing *drawing, Shape shape)
{
    Circle circle = *(shape.circle);
    printf(
        "Circle at (%d,%d) radius %d\n",
        shape.x + drawing->offsetX, shape.y + drawing->offsetY,
        circle.radius);
}

/*		  		     	 		  	 
    Affiche un Circle en format SVG		  		     	 		  	 
*/
void displayCircleAsSvg(Drawing *drawing, Shape shape)
{
    Circle circle = *(shape.circle);
    printf(
        "<circle cx=\"%d\" cy=\"%d\" r=\"%d\" ",
        shape.x + drawing->offsetX, shape.y + drawing->offsetY,
        circle.radius);
    displayColorAsSvg(shape.color);
    printf("/>\n");
}

/*
    Sauvegarde un Circle sous forme binaire
*/
void writeCircle(Shape *shape, FILE *f)
{
    fwrite(&(shape->circle->radius), sizeof(int), 1, f);
}

/*
    Sauvegarde un Circle sous forme binaire
*/
void readCircle(Shape *shape, FILE *f)
{
    int radius;

    fread(&radius, sizeof(int), 1, f);

    shape->circle = createCircle(radius);
}

/*		  		     	 		  	 
    Libère en mémoire le contenu d'un Circle		  		     	 		  	 
*/
void freeCircle(Shape shape)
{
    free(shape.circle);
}

// ############################################# //
// ################## SEGMENT ################## //
// ############################################# //

/*		  		     	 		  	 
    Crée un Segment,		  		     	 		  	 
    allant de (x1,y1), à (x2, y2)		  		     	 		  	 
*/
Segment *createSegment(int x2, int y2)
{

    Segment *segment = (Segment *)malloc(sizeof(Segment));

    segment->x2 = x2;
    segment->y2 = y2;

    return segment;
}

/*		  		     	 		  	 
    Ajoute un segment au Drawing,		  		     	 		  	 
    allant de (x1,y1), à (x2, y2)		  		     	 		  	 
*/
void addSegment(Drawing *drawing, int x1, int y1, int x2, int y2)
{
    Shape *shape = addEmptyShape(drawing, x1, y1);

    if (shape == NULL)
        return;

    shape->segment = createSegment(x2, y2);
    shape->type = 2;
}

/*		  		     	 		  	 
    Affiche un Segment		  		     	 		  	 
*/
void displaySegment(Drawing *drawing, Shape shape)
{
    Segment segment = *(shape.segment);
    printf(
        "Segment from (%d,%d) to (%d,%d)\n",
        shape.x + drawing->offsetX, shape.y + drawing->offsetY,
        segment.x2 + drawing->offsetX, segment.y2 + drawing->offsetY);
}

/*		  		     	 		  	 
    Affiche un Segment en format SVG		  		     	 		  	 
*/
void displaySegmentAsSvg(Drawing *drawing, Shape shape)
{
    Segment segment = *(shape.segment);
    printf(
        "<line x1=\"%d\" y1=\"%d\" x2=\"%d\" y2=\"%d\" ",
        shape.x + drawing->offsetX, shape.y + drawing->offsetY,
        segment.x2 + drawing->offsetX, segment.y2 + drawing->offsetY);
    displayColorAsSvg(shape.color);
    printf("/>\n");
}

/*
    Sauvegarde un Segment sous forme binaire
*/
void writeSegment(Shape *shape, FILE *f)
{
    fwrite(&(shape->segment->x2), sizeof(int), 1, f);
    fwrite(&(shape->segment->y2), sizeof(int), 1, f);
}

/*
    Sauvegarde un Segment sous forme binaire
*/
void readSegment(Shape *shape, FILE *f)
{
    int x1, x2;

    fread(&x1, sizeof(int), 1, f);
    fread(&x2, sizeof(int), 1, f);

    shape->segment = createSegment(x1, x2);
}

/*		  		     	 		  	 
    Libère en mémoire le contenu d'un Segment		  		     	 		  	 
*/
void freeSegment(Shape shape)
{
    free(shape.segment);
}

// ########################################## //
// ################## TEXT ################## //
// ########################################## //

/*		  		     	 		  	 
    Crée un Text,		  		     	 		  	 
    commençant aux coordonnées (x,y),		  		     	 		  	 
    et dont le contenu est text		  		     	 		  	 
*/
Text *createText(char *shapeText)
{

    Text *text = (Text *)malloc(sizeof(Text));

    int size = strlen(shapeText);
    text->text = (char *)malloc(size * sizeof(char));
    strncpy(text->text, shapeText, size);

    return text;
}

/*		  		     	 		  	 
    Ajoute un texte au Drawing,		  		     	 		  	 
    commençant aux coordonnées (x,y),		  		     	 		  	 
    et dont le contenu est text		  		     	 		  	 
*/
void addText(Drawing *drawing, int x, int y, char *text)
{
    Shape *shape = addEmptyShape(drawing, x, y);

    if (shape == NULL)
        return;

    shape->text = createText(text);
    shape->type = 3;
}

/*		  		     	 		  	 
    Affiche un Text		  		     	 		  	 
*/
void displayText(Drawing *drawing, Shape shape)
{
    Text text = *(shape.text);

    printf(
        "Text \"%s\" at (%d,%d)\n",
        text.text,
        shape.x + drawing->offsetX, shape.y + drawing->offsetY);
}

/*		  		     	 		  	 
    Affiche un Text en format SVG		  		     	 		  	 
*/
void displayTextAsSvg(Drawing *drawing, Shape shape)
{
    Text text = *(shape.text);
    printf(
        "<text x=\"%d\" y=\"%d\" ",
        shape.x + drawing->offsetX, shape.y + drawing->offsetY);
    displayColorAsSvg(shape.color);
    printf(">%s</text>\n", text.text);
}

/* 
    Sauvegarde un char* dans un fichier binaire
*/
void *writeSring(char *text, FILE *f)
{
    fwrite(text, (1 + strlen(text)) * sizeof(char), 1, f);
}

/*
    Sauvegarde un Text sous forme binaire
*/
void writeText(Shape *shape, FILE *f)
{
    writeSring(shape->text->text, f);
}

/* 
    Lit un char* dans un fichier binaire et le retourne
*/
char *readSring(FILE *f)
{
    char buffer[100];
    int N = 0;
    char c;

    do
    {
        fread(&c, sizeof(char), 1, f);
        buffer[N] = c;
        N++;
    } while (c != '\0');

    char *res = malloc(N * sizeof(char));

    for (int i = 0; i < N; i++)
        res[i] = buffer[i];

    return res;
}

/*
    Sauvegarde un Text sous forme binaire
*/
void readText(Shape *shape, FILE *f)
{
    shape->text = createText(readSring(f));
}

/*		  		     	 		  	 
    Libère en mémoire le contenu d'un Texte		  		     	 		  	 
*/
void freeText(Shape shape)
{
    free(shape.text->text);
    free(shape.text);
}

// ############################################# //
// ################## POLYGON ################## //
// ############################################# //

/*		  		     	 		  	 
    Crée un Polygon vide		  		     	 		  	 
*/
Polygon *createPolygon()
{

    Polygon *polygon = (Polygon *)malloc(sizeof(Polygon));
    polygon->nodes = (PolygonNode **)malloc(MAX_POLYGON_NODES * sizeof(PolygonNode *));
    polygon->size = 0;

    return polygon;
}

/*		  		     	 		  	 
    Pour ajouter un polygone, il faut donc le commencer, puis ajouter des points.		  		     	 		  	 
*/
void startPolygon(Drawing *drawing)
{

    if (drawing == NULL)
        return;

    // Delete malformed polygon
    freeMalformedPolygon(drawing);

    // New Polygon
    drawing->polygonManager->currentPolygon = createPolygon();
    drawing->polygonManager->lastPolygonShape = NULL;
}

/*		  		     	 		  	 
    Crée un PolygonNode,		  		     	 		  	 
    dont les coordonnées sont (x,y)		  		     	 		  	 
*/
PolygonNode *createPolygonNode(int x, int y)
{

    PolygonNode *polygonNode = (PolygonNode *)malloc(sizeof(PolygonNode));

    polygonNode->x = x;
    polygonNode->y = y;

    return polygonNode;
}

/*		  		     	 		  	 
    On ajoute une forme. Si on ajoute des points alors qu'un polygone n'est pas commencé,		  		     	 		  	 
    la fonction addPoint ne fera rien, mais on affichera "Error : no polygon started"		  		     	 		  	 
    Une fois terminé, si le polygone a moins de deux points, il est supprimé.		  		     	 		  	 
    Si il en a exactement deux, il est converti en segment.		  		     	 		  	 
    Sinon, il est affiché comme polygone.		  		     	 		  	 
*/
void addPoint(Drawing *drawing, int x, int y)
{

    if (drawing == NULL)
        return;

    if (drawing->polygonManager->currentPolygon == NULL)
    {
        printf("Error : no polygon started\n");
        return;
    }

    if (drawing->size == MAX_POLYGON_NODES)
    {
        printf("MAX_POLYGON_NODES reached...\n");
        return;
    }

    PolygonManager *polygonManager = drawing->polygonManager;

    // Add PolygonNode
    Polygon *polygon = polygonManager->currentPolygon;
    polygon->nodes[polygon->size] = createPolygonNode(x, y);
    polygon->size++;

    if (polygon->size == 2)
    {
        // Convert as Segment and add it into the Drawing
        drawing->polygonManager->ignore = 1;
        addSegment(
            drawing,
            polygon->nodes[0]->x, polygon->nodes[0]->y,
            polygon->nodes[1]->x, polygon->nodes[1]->y);
        drawing->polygonManager->ignore = 0;

        // Store the created segment
        polygonManager->lastPolygonShape = drawing->shapes[drawing->size - 1];
    }
    else if (polygon->size == 3)
    {
        // Remove the created segment
        freeSegment(*(polygonManager->lastPolygonShape));

        // Add the polygone into the Drawing
        polygonManager->lastPolygonShape->polygon = polygon;
        polygonManager->lastPolygonShape->type = 4;
        polygonManager->lastPolygonShape = NULL;
    }
}

/*		  		     	 		  	 
    Affiche un Polygon		  		     	 		  	 
*/
void displayPolygon(Drawing *drawing, Shape shape)
{
    Polygon polygon = *(shape.polygon);
    printf("Polygon ");

    for (int i = 0; i < polygon.size; i++)
        printf(
            "(%d,%d) ",
            polygon.nodes[i]->x + drawing->offsetX,
            polygon.nodes[i]->y + drawing->offsetY);

    printf("\n");
}

/*		  		     	 		  	 
    Affiche un Polygon en format SVG		  		     	 		  	 
*/
void displayPolygonAsSvg(Drawing *drawing, Shape shape)
{
    Polygon polygon = *(shape.polygon);
    printf("<polygon points=\"");

    for (int i = 0; i < polygon.size; i++)
        printf("%d,%d ",
               polygon.nodes[i]->x + drawing->offsetX,
               polygon.nodes[i]->y + drawing->offsetY);

    printf("\" ");
    displayColorAsSvg(shape.color);
    printf("/>\n");
}

/*
    Sauvegarde un PolygonNode sous forme binaire
*/
void writePolygonNode(PolygonNode *polygonNode, FILE *f)
{
    fwrite(&(polygonNode->x), sizeof(int), 1, f);
    fwrite(&(polygonNode->y), sizeof(int), 1, f);
}

/*
    Sauvegarde un PolygonNode sous forme binaire
*/
PolygonNode *readPolygonNode(Shape *shape, FILE *f)
{
    int x, y;

    fread(&x, sizeof(int), 1, f);
    fread(&y, sizeof(int), 1, f);

    return createPolygonNode(x, y);
}

/*
    Sauvegarde un Polygon sous forme binaire
*/
void writePolygon(Shape *shape, FILE *f)
{
    fwrite(&(shape->polygon->size), sizeof(int), 1, f);

    for (int i = 0; i < shape->polygon->size; i++)
        writePolygonNode(shape->polygon->nodes[i], f);
}

/*
    Sauvegarde un Polygon sous forme binaire
*/
void readPolygon(Shape *shape, FILE *f)
{
    Polygon *polygon = createPolygon();

    fread(&(polygon->size), sizeof(int), 1, f);

    polygon->nodes = malloc(MAX_POLYGON_NODES * sizeof(PolygonNode));

    for (int i = 0; i < polygon->size; i++)
        polygon->nodes[i] = readPolygonNode(shape, f);

    shape->polygon = polygon;
}

/*		  		     	 		  	 
    Libère en mémoire le contenu d'un Polygon		  		     	 		  	 
*/
void freePolygon2(Polygon *polygon)
{

    for (int i = 0; i < polygon->size; i++)
        free(polygon->nodes[i]);

    free(polygon->nodes);

    free(polygon);
}

/*		  		     	 		  	 
    Libère en mémoire le contenu d'un Polygon		  		     	 		  	 
*/
void freePolygon(Shape shape)
{

    Polygon *polygon = shape.polygon;

    freePolygon2(polygon);
}

// ########################################### //
// ################## COLOR ################## //
// ########################################### //

/*		  		     	 		  	 
    Change la couleur à dessiner.		  		     	 		  	 
*/
void setColor(Drawing *drawing, Color color)
{

    if (drawing == NULL)
        return;

    drawing->color = color;
}

/*		  		     	 		  	 
    Renvoie la chaine de caractère associée à la couleur		  		     	 		  	 
    actuellement sélectionnée.		  		     	 		  	 
*/
char *getColor(Color color)
{
    switch (color)
    {
    case BLACK:
        return "Black";
    case WHITE:
        return "White";
    case RED:
        return "Red";
    case BLUE:
        return "Blue";
    case GREEN:
        return "Green";
    case YELLOW:
        return "Yellow";
    default:
        printf("Color can't be printed!");
        break;
    }
}

/*		  		     	 		  	 
    Renvoie la chaine de caractère associée à la couleur		  		     	 		  	 
    actuellement sélectionnée.		  		     	 		  	 
*/
void displayColorAsSvg(Color color)
{
    printf("fill=\"%s\"", getColor(color));
}

// ##################################################### //
// ################## POLYGON MANAGER ################## //
// ##################################################### //

/*		  		     	 		  	 
    Créée un PolygonManager vide		  		     	 		  	 
*/
PolygonManager *createPolygonManager()
{

    PolygonManager *polygonManager = (PolygonManager *)malloc(sizeof(PolygonManager));

    polygonManager->currentPolygon = NULL;
    polygonManager->lastPolygonShape = NULL;
    polygonManager->ignore = 0;

    return polygonManager;
}

/*		  		     	 		  	 
    Libère en mémoire le polygonManager->currentPolygon		  		     	 		  	 
*/
void freeMalformedPolygon(Drawing *drawing)
{

    Polygon *current = drawing->polygonManager->currentPolygon;
    if (current != NULL && current->size <= 2)
        freePolygon2(current);

    drawing->polygonManager->currentPolygon = NULL;
    drawing->polygonManager->lastPolygonShape = NULL;
}

/*		  		     	 		  	 
    Libère en mémoire un PolygonManager		  		     	 		  	 
*/
void freePolygonManager(Drawing *drawing)
{

    if (drawing == NULL)
        return;

    freeMalformedPolygon(drawing);

    free(drawing->polygonManager);
    drawing->polygonManager = NULL;
}

// ############################################# //
// ################## DRAWING ################## //
// ############################################# //

/*		  		     	 		  	 
    Crée un nouveau Drawing, alloué dynamiquement.		  		     	 		  	 
*/
Drawing *createDrawing()
{

    Drawing *drawing = (Drawing *)malloc(sizeof(Drawing));

    drawing->shapes = (Shape **)malloc(MAX_SQUARES * sizeof(Shape *));
    drawing->polygonManager = createPolygonManager();
    drawing->size = 0;
    drawing->offsetX = 0;
    drawing->offsetY = 0;
    setColor(drawing, BLACK);

    return drawing;
}

/*		  		     	 		  	 
    Libère en mémoire une forme		  		     	 		  	 
*/
void freeShape(Shape **shape)
{

    if (shape == NULL)
        return;

    if (*shape == NULL)
    {
        shape = NULL;
        return;
    }

    switch ((*shape)->type)
    {
    case 0:
        freeRectangle(**shape);
        break;
    case 1:
        freeCircle(**shape);
        break;
    case 2:
        freeSegment(**shape);
        break;
    case 3:
        freeText(**shape);
        break;
    case 4:
        freePolygon(**shape);
        break;
    default:
        printf("Shape of type %d can't be freed!", (*shape)->type);
        break;
    }

    free(*shape);
    *shape = NULL;

    shape = NULL;
}

/*		  		     	 		  	 
    Supprime l'élément d'indice i de votre dessin		  		     	 		  	 
*/
void removeElement(Drawing *drawing, int i)
{

    if (!(0 <= i && i < drawing->size))
    {
        //printf("Can't remove the element!");
        return;
    }

    freeShape(&drawing->shapes[i]);

    for (int id = i + 1; id < drawing->size; id++)
        drawing->shapes[id - 1] = drawing->shapes[id];

    drawing->size--;
}

/*		  		     	 		  	 
    Libère l'instance de Drawing, et met le pointeur à NULL		  		     	 		  	 
*/
void freeDrawing(Drawing **drawing)
{

    if (drawing == NULL)
        return;

    if (*drawing == NULL)
    {
        *drawing = NULL;
        return;
    }

    freePolygonManager(*drawing);

    for (int id = 0; id < (*drawing)->size; id++)
        freeShape(&(*drawing)->shapes[id]);

    free((*drawing)->shapes);
    free(*drawing);
    *drawing = NULL;
}

/*		  		     	 		  	 
    Affiche le contenu du Drawing,		  		     	 		  	 
    ou chaque ligne est (pour le moment) au format		  		     	 		  	 
    "<id> : Rectangle at (<x>,<y>) size <width> x <height>"		  		     	 		  	 
*/
void displayDrawing(Drawing *drawing)
{

    if (drawing == NULL)
        return;

    for (int id = 0; id < drawing->size; id++)
    {
        Shape shape = *(drawing->shapes[id]);

        printf("%d : %s ", id, getColor(shape.color));
        switch (shape.type)
        {
        case 0:
            displayRectangle(drawing, shape);
            break;
        case 1:
            displayCircle(drawing, shape);
            break;
        case 2:
            displaySegment(drawing, shape);
            break;
        case 3:
            displayText(drawing, shape);
            break;
        case 4:
            displayPolygon(drawing, shape);
            break;
        default:
            printf("Shape %d of type %d can't be displayed!", id, shape.type);
            break;
        }
    }
}

/*		  		     	 		  	 
    Affiche un Polygon en format SVG		  		     	 		  	 
*/
void displayDrawingAsSvg(Drawing *drawing)
{

    if (drawing == NULL)
        return;

    printf("<svg>\n"); // width=\"100\" height=\"100\"

    for (int id = 0; id < drawing->size; id++)
    {
        Shape shape = *(drawing->shapes[id]);
        printf("\t");

        switch (shape.type)
        {
        case 0:
            displayRectangleAsSvg(drawing, shape);
            break;
        case 1:
            displayCircleAsSvg(drawing, shape);
            break;
        case 2:
            displaySegmentAsSvg(drawing, shape);
            break;
        case 3:
            displayTextAsSvg(drawing, shape);
            break;
        case 4:
            displayPolygonAsSvg(drawing, shape);
            break;
        default:
            printf("Shape %d of type %d can't be displayed as SVG!", id, shape.type);
            break;
        }
    }

    printf("</svg>\n");
}

// ####################################################### //
// ################## FUSION DE DESSINS ################## //
// ####################################################### //

/*
    Fusionne deux dessins
*/
Drawing *mergeDrawings(Drawing *d1, Drawing *d2)
{
    if (d1 == NULL || d2 == NULL)
        return NULL;

    Drawing *drawing = createDrawing();

    for (int i = 0; i < d1->size + d2->size; i++)
    {
        Shape oldShape;
        int offsetX, offsetY;

        if (i < d1->size)
        {
            oldShape = *(d1->shapes[i]);
            offsetX = d1->offsetX;
            offsetY = d1->offsetY;
        }
        else
        {
            oldShape = *(d2->shapes[i - d1->size]);
            offsetX = d2->offsetX;
            offsetY = d2->offsetY;
        }

        int color = oldShape.color;
        int x = oldShape.x + offsetX, y = oldShape.y + offsetY;

        switch (oldShape.type)
        {
        case 0:
            addRectangle(
                drawing,
                x, y,
                oldShape.rectangle->width,
                oldShape.rectangle->height);
            break;
        case 1:
            addCircle(drawing, x, y, oldShape.circle->radius);
            break;
        case 2:
            addSegment(
                drawing, x, y,
                oldShape.segment->x2 + offsetX,
                oldShape.segment->y2 + offsetY);
            break;
        case 3:
            addText(drawing, x, y, oldShape.text->text);
            break;
        case 4:
            startPolygon(drawing);
            for (int j = 0; j < oldShape.polygon->size; j++)
                addPoint(
                    drawing,
                    oldShape.polygon->nodes[j]->x + offsetX,
                    oldShape.polygon->nodes[j]->y + offsetY);
            break;
        default:
            printf("Shape %d of type %d can't be added!", i, oldShape.type);
            break;
        }
    }

    return drawing;
}

// ################################################# //
// ################## TRANSLATION ################## //
// ################################################# //

/*		  		     	 		  	 
    Décale toutes les formes de votre dessin de dx et dy.		  		     	 		  	 
*/
void translateDrawing(Drawing *drawing, int dx, int dy)
{
    if (drawing == NULL)
        return;

    drawing->offsetX += dx;
    drawing->offsetY += dy;
}

// #################################################### //
// ################## SAVE AND STORE ################## //
// #################################################### //

/*
    Sauvegarde le fichier sous forme binaire
*/
void writeDrawing(Drawing *drawing, char *fileName)
{
    if (drawing == NULL || fileName == NULL)
        return;

    FILE *f = fopen(fileName, "wb");

    // Store the size
    fwrite(&(drawing->size), sizeof(int), 1, f);
    fwrite(&(drawing->offsetX), sizeof(int), 1, f);
    fwrite(&(drawing->offsetY), sizeof(int), 1, f);

    // Store the shapes
    for (int id = 0; id < drawing->size; id++)
    {
        Shape *shape = drawing->shapes[id];

        writeShape(shape, f);

        switch (shape->type)
        {
        case 0:
            writeRectangle(shape, f);
            break;
        case 1:
            writeCircle(shape, f);
            break;
        case 2:
            writeSegment(shape, f);
            break;
        case 3:
            writeText(shape, f);
            break;
        case 4:
            writePolygon(shape, f);
            break;
        default:
            printf("Shape %d of type %d can't be written!", id, shape->type);
            exit(1);
            break;
        }
    }

    fclose(f);
}

/*
    Lit le fichier sous forme binaire et le renvoie
*/
Drawing *readDrawing(char *filename)
{
    FILE *f = fopen(filename, "rb");

    Drawing *drawing = createDrawing();

    // Store the size
    fread(&(drawing->size), sizeof(int), 1, f);
    fread(&(drawing->offsetX), sizeof(int), 1, f);
    fread(&(drawing->offsetY), sizeof(int), 1, f);

    drawing->shapes = (Shape **)malloc(MAX_SQUARES * sizeof(Shape *));

    // Store the shapes
    for (int id = 0; id < drawing->size; id++)
    {
        Shape *shape = readShape(f);

        switch (shape->type)
        {
        case 0:
            readRectangle(shape, f);
            break;
        case 1:
            readCircle(shape, f);
            break;
        case 2:
            readSegment(shape, f);
            break;
        case 3:
            readText(shape, f);
            break;
        case 4:
            readPolygon(shape, f);
            break;
        default:
            printf("Shape %d of type %d can't be ridden!", id, shape->type);
            exit(1);
            break;
        }

        drawing->shapes[id] = shape;
    }

    fclose(f);

    return drawing;
}