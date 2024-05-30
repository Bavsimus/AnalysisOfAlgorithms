#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x, y;
} Point;

int findSide(Point p1, Point p2, Point p) {
    int val = (p.y - p1.y) * (p2.x - p1.x) - (p2.y - p1.y) * (p.x - p1.x);
    if (val > 0) return 1;
    if (val < 0) return -1;
    return 0;
}

int lineDist(Point p1, Point p2, Point p) {
    return abs((p.y - p1.y) * (p2.x - p1.x) - (p2.y - p1.y) * (p.x - p1.x));
}

void quickHull(Point points[], int n, Point p1, Point p2, int side, Point hull[], int *hullSize) {
    int ind = -1;
    int maxDist = 0;

    for (int i = 0; i < n; i++) {
        int tempDist = lineDist(p1, p2, points[i]);
        if (findSide(p1, p2, points[i]) == side && tempDist > maxDist) {
            ind = i;
            maxDist = tempDist;
        }
    }
    if (ind == -1) {
        hull[*hullSize] = p1;
        (*hullSize)++;
        hull[*hullSize] = p2;
        (*hullSize)++;
        return;
    }

    quickHull(points, n, points[ind], p1, -findSide(points[ind], p1, p2), hull, hullSize);
    quickHull(points, n, points[ind], p2, -findSide(points[ind], p2, p1), hull, hullSize);
}

void findConvexHull(Point points[], int n, Point hull[], int *hullSize) {
    int minX = 0, maxX = 0;
    for (int i = 1; i < n; i++) {
        if (points[i].x < points[minX].x) minX = i;
        if (points[i].x > points[maxX].x) maxX = i;
    }

    quickHull(points, n, points[minX], points[maxX], 1, hull, hullSize);
    quickHull(points, n, points[minX], points[maxX], -1, hull, hullSize);
}

void printHull(Point hull[], int hullSize) {
    printf("The points in the convex hull are:\n");
    for (int i = 0; i < hullSize; i++) {
        printf("(%d, %d)\n", hull[i].x, hull[i].y);
    }
}

int main() {
    Point points[] = {{0, 3}, {2, 3}, {1, 1}, {2, 1}, {3, 0}, {0, 0}, {3, 3}};
    int n = sizeof(points) / sizeof(points[0]);

    Point hull[100];
    int hullSize = 0;

    findConvexHull(points, n, hull, &hullSize);
    printHull(hull, hullSize);

    return 0;
}

