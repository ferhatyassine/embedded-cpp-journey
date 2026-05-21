// 01_exeptions.cpp - premier contact avec try/throw/catch
#include <iostream>
#include <stdexcept> // pour std::runtime_error, std::invalid_argument

// fonction qui peut echouer : division entiere 
int safe_divide(int a , int b){
    if (b == 0)
    {
        throw std::runtime_error("division par 0");
        return a/b;
    }
    else
    return a/b; 
    
}

int main(){
    // cas normal
    try {
        int r = safe_divide(10,2);
        std::cout << "10/2= "<< r << '\n';
    }
    catch (const std::exception& e){
        std::cout <<"Erreur:" << e.what()<<'\n';
        }
        // cas qui throw
        try
        {
            int r = safe_divide(10,0);
            std::cout<<"10/0= "<<r<<'\n'; //jamais atteint
        }
        catch(const std::exception& e)
        {
            std::cerr <<"Erreur :" << e.what() << '\n';
        }

        //cas std::stoi qui throw std::invalid_argument
        try
        {
            int n = std::stoi("abc");
            std::cout<<"n= "<<n<<'\n';
        }
        catch(const std::invalid_argument& e)
    
        {
            std::cerr << "stoi a echoue :"<< e.what() << '\n';
        }
        catch(const std::exception& e){
            std::cerr<<"autre erreur : "<<e.what()<<'\n';
        }
        std::cout <<"programme termine proprement.\n";
        return 0;
        
}