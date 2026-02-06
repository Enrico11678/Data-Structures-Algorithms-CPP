
#include "zlasdtest/test.hpp"

#include "zmytest/test.hpp"

/* ************************************************************************** */

#include <iostream>

/* ************************************************************************** */

int main() {
  std::cout << "LASD Libraries 2025" << std::endl;

  int scelta = 0;
  
  do{
    std::cout << "Choose the test to run (1: lasdtest, 2: mytest, 0: exit): ";
    std::cin >> scelta;

    switch(scelta){
      case 1:
        lasdtest();
        break;
      case 2:
        mytest();
        break;
      case 0:
        std::cout << "Exiting..." << std::endl;
        break;
      default:
        std::cout << "Invalid choice, please try again." << std::endl;
    }
  }while(scelta != 0);

  return 0;
}
