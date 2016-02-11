//
// Created by kazem on 09/02/16.
//

#ifndef DSLPROJECT_SCHEDULE_H
#define DSLPROJECT_SCHEDULE_H

enum MaType{
    DIA,
    ELL,
    CSR,
    COO,
    Dense
};

class Schedule {

public:
    Schedule();
    MaType MType;

};


#endif //DSLPROJECT_SCHEDULE_H
