#include <iostream>
#include "static_check.h"

int main(int argc,char* argv[]){
  SLIB_STATIC_CHECK(sizeof(int)==3 , size_error);
  return 0;
}
