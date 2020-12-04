#include <stdio.h>
#include <stdlib.h>
#include "proj.h"

void initStderr()
{
    fprintf(stderr, "\033[1;31m");
}

void resetStderr()
{
    fprintf(stderr, "\033[0m");
}

// fprintf(stderr, "Erreur 10 : vector_empty\n");
// exit(10);

void write()
{
    // INIT
    printf("INIT\n\n");
    Drawing *drawing = createDrawing();

    // AJOUTER LES ELEMENTS
    printf("AJOUTER LES ELEMENTS\n\n");

    addRectangle(drawing, 20, 25, 10, 5);

    setColor(drawing, BLUE);

    addCircle(drawing, 50, 75, 10);

    addSegment(drawing, 10, 15, 20, 35);
    addSegment(drawing, 50, 53, 5, 8);

    addText(drawing, 70, 20, "Hello !");

    addSegment(drawing, 10, 15, 20, 35);
    addSegment(drawing, 50, 53, 5, 8);

    setColor(drawing, RED);

    startPolygon(drawing);
    addPoint(drawing, 10, 50);
    addPoint(drawing, 20, 30);
    addPoint(drawing, 25, 35);

    addSegment(drawing, 10, 15, 20, 35);

    // PRINT
    // printf("PRINT\n\n");
    // displayDrawing(drawing);

    // SVG
    printf("SVG\n\n");
    displayDrawingAsSvg(drawing);

    // TRANSLATE
    printf("TRANSLATE\n\n");
    translateDrawing(drawing, 10, 20);

    // SVG
    printf("SVG\n\n");
    displayDrawingAsSvg(drawing);

    // WRITE FILE
    printf("WRITE FILE\n\n");
    writeDrawing(drawing, "drawing.bin");

    // FREE
    printf("FREE\n\n");
    freeDrawing(&drawing);
}

void read()
{
    // READ FILE
    printf("READ FILE\n\n");
    Drawing *drawing = readDrawing("drawing.bin");

    // SVG
    printf("SVG\n\n");
    displayDrawingAsSvg(drawing);

    // FREE
    printf("FREE\n\n");
    freeDrawing(&drawing);
}

void merge()
{
    // INIT
    printf("INIT\n\n");
    Drawing *d1 = createDrawing();

    // AJOUTER LES ELEMENTS
    printf("AJOUTER LES ELEMENTS\n\n");

    addRectangle(d1, 20, 25, 10, 5);

    setColor(d1, BLUE);

    addCircle(d1, 50, 75, 10);

    addSegment(d1, 10, 15, 20, 35);
    addSegment(d1, 50, 53, 5, 8);

    addText(d1, 70, 20, "Hello !");

    addSegment(d1, 10, 15, 20, 35);
    addSegment(d1, 50, 53, 5, 8);

    setColor(d1, RED);

    startPolygon(d1);
    addPoint(d1, 10, 50);
    addPoint(d1, 20, 30);
    addPoint(d1, 25, 35);

    addSegment(d1, 10, 15, 20, 35);

    // PRINT
    // printf("PRINT\n\n");
    // displayDrawing(drawing);

    // INIT
    printf("INIT\n\n");
    Drawing *d2 = createDrawing();

    // AJOUTER LES ELEMENTS
    printf("AJOUTER LES ELEMENTS\n\n");

    addRectangle(d2, 20, 25, 10, 5);

    setColor(d2, BLUE);

    addCircle(d2, 50, 75, 10);

    addSegment(d2, 10, 15, 20, 35);
    addSegment(d2, 50, 53, 5, 8);

    addText(d2, 70, 20, "Hello !");

    addSegment(d2, 10, 15, 20, 35);
    addSegment(d2, 50, 53, 5, 8);

    // TRANSLATE
    printf("TRANSLATE\n\n");
    translateDrawing(d2, 10, -10);

    // PRINT
    // printf("PRINT\n\n");
    // displayDrawing(drawing);

    // SVG
    printf("SVG\n\n");
    displayDrawingAsSvg(d1);

    // SVG
    printf("SVG\n\n");
    displayDrawingAsSvg(d2);

    // MERGE
    printf("MERGE\n\n");
    Drawing *d3 = mergeDrawings(d1, d2);

    // SVG
    printf("SVG\n\n");
    displayDrawingAsSvg(d3);

    //FREE
    printf("FREE\n\n");
    freeDrawing(&d1);
    freeDrawing(&d2);
    freeDrawing(&d3);
}

int main(int argc, char const *argv[])
{
    initStderr();

    // write();
    // read();
    merge();

    resetStderr();

    return 0;
}
