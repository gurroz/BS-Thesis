

#include "movimientosAUV.h"

MovimientosAUV::MovimientosAUV(){}

Punto *MovimientosAUV::getMovimiento(int number_nodo, int indice_unit){
    int nodo = number_nodo;

    switch(indice_unit){
    case 0:
        if(nodo == 6) return new Punto(0.000000,0.086957,0.02173);
        if(nodo == 32) return new Punto(0.000000, 0.065217, 0.02173);
        if(nodo == 57) return new Punto(0.000000, 0.065217, 0.02173);
        if(nodo == 70) return new Punto(0.000000, 0.050000, 0.02173);
        if(nodo == 71) return new Punto(0.000000, 0.050000, 0.02173);
        if(nodo == 72) return new Punto(0.000000, 0.050000, 0.02173);
        if(nodo == 73) return new Punto(0.000000, 0.050000, 0.02173);
        if(nodo == 78) return new Punto(0.000000, 0.065217, 0.02173);
        if(nodo == 79) return new Punto(0.000000, 0.020000, 0.00000);
        if(nodo == 80) return new Punto(0.000000, 0.020000, 0.00000);
        break;
    case 1:
        if(nodo == 30) return new Punto(0.090000, 0.000000, -0.09000);
        if(nodo == 7) return new Punto(0.000000, 0.032500, -0.01739);
        if(nodo == 32) return new Punto(0.000000, -0.022000, -0.02550);
        if(nodo == 6) return new Punto(0.000000, -0.022000, -0.01000);
        if(nodo == 55) return new Punto(-0.090000, 0.000000, -0.09000);
        if(nodo == 57) return new Punto(0.000000, -0.022000, -0.02550);
        if(nodo == 70) return new Punto(0.045000, -0.020000, -0.02000);
        if(nodo == 71) return new Punto(-0.045000, -0.020000, -0.02000);
        if(nodo == 72) return new Punto(0.040000, 0.000000, -0.02000);
        if(nodo == 73) return new Punto(-0.040000, 0.000000, -0.02000);
        if(nodo == 74) return new Punto(0.040000, 0.000000, -0.02000);
        if(nodo == 75) return new Punto(-0.040000, 0.000000, -0.02000);
        if(nodo == 76) return new Punto(0.045000, 0.023000, -0.02000);
        if(nodo == 77) return new Punto(-0.045000, 0.023000, -0.02000);
        if(nodo == 79) return new Punto(0.080000, 0.000000, -0.08000);
        if(nodo == 80) return new Punto(-0.080000, 0.000000, -0.08000);
        if(nodo == 81) return new Punto(0.040000, 0.000000, -0.04000);
        if(nodo == 82) return new Punto(-0.040000, 0.000000, -0.04000);
        break;
    case 2:
        if(nodo == 16) return new Punto(-0.130435, -0.130435, 0.00000);
        if(nodo == 15) return new Punto(-0.086957, -0.130435, 0.01739);
        if(nodo == 17) return new Punto(-0.086957, -0.130435, 0.01739);
        if(nodo == 14) return new Punto(0.000000, -0.065217, 0.00000);
        if(nodo == 41) return new Punto(0.130435, -0.130435, 0.00000);
        if(nodo == 40) return new Punto(0.086957, -0.130435, 0.01739);
        if(nodo == 42) return new Punto(0.086957, -0.130435, 0.01739);
        if(nodo == 39) return new Punto(0.000000, -0.065217, 0.00000);
        if(nodo == 20) return new Punto(0.000000, -0.034783, 0.00000);
        if(nodo == 45) return new Punto(0.000000, -0.034783, 0.00000);
        if(nodo == 58) return new Punto(0.000000, -0.026087, 0.00000);
        if(nodo == 60) return new Punto(0.000000, -0.026087, 0.00000);
        if(nodo == 62) return new Punto(0.000000, -0.026087, 0.00000);
        if(nodo == 64) return new Punto(0.000000, -0.026087, 0.00000);
        break;
    case 3:
        if(nodo == 14) return new Punto(0.021739, 0.173913, -0.02173);
        if(nodo == 15) return new Punto(0.000000, 0.152174, -0.02173);
        if(nodo == 16) return new Punto(0.000000, 0.021739, 0.00000);
        if(nodo == 17) return new Punto(0.000000, 0.152174, -0.02173);
        if(nodo == 39) return new Punto(-0.021739, 0.173913, -0.02173);
        if(nodo == 40) return new Punto(0.000000, 0.152174, -0.02173);
        if(nodo == 41) return new Punto(0.000000, 0.021739, 0.00000);
        if(nodo == 42) return new Punto(0.000000, 0.152174, -0.02173);
        break;
    case 4:
        if(nodo == 20) return new Punto(0.000000, -0.062000, 0.01000);
        if(nodo == 21) return new Punto(0.000000, 0.020000, 0.01000);
        if(nodo == 45) return new Punto(0.000000, -0.062000, 0.01000);
        if(nodo == 46) return new Punto(0.000000, 0.020000, 0.01000);
        if(nodo == 88) return new Punto(0.000000, -0.045000, 0.00700);
        if(nodo == 89) return new Punto(0.000000, -0.045000, 0.00700);
        if(nodo == 90) return new Punto(0.000000, 0.015000, 0.00700);
        if(nodo == 91) return new Punto(0.000000, 0.015000, 0.00700);
        if(nodo == 96) return new Punto(0.000000, -0.045000, 0.00700);
        if(nodo == 97) return new Punto(0.000000, -0.045000, 0.00700);
        if(nodo == 98) return new Punto(0.000000, 0.015000, 0.00700);
        if(nodo == 99) return new Punto(0.000000, 0.015000, 0.00700);
        break;
    case 5:
        if(nodo == 20) return new Punto(0.000000, -0.056000, 0.01000);
        if(nodo == 21) return new Punto(0.000000, 0.026000, 0.01000);
        if(nodo == 45) return new Punto(0.000000, -0.056000, 0.01000);
        if(nodo == 46) return new Punto(0.000000, 0.026000, 0.01000);
        if(nodo == 88) return new Punto(0.000000, -0.038000, 0.00700);
        if(nodo == 89) return new Punto(0.000000, -0.038000, 0.00700);
        if(nodo == 90) return new Punto(0.000000, 0.022000, 0.00700);
        if(nodo == 91) return new Punto(0.000000, 0.022000, 0.00700);
        if(nodo == 96) return new Punto(0.000000, -0.038000, 0.00700);
        if(nodo == 97) return new Punto(0.000000, -0.038000, 0.00700);
        if(nodo == 98) return new Punto(0.000000, 0.022000, 0.00700);
        if(nodo == 99) return new Punto(0.000000, 0.022000, 0.00700);
        break;
    case 6:
        if(nodo == 2) return new Punto(0.000000, -0.086957, 0.01304);
        if(nodo == 3) return new Punto(0.000000, -0.043478, 0.00000);
        if(nodo == 4) return new Punto(0.000000, 0.086957, 0.00000);
        if(nodo == 25) return new Punto(0.000000, 0.043478, -0.01739);
        if(nodo == 24) return new Punto(0.000000, 0.043478, -0.00869);
        if(nodo == 23) return new Punto(0.000000, 0.017391, 0.00000);
        if(nodo == 21) return new Punto(0.000000, 0.017391, 0.00000);
        if(nodo == 50) return new Punto(0.000000, 0.043478, -0.01739);
        if(nodo == 49) return new Punto(0.000000, 0.043478, -0.00869);
        if(nodo == 48) return new Punto(0.000000, 0.017391, 0.00000);
        if(nodo == 46) return new Punto(0.000000, 0.017391, 0.00000);
        if(nodo == 59) return new Punto(0.000000, 0.008696, 0.00000);
        if(nodo == 61) return new Punto(0.000000, 0.008696, 0.00000);
        if(nodo == 63) return new Punto(0.000000, 0.008696, 0.00000);
        if(nodo == 65) return new Punto(0.000000, 0.008696, 0.00000);
        if(nodo == 90) return new Punto(0.000000, 0.017391, 0.00000);
        if(nodo == 91) return new Punto(0.000000, 0.017391, 0.00000);
        if(nodo == 92) return new Punto(0.000000, 0.017391, 0.00000);
        if(nodo == 93) return new Punto(0.000000, 0.017391, 0.00000);
        if(nodo == 98) return new Punto(0.000000, 0.017391, 0.00000);
        if(nodo == 99) return new Punto(0.000000, 0.017391, 0.00000);
        if(nodo == 100) return new Punto(0.000000, 0.017391, 0.00000);
        if(nodo == 101) return new Punto(0.000000, 0.017391, 0.00000);
        break;
    case 7:
        if(nodo == 7) return new Punto(0.000000, 0.032500, 0.00000);
        if(nodo == 32) return new Punto(0.000000, -0.020000, 0.00000);
        if(nodo == 57) return new Punto(0.000000, -0.020000, 0.00000);
        if(nodo == 6) return new Punto(0.000000, -0.021000, 0.00000);
        if(nodo == 70) return new Punto(0.000000, -0.020000, 0.00000);
        if(nodo == 71) return new Punto(0.000000, -0.020000, 0.00000);
        if(nodo == 76) return new Punto(0.000000, 0.023000, 0.00000);
        if(nodo == 77) return new Punto(0.000000, 0.023000, 0.00000);
        break;
    case 8:
        if(nodo == 20) return new Punto(0.000000, 0.030000, -0.01000);
        if(nodo == 45) return new Punto(0.000000, 0.030000, -0.01000);
        if(nodo == 88) return new Punto(0.000000, 0.015000, -0.00700);
        if(nodo == 89) return new Punto(0.000000, 0.015000, -0.00700);
        if(nodo == 96) return new Punto(0.000000, 0.015000, -0.00700);
        if(nodo == 97) return new Punto(0.000000, 0.015000, -0.00700);
        break;
    case 9:
        if(nodo == 34) return new Punto(0.000000, -0.260000, -0.05000);
        if(nodo == 7) return new Punto(0.000000, -0.260000, -0.05000);
        if(nodo == 8) return new Punto(0.000000, -0.260000, -0.10000);
        if(nodo == 9) return new Punto(0.000000, -0.130000, -0.15000);
        if(nodo == 31) return new Punto(0.000000, -0.150000, -0.13000);
        if(nodo == 56) return new Punto(0.000000, -0.150000, -0.13000);
        if(nodo == 74) return new Punto(0.000000, -0.200000, -0.05000);
        if(nodo == 75) return new Punto(0.000000, -0.200000, -0.05000);
        if(nodo == 76) return new Punto(0.000000, -0.200000, -0.05000);
        if(nodo == 77) return new Punto(0.000000, -0.200000, -0.05000);
        if(nodo == 79) return new Punto(0.000000, -0.020000, 0.00000);
        if(nodo == 80) return new Punto(0.000000, -0.020000, 0.00000);
        break;
    case 10:
        if(nodo == 30) return new Punto(0.000000, -0.140000, -0.01000);
        if(nodo == 55) return new Punto(0.000000, -0.140000, -0.01000);
        if(nodo == 79) return new Punto(0.000000, -0.100000, -0.00800);
        if(nodo == 80) return new Punto(0.000000, -0.100000, -0.00800);
        if(nodo == 70) return new Punto(0.000000, -0.030000, -0.02000);
        if(nodo == 71) return new Punto(0.000000, -0.030000, -0.02000);
        if(nodo == 72) return new Punto(0.000000, -0.030000, -0.02000);
        if(nodo == 73) return new Punto(0.000000, -0.030000, -0.02000);
        if(nodo == 74) return new Punto(0.000000, -0.030000, -0.02000);
        if(nodo == 75) return new Punto(0.000000, -0.030000, -0.02000);
        if(nodo == 76) return new Punto(0.000000, -0.040000, -0.02000);
        if(nodo == 77) return new Punto(0.000000, -0.040000, -0.02000);
        if(nodo == 81) return new Punto(0.000000, -0.040000, -0.00000);
        if(nodo == 82) return new Punto(0.000000, -0.040000, -0.00000);
        break;
    }
    return new Punto(0,0,0);
};
