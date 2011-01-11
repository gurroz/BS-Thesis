#include "comando.h"

Comando::Comando(Malla *m) {
    malla = m;
}

Malla* Comando::getMalla() {
    return malla;
}
