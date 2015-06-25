#include "xoorath_cpp_utils.h"
#include "lens.h"
#include <stdlib.h>
#include <iostream>

enum Clothing
{
  Clothing_Undershirt,
  Clothing_Shirt,
  Clothing_Jacket,
};

void badstuff(LensedValue<std::string>& baddy)
{

}

S32 main(S32 argc, cstr argv[])
{
  LensedValue<std::string> texts("input");
  badstuff(texts);

  auto p1 = texts.CreateLens([](std::string & val) {
    val += " 1";
    std::cout << val << std::endl;
  }, 0, false);

  auto p2 = texts.CreateLens([](std::string & val) {
    val += " 2";
    std::cout << val << std::endl;
  }, 0, false);

  auto p3 = texts.CreateLens([](std::string & val) {
    val += " 3";
    std::cout << val << std::endl;
  }, 0, false);

  auto p4 = texts.CreateLens([](std::string & val) {
    val += " 4";
    std::cout << val << std::endl;
  }, 0, false);

  auto p5 = texts.CreateLens([](std::string & val) {
    val += " 5";
    std::cout << val << std::endl;
  }, 0, false);


  p1.Add();
  p3.Add();
  p2.Add();

  texts.GetValue();
  getchar();

  return EXIT_SUCCESS;
}