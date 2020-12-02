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

int main(int argc, char const *argv[])
{
    initStderr();

    // INIT
    Drawing *drawing = createDrawing();

    // AJOUTER LES ELEMENTS
    addText(drawing, 70, 20, "Hello !");

    addRectangle(drawing, 20, 25, 10, 5);

    setColor(drawing, BLUE);
    addCircle(drawing, 50, 75, 10);

    addSegment(drawing, 10, 15, 20, 35);
    addSegment(drawing, 50, 53, 5, 8);

    setColor(drawing, RED);
    startPolygon(drawing);
    addPoint(drawing, 10, 50);
    addPoint(drawing, 20, 30);
    addPoint(drawing, 25, 35);

    // PRINT
    // displayDrawing(drawing);

    // SVG
    displayDrawingAsSvg(drawing);

    // WRITE FILE
    writeDrawing(drawing, "drawing.bin");

    // FREE
    freeDrawing(&drawing);

    resetStderr();

    return 0;
}
