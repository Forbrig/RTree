#include <iostream>
#include <vector>
#include <string>
#include <fstream>

#include "../RTree.h"

using namespace std;

typedef int ValueType;
typedef long long CoordType;

struct Rect {
    Rect()  {}

    Rect (CoordType a_minX, CoordType a_minY, CoordType a_minZ, CoordType a_maxX, CoordType a_maxY, CoordType a_maxZ) {
        min[0] = a_minX;
        min[1] = a_minY;
        min[2] = a_minZ;

        max[0] = a_maxX;
        max[1] = a_maxY;
        max[2] = a_maxZ;
    }

    CoordType min[3];
    CoordType max[3];
};

bool MySearchCallback(ValueType id) {
    cout << "Hit data rect " << id << "\n";
    return true; // keep going
}

int main (int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Usage: " << argv[0] << " inFile\n";
        return -1;
    }

    //read file
    typedef std::vector< Rect > RectVector;
    RectVector rectVector;
    
    {
        ifstream inFile(argv[1]);
        while (!inFile.eof()) {
            // security and robustness be damned
            CoordType xmin, ymin, zmin, xmax, ymax, zmax;
            // string dummy;
            inFile >> xmin >> ymin >> zmin >> xmax >> ymax >> zmax;
            // cout << xmin << " " << ymin << " " << zmin << " " << xmax << " " << ymax << " " << zmax << "\n";
            // rectVector.push_back(Rect(xmin, ymin, zmin, xmin + xmax, ymin + ymax, zmin + zmax));
            rectVector.push_back(Rect(xmin, ymin, zmin, xmax, ymax, zmax));
        }
    }

    typedef RTree<ValueType, CoordType, 3, float> MyTree;
    MyTree tree;

    unsigned int i;
    cout << "number of rectangles is " << rectVector.size() << "\n";

    for (i = 0; i < rectVector.size(); i++) {
        tree.Insert(rectVector[i].min, rectVector[i].max, i); // Note, all values including zero are fine in this version
    }

    unsigned int nhits;
    // Rect search_rect(5463, 3699, 0, 5467, 3714, 0);
    // nhits = tree.Search(search_rect.min, search_rect.max, MySearchCallback);

    // Rect search_rect2(904, 415, 0, 908, 458, 0);
    // nhits = tree.Search(search_rect2.min, search_rect2.max, MySearchCallback);

    Rect search_rect3(3465, 3332, 0, 3497, 3348, 0);
    nhits = tree.Search(search_rect3.min, search_rect3.max, MySearchCallback);

    

    return 0;
}