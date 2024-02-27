#include <LogMe/LogMeStaticChain.hpp>
#include <vector>
#include <list>


// On veut changer le comportement pour les listes de manière non intrusive
// dans la bibliothèque
struct MyListFormatter : LogMe::FormatterBase<LogMe::DefaultFormatter>
{
   using base = LogMe::FormatterBase<LogMe::DefaultFormatter>;
   using base::format; // Obligé (raison obscure du C++ sur les règles de lookup)


   template <class T>
   static void format(std::ostream& os, const std::list<T>& data) { LogMe::format_container(os, data, '{', '}'); }
};




int main() {
   // On utiliser le formatter par default de bibliothèque
   {
      LogMe::StreamLogger<> mylogger;
      mylogger << "Le logger de la bibliothèque avec le formatteur par défaut!\n";
      {
         auto vec = std::vector{1, 2, 3};
         mylogger << "Vec=" << vec << "\n";
      }
      {
         auto list = std::list{1, 2, 3};
         mylogger << "List=" << list << "\n";
      }
   }


   // On utiliser le formatter par default de bibliothèque
   {
      LogMe::StreamLogger<MyListFormatter> mylogger;
      mylogger << "Mon logger que j'ai cutomizé!\n";
      {
         auto vec = std::vector{1, 2, 3};
         mylogger << "Vec=" << vec << "\n";
      }
      {
         auto list = std::list{1, 2, 3};
         mylogger << "List=" << list << "\n";
      }
   }
}