#include"Serializer.hpp"

#include<iostream>
int main(void)
{
    Data a;
    a.value = 42;
    
    uintptr_t raw=Serializer::serialize(&a);
    Data* restord = Serializer::deserialize(raw);

    if(restord==&a)
    {
        std::cout<< "Success"<<std::endl;
    }
    else
    {
        std::cout<< "Faild" <<std::endl;
    }
}
