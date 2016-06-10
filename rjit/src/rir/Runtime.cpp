#include "Runtime.h"
#include "RIntlns.h"
#include "../Precious.h"
#include "../Protect.h"

#include <iostream>

extern "C" SEXP R_MakeWeakRefC(SEXP key, SEXP val, R_CFinalizer_t fin,
                               Rboolean onexit);

namespace rjit {
namespace rir {

void BCProm::val(SEXP wrapper, SEXP aVal) {
    SET_ATTRIB(wrapper, CONS_NR(aVal, R_NilValue));
    _val = aVal;
}

SEXP mkBCProm(Code* fun, SEXP env) {
    SEXP s = Rf_allocVector(BCCodeType, sizeof(BCProm));
    *getBCProm(s) = BCProm(fun, env);
    return s;
}

SEXP mkBCCls(Code* fun, SEXP formals, num_args_t nargs, Code::CC cc,
             SEXP env) {
    SEXP s = Rf_allocVector(BCCodeType, sizeof(BCClosure));
    *getBCCls(s) = BCClosure(fun, formals, nargs, cc, env);

    Precious::add(s);
    return s;
}
}
}
