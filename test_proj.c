#include <stdio.h>
#include <stdlib.h>
#include "proj.h"

Drawing *createD1()
{
    Drawing *d1 = createDrawing();

    // AJOUTER LES ELEMENTS

    setColor(d1, GREEN);
    addRectangle(d1, 250, 50, 100, 200);
    setColor(d1, BLACK);
    addCircle(d1, 250, 50, 25);
    addSegment(d1, 350, 50, 250, 250);
    setColor(d1, RED);
    startPolygon(d1);
    addPoint(d1, 350, 250);
    addPoint(d1, 450, 250);
    addPoint(d1, 400, 300);
    setColor(d1, BLUE);
    addText(d1, 400, 300, "Test !");
    exportSVG(d1, "test.svg");

    return d1;
}

Drawing *createD2()
{
    Drawing *d2 = createDrawing();

    // AJOUTER LES ELEMENTS

    addRectangle(d2, 20, 25, 10, 5);

    setColor(d2, BLUE);

    addCircle(d2, 50, 75, 10);

    addSegment(d2, 10, 15, 20, 35);
    addSegment(d2, 50, 53, 5, 8);

    addText(d2, 70, 20, "Hello !");

    addSegment(d2, 10, 15, 20, 35);
    addSegment(d2, 50, 53, 5, 8);

    return d2;
}

Drawing *createD3(int nbPolygons, int nbPolygonsNodes)
{
    Drawing *d3 = createDrawing();

    // AJOUTER LES ELEMENTS

    for (int i = 0; i < nbPolygons; i++)
    {
        startPolygon(d3);
        for (int j = 0; j < nbPolygonsNodes; j++)
        {
            addPoint(d3, i, j);
        }
    }

    return d3;
}

void displayD123(Drawing *d1, Drawing *d2, Drawing *d3)
{
    printf("\n\nD1 : \n\n");
    displayDrawing(d1);

    printf("\n\nD2 : \n\n");
    displayDrawing(d2);

    printf("\n\nD3 : \n\n");
    displayDrawing(d3);
}

void freeD123(Drawing *d1, Drawing *d2, Drawing *d3)
{
    freeDrawing(&d1);
    freeDrawing(&d2);
    freeDrawing(&d3);
}

int main(int argc, char const *argv[])
{
    Drawing *d1 = createD1();
    Drawing *d2 = createD2();
    Drawing *d3 = createD3(28, 25);

    translateDrawing(d2, 10, -10);

    displayD123(d1, d2, d3);

    // Write & Read & Print
    writeDrawing(d3, "drawing.bin");
    printf("READ\n");
    Drawing *d4 = readDrawing("drawing.bin");
    printf("\n\nD4 :\n\n");
    displayDrawing(d4);
    freeDrawing(&d4);

    // Concat & Print
    d4 = concatDrawings(d2, d3);
    exportSVG(d1, "test.svg");
    freeDrawing(&d4);

    freeD123(d1, d2, d3);

    return 0;
}
