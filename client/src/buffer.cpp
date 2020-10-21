#include "header.h"

//Instâncias da classe buffer
buffer::buffer(/* args */)
{
    this->flag_rec = false;
    this->flag_send = false;
    this->flag_res = 0;
}

buffer::~buffer()
{
}