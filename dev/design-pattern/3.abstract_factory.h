
// assume there is two world

namespace WorldA{
#include "2.Factory.h"
}
namespace WorldB{
#include "2.Factory.h"
}
// ok
#include <vector>
using Interface=WorldA::Interface;
using Id = WorldA::Id;

struct AbstractCreator{
    virtual Interface * Create(Id _id)=0;
};

//WA
struct AbstractCreatorA{
    virtual Interface * Create(Id _id){
        return WorldA::Factory2(_id);
    }
}; 
//WB
struct AbstractCreatorB{
    virtual Interface * Create(Id _id){
        return WorldB::Factory2(_id);
    }
}; 

