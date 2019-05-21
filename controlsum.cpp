#include <iostream>
#include <iostream>
#include <cmath>
#include <chrono>
#include <thread>
#include <memory>
#include <vector>
#include <random>
#include <map>

using ui = unsigned int;

class CollisionHolder{
    bool collisionFound;
    std::array<std::string,2> collisions;
    unsigned collisions_count;
    public:
    CollisionHolder():collisions_count(0),collisionFound(false){}
    void addString(const std::string& colliding_string){
        switch (collisions_count)
        {
        case 0:
            collisions[0] = colliding_string;
            collisions_count++;
            break;
        case 1:
            if(colliding_string!=collisions[0]){
                collisions[1] = colliding_string;
            collisions_count++;
            collisionFound = true;}
            break;
        
        default:
            collisions_count++;
            break;
        }
    }

    const auto& get_collisions(){
        return collisions;
    }

    bool collision_found(){
        return collisionFound;
    }

    unsigned collision_count(){
        return collisions_count;
    }

};


ui DJB(std::string data){
    ui H = 5381;
    for(auto character : data){
        H = (H<<5) + H + ((ui)character);
    }

    return H;
}

ui Addler32(std::string data){
    ui A = 1; //suma bajtów (+1)
    ui B = 0; //suma wszystkich a
    ui P = 65521;

    for(auto character : data){
        A = (A+character)%P;
        B = (B+A)%P;
    }

    return (B<<16)+A;
}




const std::string source  = "abcdefghijklmopqrstvuwxyzABCDEFGHIJKLMNOPQRSTVUWXYZ123456789!@#$^&*(){}[];:'<>,./?|~"; 

std::default_random_engine generator{static_cast<long unsigned int>(time(0))};
std::uniform_int_distribution<int> distribution(0,source.length()-1);


std::string random_string(int length){
    
    
    char* chars = new char [length];
    for (size_t i = 0; i < length; i++)
    {
        chars[i] = source[distribution(generator)]; 
    }

    std::string random_string(chars);
    delete [] chars;

    return random_string;
    
}

void classroomExercise(){
    std::map<ui,CollisionHolder> addler32_8;
    std::map<ui,CollisionHolder> addler32_100;
    std::map<ui,CollisionHolder> djb_8;
    std::map<ui,CollisionHolder> djb_100;
    for (int i = 0; i < 100000; i++)
    {
        std::string random_8_addler = random_string(8);
        std::string random_100_addler = random_string(100);
        std::string random_8_djb = random_string(8);
        std::string random_100_djb = random_string(100);
        addler32_8[Addler32(random_8_addler)].addString(random_8_addler);
        addler32_100[Addler32(random_100_addler)].addString(random_100_addler);
        djb_8[DJB(random_8_djb)].addString(random_8_djb);
        djb_100[DJB(random_100_djb)].addString(random_100_djb);
    }


    auto print_info = [](auto& hash, auto& collisionHolder)->void{
         if(collisionHolder.collision_found()){
            auto& collisions = collisionHolder.get_collisions();
            std::cout<<"Collision found for hash: "<<hash<<'\n'
            <<"Total collisions for hash: "<<collisionHolder.collision_count()<<'\n'
            <<"Colliding strings:\n"
            <<collisions[0]<<'\n'
            <<collisions[1]<<"\n\n";
            
        }
    };

    std::cout<<"****************||    Addler32 - 8   ||*********************\n\n";
    for(auto&[hash,collisionHolder] : addler32_8){
       print_info(hash,collisionHolder);
    }
    std::cout<<"****************||    Addler32 - 100 ||*********************\n\n";
    for(auto&[hash,collisionHolder] : addler32_100){
        print_info(hash,collisionHolder);
    }
    std::cout<<"****************||    DJB - 8        ||*********************\n\n";
    for(auto&[hash,collisionHolder] : djb_8){
        print_info(hash,collisionHolder);
    }
    std::cout<<"****************||    DJB - 100      ||*********************\n\n";
    for(auto&[hash,collisionHolder] : djb_100){
        print_info(hash,collisionHolder);
    }


    std::cout<<"****************||    Addler32 - 8   ||*********************\n\n";
    ui collisions = 0;
    for(auto&[hash,collisionHolder] : addler32_8){
        if(collisionHolder.collision_found()) collisions+= collisionHolder.collision_count();
    }
    std::cout<<"Total collisions: "<<collisions<<'\n';
    collisions = 0;
    std::cout<<"****************||    Addler32 - 100 ||*********************\n\n";
    for(auto&[hash,collisionHolder] : addler32_100){
        if(collisionHolder.collision_found()) collisions+= collisionHolder.collision_count();
    }
    
    std::cout<<"Total collisions: "<<collisions<<'\n';
    collisions = 0;
    std::cout<<"****************||    DJB - 8        ||*********************\n\n";
    for(auto&[hash,collisionHolder] : djb_8){
        if(collisionHolder.collision_found()) collisions+= collisionHolder.collision_count();
    }
    
    std::cout<<"Total collisions: "<<collisions<<'\n';
    collisions = 0;
    std::cout<<"****************||    DJB - 100      ||*********************\n\n";
    for(auto&[hash,collisionHolder] : djb_100){
    if(collisionHolder.collision_found()) collisions+= collisionHolder.collision_count();
    
    }
    std::cout<<"Total collisions: "<<collisions<<'\n';
    collisions = 0;

    
}



int main(int argc, char** argv){

std::string mode = argv[1];
std::string input;


    if(mode=="--addler"){
        std::cin>>input;
        std::cout<<Addler32(input)<<'\n';
    }
    else if(mode=="--djb"){
        std::cin>>input;
        std::cout<<DJB(input)<<'\n';
    }
    else classroomExercise();





}